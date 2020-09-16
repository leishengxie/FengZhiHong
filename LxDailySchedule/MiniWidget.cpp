#include "MiniWidget.h"
#include <QPainter>
#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QtDebug>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainterPath>
#include <QTimer>

// 默认闹铃
static const QString s_strAlarm = "default_alarm.mp3";

CMiniWidget::CMiniWidget(QWidget *parent)
    : QWidget(parent, Qt::WindowStaysOnTopHint | Qt::CoverWindow | Qt::Window | Qt::FramelessWindowHint)
    , m_pMediaPlayer(new QMediaPlayer(this))
{

    setAttribute(Qt::WA_TranslucentBackground, true);

    m_bCanDrag = false;
    m_unAngle = 0;

    //setCursor(QCursor(Qt::PointingHandCursor));
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    int dWidth = screenRect.width();
    //int dHeight = screenRect.height();//桌面大小
    move(dWidth - width(), 0);
    qDebug() << __FUNCTION__ << rect();

    QString strDefaultAlarmPath = qApp->applicationDirPath() + "/" + s_strAlarm;
    m_pMediaPlayer->setMedia(QUrl::fromLocalFile(strDefaultAlarmPath));
    connect(m_pMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State))
            , this, SLOT(slot_mediaPlayerStateChanged(QMediaPlayer::State)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
    m_timer->setInterval(30);
}

void CMiniWidget::slot_show(const T_ScheduleItem &tScheduleItem)
{
    m_strText = tScheduleItem.strContent;
    if (tScheduleItem.bUseAlarmClock)
    {
        m_pMediaPlayer->play();
        m_timer->start();
    }
    else
    {
        m_pMediaPlayer->stop();
        m_unAngle = 0;
        m_timer->stop();
    }
    update();
    QWidget::show();


}

void CMiniWidget::slot_timeout()
{
    m_unAngle += 1;
    if (m_unAngle >= 360)
    {
        m_unAngle = 0;
    }
    update();
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
    //qDebug() << rectThis << rectContent;
    painter.drawRoundedRect(rectContent, nRadius, nRadius);
    painter.restore();

    // 画头像
    painter.save();
    QPixmap pix(":/img/appIcon/app.ico");
    QRect rectPixSrc = pix.rect();
    QRect rectPixDest = rectPixSrc;
    painter.translate(rectPixDest.width() / 2, rectPixDest.height() / 2); //设置旋转中心
    painter.rotate(m_unAngle); //旋转
    painter.translate(-(rectPixDest.width() / 2), -(rectPixDest.height() / 2)); //将原点复位
    QPainterPath path;
    path.addEllipse(rectPixDest);
    painter.setClipPath(path);
    painter.drawPixmap(rectPixDest, pix);
    painter.restore();

    // 画文本内容
    painter.save();
    QRect rectCurScheduleContent = rectContent.adjusted(rectPixDest.size().width(), 0, 0, 0);
    QFont fontBold = font();
    fontBold.setPointSize(fontBold.pointSize() + 5);
    fontBold.setBold(true);
    painter.setFont(fontBold);
    painter.setPen(QColor(Qt::red));
    QFontMetrics fontMetricsContent(painter.font());
    QString strTextElided = fontMetricsContent.elidedText(m_strText, Qt::ElideRight, width() - rectPixDest.size().width());
    painter.drawText(rectCurScheduleContent, Qt::AlignCenter, strTextElided);
    painter.restore();

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
    setCursor(QCursor(Qt::SizeAllCursor));
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

void CMiniWidget::slot_mediaPlayerStateChanged(QMediaPlayer::State newState)
{
    if (QMediaPlayer::StoppedState == newState)
    {
        //m_pMediaPlayer->stop();
        m_unAngle = 0;
        m_timer->stop();
        update();
    }
}

QSize CMiniWidget::sizeHint() const
{
    return QSize(300, 64);
}
