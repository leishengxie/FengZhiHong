#include "LBaseWidget.h"
#include "LEvent.h"

CLBaseWidget::CLBaseWidget(QWidget *parent) : QWidget(parent)
{

}

//void CLBaseWidget::event(QEvent *event)
//{
//    QEvent::Type eType = event->type();
//    if(eType == CSaveEvent::eventType())
//    {
//        //CSaveEvent * saveEvent = (CSaveEvent*)e;
//        return actSaveEvent();
//    }
//    return QWidget::event(event);
//}

void CLBaseWidget::customEvent(QEvent *event)
{
    QEvent::Type eType = event->type();
    if(eType == CSaveEvent::eventType())
    {
        //CSaveEvent * saveEvent = (CSaveEvent*)e;
        actSaveEvent();
        event->accept();
    }

}
