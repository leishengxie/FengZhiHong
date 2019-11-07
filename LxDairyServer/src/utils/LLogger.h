#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H

#include <QFile>
#include <QString>

#define MAX_LOG_STRING_LEN  4096

enum E_LogLEevel
{
    EL_Critical,
    EL_Error,
    EL_Warn,
    EL_Info,
    EL_Debug,
    EL_Debug2,

    EL_LevelCount
};


///
/// \brief 日志类, 把文本日志输入到文件
///
class CLLogger
{
public:
    CLLogger(const QString & strLogFile, int level = EL_Info);
    ~CLLogger();

    bool isValid();
    void setLogLevel(int level);
    void log(int level, const char * fmt, ...);
    void log(int level, const QString &content);

    void setMaxSize(int bytes)
    {
        m_nMaxSize = bytes;
    }

protected:
    void log2file(const QString &log);
    void backup();

protected:
    // 日志级别
    int m_loglevel;

    // 日志文件指针
    QFile* m_pFile;

    // 日志文件的大小
    int m_nMaxSize;
};

#ifdef Q_OS_WIN
#define INT64_FMT "%I64d"
#else
#define INT64_FMT "%lld"
#endif

#endif // SIMPLE_LOG_H
