#include "widget.h"

#include <QPaintEvent>
#include <QPainter>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // 设置画笔颜色
    painter.setPen(QColor(0, 160, 230));

    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);

    painter.drawText(rect(), QStringLiteral("青春不老，奋斗不止！-纯正开源之美，有趣、好玩、靠谱 33333333333333333333333333333333333333333333333333333333333333333333333333444444444444444444444444444444444444444444444444444444444444444444444444"), option);
}
