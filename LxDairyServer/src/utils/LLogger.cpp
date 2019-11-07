#include "LLogger.h"
#include <QDateTime>
#include <QTextStream>
#include <QFileInfo>

static const char * g_levelString[EL_LevelCount] =
{
    "CRITICAL",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "DEBUG2"
};

CLLogger::CLLogger(const QString &strLogFile, int level)
    : m_loglevel(level)
    , m_nMaxSize(524288)
{
    m_pFile = new QFile(strLogFile);
    if(m_pFile && !m_pFile->open( QFile::WriteOnly | QFile::Append))
    {
        delete m_pFile;
        m_pFile = 0;
    }
}

CLLogger::~CLLogger()
{
    if(m_pFile)
    {
        m_pFile->close();
        delete m_pFile;
    }
}

bool CLLogger::isValid()
{
    return m_pFile != 0;
}

void CLLogger::setLogLevel(int level)
{
    if(level < EL_Critical)
    {
        m_loglevel = EL_Critical;
    }
    else if(level > EL_Debug2)
    {
        m_loglevel = EL_Debug2;
    }
    else
    {
        m_loglevel = level;
    }
}

void CLLogger::log(int level, const char *fmt, ...)
{
    if(level > m_loglevel || !m_pFile) return;

    char buffer[MAX_LOG_STRING_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, MAX_LOG_STRING_LEN - 1, fmt, args);
    va_end(args);

    QString strLogInfo = QString("%1[%2]: %3\r\n")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
            .arg(g_levelString[level])
            .arg(buffer);

    log2file(strLogInfo);
}

void CLLogger::log(int level, const QString &content)
{
    if(level > m_loglevel || !m_pFile) return;
    QString strLogInfo = QString("%1[%2]: %3\r\n")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
            .arg(g_levelString[level])
            .arg(content);

    log2file(strLogInfo);
}

void CLLogger::log2file(const QString &log)
{
    if(m_pFile->size() >= m_nMaxSize )
    {
        backup();//the current file will be renamed
    }
    m_pFile->write(log.toLatin1());
    m_pFile->flush();
}

///
/// \brief CLLogger::backup
/// 日志文件过大时需要另起一个文件
///
void CLLogger::backup()
{
    QString logFileName = m_pFile->fileName();
    QString magicFileName = QString("%1.magic").arg(logFileName);
    QFile magic(magicFileName);
    int number = 1;
    if(magic.exists())
    {
        magic.open(QFile::ReadWrite);
        QTextStream ts(&magic);
        ts.setCodec("UTF-8");
        ts >> number;
        number++;
        ts.seek(0);
        ts << number;
        ts.flush();
        magic.close();
    }
    else
    {
        magic.open(QFile::WriteOnly);
        QTextStream ts(&magic);
        ts.setCodec("UTF-8");
        ts << 1;
        ts.flush();
        magic.flush();
        magic.close();
    }

    QString backupName = QString("%1.%2").arg(logFileName).arg(number);
    m_pFile->copy(backupName);
    m_pFile->open(QFile::WriteOnly | QFile::Truncate);
}
