#include "LLrcWidget.h"
#include <QApplication>
#include <QMenu>
#include <QPainter>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QTimer>
#include <QDesktopWidget>

// 30毫秒刷新
#define DEFAULT_MS    30

// 定义常量
static const int s_nWidthThis = 800;
static const int s_nHeightThis = 60;
static const int s_nWidthInnerThis = 200;   // 作为内部部件时的宽度
static const int s_nHeightInnerThis = 25;

CLLrcWidget::CLLrcWidget(QWidget *parent)
    : QWidget(parent)
    , m_pTimer( new QTimer(this))
    , m_ptOffset(QPoint(0, 0))
    , m_dLrcMaskWidth(0)
{
    init();
}



void CLLrcWidget::init()
{
    if (isWindow())
    {
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        // 设置背景透明
        setAttribute(Qt::WA_TranslucentBackground);
        // 固定部件大小
        setMaximumSize(s_nWidthThis, s_nHeightThis);
        setMinimumSize(s_nWidthThis, s_nHeightThis);

        // 设置字体
        font.setFamily("Times New Roman");
        font.setBold(true);
        font.setPointSize(30);


        //设置歌词位置
        QDesktopWidget* desk = QApplication::desktop();
        move(((desk->width() / 2) - (width() / 3)) , (desk->height() - height()) - 50);

        show();
    }
    else
    {

        //setStyleSheet("QWidget{border:none}");
        // 设置字体
        font.setFamily("Times New Roman");
        font.setBold(true);
    }


    // 歌词的线性渐变填充
    m_linearGradient.setStart(0, 10);
    m_linearGradient.setFinalStop(0, 40);
    m_linearGradient.setColorAt(0.1, QColor(14, 179, 255));
    m_linearGradient.setColorAt(0.5, QColor(114, 232, 255));
    m_linearGradient.setColorAt(0.9, QColor(14, 179, 255));
    // 遮罩的线性渐变填充
    m_linearGradientMask.setStart(0, 10);
    m_linearGradientMask.setFinalStop(0, 40);
    m_linearGradientMask.setColorAt(0.1, QColor(222, 54, 4));
    m_linearGradientMask.setColorAt(0.5, QColor(255, 72, 16));
    m_linearGradientMask.setColorAt(0.9, QColor(222, 54, 4));


    // 设置定时器
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

}

void CLLrcWidget::clearCurLrc()
{
    m_pTimer->stop();
    m_dLrcMaskWidth = 0;
    CLLrc::clearCurLrc();
    update();
}

void CLLrcWidget::onPositionChanged(qint64 position)
{
    refreshLrc(position);
    if (m_bCurLrcTimeOut)
    {
        stop();
        start();
    }
}

void CLLrcWidget::onDurationChanged(qint64 duration)
{
    refreshDuration(duration);
}

void CLLrcWidget::start()
{
    qreal count = m_llIntervalTime / DEFAULT_MS;
    // 获取遮罩每次需要增加的宽度，这里的200是部件的固定宽度
    m_dLrcMaskWidthInterval = width() / count;
    m_dLrcMaskWidth = 0;
    m_pTimer->start(DEFAULT_MS);
}

void CLLrcWidget::stop()
{
    m_pTimer->stop();
    m_dLrcMaskWidth = 0;
    update();
}



void CLLrcWidget::onTimeOut()
{
    m_dLrcMaskWidth += m_dLrcMaskWidthInterval;
    update();
}

void CLLrcWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setFont(font);
    // 先绘制底层文字，作为阴影
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawText(1, 1, width(), height(), Qt::AlignLeft, m_strCurLrc);
    // 再在上面绘制渐变文字
    painter.setPen(QPen(m_linearGradient, 0));
    painter.drawText(0, 0, width(), height(), Qt::AlignLeft, m_strCurLrc);

    // 设置歌词遮罩
    painter.setPen(QPen(m_linearGradientMask, 0));
    painter.drawText(0, 0, m_dLrcMaskWidth, height(), Qt::AlignLeft, m_strCurLrc);
}

void CLLrcWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    m_ptOffset = event->globalPos() - frameGeometry().topLeft();
}

void CLLrcWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
       setCursor(Qt::PointingHandCursor);
       move(event->globalPos() - m_ptOffset);
    }
}

void CLLrcWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (isWindow())
    {
        QMenu menu;
        menu.addAction(tr("隐藏"),this,SLOT(hide()));
        menu.exec(event->globalPos());
    }
}

QSize CLLrcWidget::sizeHint() const
{
    return QSize(s_nWidthInnerThis, s_nHeightInnerThis);
}
