#include "MiniWidget.h"
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>
#include <QtDebug>

CMiniWidget::CMiniWidget(QWidget *parent)
    : QWidget(parent, Qt::WindowStaysOnTopHint | Qt::Window | Qt::FramelessWindowHint)
{


    //setCursor(QCursor(Qt::PointingHandCursor));
}

void CMiniWidget::show(const QString &strText)
{
    m_strText = strText;
    update();
    QWidget::show();

    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    int dWidth = screenRect.width();
    //int dHeight = screenRect.height();//桌面大小
    move(dWidth - width(), 0);
    qDebug() << __FUNCTION__ << rect();
}

void CMiniWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));
    painter.drawText(rect(), Qt::AlignCenter, m_strText);
}

void CMiniWidget::enterEvent(QEvent *event)
{
    qDebug() << __FUNCTION__;

    QWidget::enterEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
}

QSize CMiniWidget::sizeHint() const
{
    return QSize(100, 40);
}
