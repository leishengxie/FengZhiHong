#include "QMyLabel.h"


QClickLabel::QClickLabel(QWidget *parent):QLabel(parent){}
QClickLabel::QClickLabel(QWidget *parent, Qt::WindowFlags f):QLabel(parent,f){}
QClickLabel::QClickLabel(const QString &text, QWidget *parent,Qt::WindowFlags f):QLabel(text,parent,f){}

void QClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    emit clicked();
}
