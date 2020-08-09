#include "MiniWidget.h"
#include <QPainter>
#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QtDebug>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainterPath>

CMiniWidget::CMiniWidget(QWidget *parent)
    : QWidget(parent, Qt::WindowStaysOnTopHint | Qt::CoverWindow | Qt::Window | Qt::FramelessWindowHint)
{

    setAttribute(Qt::WA_TranslucentBackground, true);

    m_bCanDrag = false;
    //setCursor(QCursor(Qt::PointingHandCursor));
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    int dWidth = screenRect.width();
    //int dHeight = screenRect.height();//桌面大小
    move(dWidth - width(), 0);
    qDebug() << __FUNCTION__ << rect();
}

void CMiniWidget::show(const QString &strText)
{
    m_strText = strText;
    update();
    QWidget::show();


}

void CMiniWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
   // painter.eraseRect(rect());
    //painter.setOpacity(0);
   // painter.fillRect(rect(), QColor(255, 255, 255, 100));
    QRect rectThis = rect();

    // 画内容区
    painter.save();
    painter.setPen(QColor(Qt::green));
    painter.setBrush(QBrush(Qt::white));
    QRect rectContent;
    rectContent = rectThis.adjusted(0, 10, 0, -10);
    int nRadius = rectContent.size().height() / 2;
    qDebug() << rectThis << rectContent;
    painter.drawRoundedRect(rectContent, nRadius, nRadius);
    painter.restore();

    // 画头像
    painter.save();
    QPixmap pix(":/img/tool_img/maple_leaf_book.png");
    QRect rectPixSrc = pix.rect();
    QRect rectPixDest = rectPixSrc;
    QPainterPath path;
    path.addEllipse(rectPixDest);
    painter.setClipPath(path);
    painter.drawPixmap(rectPixDest, pix);
    painter.restore();

    // 画文本内容
    QRect rectCurScheduleContent = rectContent.adjusted(rectPixDest.size().width(), 0, 0, 0);
    painter.setPen(QColor(Qt::red));
    painter.drawText(rectCurScheduleContent, Qt::AlignCenter, m_strText);

    // 画文本标题
    QFontMetrics fontMetrics(font());
    int h = fontMetrics.height();
    int w = fontMetrics.width("当前安排:");
    QRect rectTitle(rectPixDest.width(), 0, w, h);
    painter.fillRect(rectTitle, Qt::black);

    painter.setPen(QColor(0, 160, 230));
    painter.drawText(rectTitle, Qt::AlignCenter, "当前安排:");
}

void CMiniWidget::enterEvent(QEvent *event)
{
    qDebug() << __FUNCTION__;

    QWidget::enterEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void CMiniWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ( m_bCanDrag )
    {
        QPoint movePot = event->globalPos() - m_ptMousePress;

        // move是移动的位置是相对于全局而言(即屏幕)
        QApplication::activeWindow()->move(movePot);
        return;
    }
}

void CMiniWidget::mousePressEvent(QMouseEvent *event)
{
    m_bCanDrag = true;
    const QPoint& posGlobal= event->globalPos(); // 返回相对于屏幕左上角的全局坐标
    m_ptMousePress = mapFromGlobal(posGlobal); // 转换为相对于当前窗口this的窗口坐标
}

void CMiniWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_bCanDrag = false;
}

void CMiniWidget::changeEvent(QEvent *event)
{

        if(event->type()==QEvent::WindowStateChange)
        {
            if(windowState() & Qt::WindowMinimized)
            {
                event->ignore();
                qDebug() << __FUNCTION__;
            }
        }
    //QWidget::changeEvent(event);

}

QSize CMiniWidget::sizeHint() const
{
    return QSize(256, 64);
}
