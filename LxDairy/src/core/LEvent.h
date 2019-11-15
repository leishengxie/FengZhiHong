#ifndef CLEVENT_H
#define CLEVENT_H
#include <QEvent>

class CLEvent
{
public:
    CLEvent();
};

///
/// \brief The TaskEvent class
///
class TaskEvent : public QEvent
{
public:
    TaskEvent(Type type)
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




#endif // CLEVENT_H
