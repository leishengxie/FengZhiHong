#ifndef CLEVENT_H
#define CLEVENT_H
#include <QEvent>


enum E_ActionEvent
{
    EA_Save = QEvent::User + 1,
    EA_SaveAll
};


class CSaveEvent : public QEvent
{
public:
    CSaveEvent()
        : QEvent(eventType())
    {}

    static QEvent::Type eventType()
    {
        if(s_evType == QEvent::None)
        {
            s_evType = (QEvent::Type)registerEventType();
        }
        return s_evType;
    }

private:
    static QEvent::Type s_evType;
};




#endif // CLEVENT_H
