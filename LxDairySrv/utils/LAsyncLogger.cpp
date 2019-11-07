#include "LAsyncLogger.h"
#include "LLogger.h"
#include <QHash>
#include <QEvent>
#include <QCoreApplication>
#include <QThread>
#include "LHttpConfig.h"
#include "LHttpEvent.h"
#include <QSettings>
#include <QDir>



///
/// \brief 单一线程的日志数据,
///
class LogBuffer
{
public:
    LogBuffer(QObject* receiver)
        : m_receiver(receiver)
        , m_level(EL_Error)
        , m_maxLen(4096)
    {
        m_content.reserve(m_maxLen);
    }

    void checkLogLevelChange(int level)
    {
        flush();

        if(level != m_level)
        {
            m_level = level;
        }
    }

    void debug()
    {
        checkLogLevelChange(EL_Debug);
    }

    void info()
    {
        checkLogLevelChange(EL_Info);
    }

    void warn()
    {
        checkLogLevelChange(EL_Warn);
    }

    void error()
    {
        checkLogLevelChange(EL_Error);
    }

    void flush()
    {
        if(m_content.length() > 0)
        {
            // 向所属线程推送事件
            QCoreApplication::postEvent(m_receiver, new AsyncLoggerEvent(m_content, m_level));
            m_content.clear();
        }
    }

    ///
    /// \brief 记录tid字符串到m_content
    /// \param threadId
    ///
    void tid(Qt::HANDLE threadId)
    {
        m_content += " tid ";
#ifdef WIN32
        char buf[16];
        sprintf(buf, "%p", threadId);
        m_content += buf;
#else
        m_content += threadId;
#endif
    }

    void checkFlush()
    {
        if(m_content.length() > 4000)
        {
            QCoreApplication::postEvent(m_receiver, new AsyncLoggerEvent(m_content, m_level));
            m_content.clear();
        }
    }

    void putQChar(QChar t)
    {
        m_content += t;
        checkFlush();
    }

    void putChar(char t)
    {
        m_content += t;
        checkFlush();
    }

    void putCString(const char* t)
    {
        m_content += t;
        checkFlush();
    }

    void putQString(const QString & t)
    {
        m_content += t;
        checkFlush();
    }

    void putLatin1(const QLatin1String & t)
    {
        m_content += t;
        checkFlush();
    }

    void putByteArray(const QByteArray & t)
    {
        m_content += t;
        checkFlush();
    }

    void putStringRef(const QStringRef & t)
    {
        m_content += t;
        checkFlush();
    }

    // 事件接受对象
    QObject* m_receiver;
    int m_level;
    int m_maxLen;
    QString m_content;
};





///
/// \brief The AsyncLoggerPrivate class
/// 异步日志私有类，隐藏实现
///
class AsyncLoggerPrivate : public QObject
{
public:
    AsyncLoggerPrivate()
        : m_loglevel(EL_Debug)
        , m_maxSize(524288)
        , m_logdir("logs")
        , m_log(m_logdir + "/httpserver.log")
    {
        m_log.setMaxSize(m_maxSize);
        QDir dir;
        dir.mkpath(m_logdir);

        if(m_filterKeys.size() < 1)
        {
            return;
        }

        int count = m_filterKeys.size();

        for(int i = 0; i < count; i++)
        {
            m_q->addLogFilter(m_filterKeys.at(i), m_filterLevels.at(i));
        }
    }
    ~AsyncLoggerPrivate()
    {
    }

    ///
    /// \brief event 监听日志的事件
    /// \param e
    /// \return
    ///
    bool event(QEvent* e)
    {
        if(e->type() == AsyncLoggerEvent::s_evType)
        {
            AsyncLoggerEvent* aloggerEvent = (AsyncLoggerEvent*)e;
            QHash<QString, CLLogger*>::iterator it = m_logFilters.begin();

            // 日志过滤
            while(it != m_logFilters.end())
            {
                if(aloggerEvent->m_content.startsWith(it.key()))
                {
                    break;
                }

                ++it;
            }

            if(it != m_logFilters.end())
            {
                it.value()->log(aloggerEvent->m_level, aloggerEvent->m_content);
            }
            else
            {
                m_log.log(aloggerEvent->m_level, aloggerEvent->m_content);
            }

            return true;
        }

        return QObject::event(e);
    }

    //
    LogBuffer* getLogBuffer(Qt::HANDLE tid)
    {
        QHash<Qt::HANDLE, LogBuffer*>::iterator it = m_hashLogBuffers.find(tid);
        LogBuffer* logBuffer;

        if(it == m_hashLogBuffers.end())
        {
            logBuffer = new LogBuffer(this);
            m_hashLogBuffers.insert( tid, logBuffer );
        }
        else
        {
            logBuffer = it.value();
        }

        return logBuffer;
    }

    void reset()
    {
        m_filterKeys.clear();
        m_filterLevels.clear();
    }

    int m_loglevel;
    int m_maxSize;
    QString m_logdir;

    QStringList m_filterKeys;
    QList<int> m_filterLevels;

    //default log
    CLLogger m_log;

    // 存放根据线程id记录对应的日志数据
    QHash<Qt::HANDLE, LogBuffer*> m_hashLogBuffers;

    // 日志过滤
    QHash<QString, CLLogger*> m_logFilters;

    AsyncLogger* m_q;
};






///
/// \brief AsyncLogger::AsyncLogger
///
AsyncLogger::AsyncLogger()
    : m_d(new AsyncLoggerPrivate)
{
    AsyncLoggerEvent::eventType();
}

AsyncLogger::~AsyncLogger()
{
    delete m_d;
}

void AsyncLogger::loadConfig(QString strConfigPath)
{
    QSettings setting(strConfigPath, "ini");
    setting.beginGroup("log");
    m_d->m_loglevel = setting.value("level", EL_Debug).toInt();
    m_d->m_maxSize = setting.value("size", 524288).toInt();
    m_d->m_logdir = setting.value("dir", "logs").toString();
    QString filters = setting.value("filters").toString();

    if(!filters.isEmpty())
    {
        m_d->m_filterKeys = filters.split(',', QString::SkipEmptyParts);
        QString levels = setting.value("filter_levels").toString();

        if(!levels.isEmpty())
        {
            QStringList levelList = levels.split(',', QString::SkipEmptyParts);

            foreach (QString lev, levelList)
            {
                m_d->m_filterLevels.append(lev.toInt());
            }
        }
    }

    setting.endGroup();
}

AsyncLogger & AsyncLogger::getInstance()
{
    static AsyncLogger logger;
    return logger;
}

void AsyncLogger::setLogLevel(int level)
{
    m_d->m_log.setLogLevel(level);
}

void AsyncLogger::addLogFilter(const QString & tag, int level)
{
    QString logFile = QString("%1/%2").arg(m_d->m_logdir).arg(tag);
    CLLogger* logger = new CLLogger(logFile, level);
    logger->setMaxSize(m_d->m_maxSize);
    m_d->m_logFilters.insert(tag, logger);
}

void AsyncLogger::debug()
{
    m_d->getLogBuffer(QThread::currentThreadId())->debug();
}

void AsyncLogger::info()
{
    m_d->getLogBuffer(QThread::currentThreadId())->info();
}

void AsyncLogger::warn()
{
    m_d->getLogBuffer(QThread::currentThreadId())->warn();
}

void AsyncLogger::error()
{
    m_d->getLogBuffer(QThread::currentThreadId())->error();
}

void AsyncLogger::flush()
{
    m_d->getLogBuffer(QThread::currentThreadId())->flush();
}

void AsyncLogger::tid()
{
    Qt::HANDLE tid = QThread::currentThreadId();
    m_d->getLogBuffer(tid)->tid(tid);
}

AsyncLogger & debug(AsyncLogger & logger)
{
    logger.debug();
    return logger;
}

AsyncLogger & info(AsyncLogger & logger)
{
    logger.info();
    return logger;
}

AsyncLogger & warn(AsyncLogger & logger)
{
    logger.warn();
    return logger;
}

AsyncLogger & error(AsyncLogger & logger)
{
    logger.error();
    return logger;
}

AsyncLogger & endl(AsyncLogger & logger)
{
    logger.flush();
    return logger;
}
AsyncLogger & flush(AsyncLogger & logger)
{
    logger.flush();
    return logger;
}
AsyncLogger & tid(AsyncLogger & logger)
{
    logger.tid();
    return logger;
}
AsyncLogger & AsyncLogger::operator<<(QChar t)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQChar(t);
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(bool t)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putCString(t ? "true" : "false");
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(char t)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putChar(t);
    return *this;
}

AsyncLogger & AsyncLogger::operator<<(signed short i)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(i));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(unsigned short i)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(i));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(signed int i)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(i));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(unsigned int i)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(i));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(signed long l)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(l));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(unsigned long l)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(l));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(qint64 i)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(i));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(quint64 i)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(i));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(float f)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(f));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(double f)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(QString::number(f));
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(const char* s)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putCString(s);
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(const QString & s)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putQString(s);
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(const QStringRef & s)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putStringRef(s);
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(QLatin1String s)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putLatin1(s);
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(const QByteArray & b)
{
    m_d->getLogBuffer(QThread::currentThreadId())->putByteArray(b);
    return *this;
}
AsyncLogger & AsyncLogger::operator<<(const void* p)
{
    char buf[16];
    sprintf(buf, "%p", p);
    m_d->getLogBuffer(QThread::currentThreadId())->putCString(buf);
    return *this;
}
