#include "LBaseWidget.h"
#include "LEvent.h"

CLBaseWidget::CLBaseWidget(QWidget* parent) : QWidget(parent)
{

}

bool CLBaseWidget::actSave()
{
//    CSaveEvent e;
//    QApplication::sendEvent(this, &e);
//    if (!e.isAccepted())
//    {
//        return false;
//    }
//    return true;
}

bool CLBaseWidget::event(QEvent* event)
{
    QEvent::Type eType = event->type();
    if(eType == CSaveEvent::eventType())
    {
        //CSaveEvent * saveEvent = (CSaveEvent*)e;
        actSaveEvent();
        return true;
    }
    return QWidget::event(event);
}

//void CLBaseWidget::customEvent(QEvent *event)
//{
//    QEvent::Type eType = event->type();
//    if(eType == CSaveEvent::eventType())
//    {
//        //CSaveEvent * saveEvent = (CSaveEvent*)e;
//        actSaveEvent();
//        event->accept();
//    }

//}
