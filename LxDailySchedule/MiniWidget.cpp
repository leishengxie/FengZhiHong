#include "MiniWidget.h"
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>

CMiniWidget::CMiniWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window | Qt::FramelessWindowHint);


    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    int dWidth = screenRect.width();
    //int dHeight = screenRect.height();//桌面大小
    move(dWidth - width(), 0);
}

void CMiniWidget::showText(const QString &strText)
{
    m_strText = strText;
    update();
}

void CMiniWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));
    painter.drawText(rect(), Qt::AlignCenter, m_strText);
}

QSize CMiniWidget::sizeHint() const
{
    return QSize(100, 40);
}
