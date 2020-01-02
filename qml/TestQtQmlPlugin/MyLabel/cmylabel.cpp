#include "cmylabel.h"
#include <QLabel>
#include <QHBoxLayout>

CMyLabel::CMyLabel(QWidget *parent) :
    QLabel(parent)
{
//    QLabel *label = new QLabel;
//    label->setText("hello world");
//    QHBoxLayout* lay = new QHBoxLayout;
//    lay->addWidget(label);
//    setLayout(lay);
    setText("hello");
}
