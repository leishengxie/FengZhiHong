#ifndef CLHTTPEVENT_H
#define CLHTTPEVENT_H
#include <QEvent>
#include <QObject>

enum E_UesrEventType
{
    EU_HttpWorkTask = QEvent::User + 1
};

///
/// \brief The TaskEvent class
///
class TaskEvent : public QEvent
{
public:
    TaskEvent(qintptr socket)
        : QEvent(evType())
        , m_socket(socket)
    {}

    static QEvent::Type evType()
    {
        if(s_evType == QEvent::None)
        {
            s_evType = (QEvent::Type)registerEventType();
        }
        return s_evType;
    }

    qintptr m_socket;

private:
    static QEvent::Type s_evType;
};



///
/// \brief The AsyncLoggerEvent class
/// 自定义事件日志
///
class AsyncLoggerEvent : public QEvent
{
public:
    AsyncLoggerEvent(QString & content, int level)
        : QEvent(eventType())
        , m_content(content)
        , m_level(level)
    {

    }

    static Type eventType()
    {
        if(s_evType == QEvent::None)
        {
            s_evType = (QEvent::Type)registerEventType();
        }
        return s_evType;
    }

    // 用户自定的事件类型
    static Type s_evType;

    // 事件的内容
    QString m_content;

    int m_level;
};



#endif // CLHTTPEVENT_H
