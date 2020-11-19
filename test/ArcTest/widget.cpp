#include "widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *)
{
    QPoint startPt(0, 0);
    QRect rect(startPt.x(), startPt.y(), 200, 50);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing); //抗锯齿
    p.fillRect(rect, QColor(255, 255, 255));

    //int arcR = rect.width()/2;
    //int rectSize = rect.width();
    QPainterPath path;

//    path.moveTo(rect.center());
//    path.arcTo(rect, 0.0f, 180.0f);
//    p.fillPath(path, QBrush(QColor(122, 122, 122)));


    int d = rect.height();
    int r = d / 2;
    path.moveTo(r, 0);
    path.lineTo(rect.width() - r, 0);
    path.arcTo(rect.width() - d, 0, d, d, 90, -180);
    path.lineTo(r, d);
    path.arcTo(0, 0, d, d, 270, -180);
    p.fillPath(path, QBrush(QColor(122, 122, 122)));

}

