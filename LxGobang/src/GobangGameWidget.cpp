#include "GobangGameWidget.h"
#include "ui_GobangGameWidget.h"

#include "core/Player.h"
#include <QLabel>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

CGobangGameWidget::CGobangGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CGobangGameWidget)
    , CGobangGame(nullptr, new CHumanPlayer(), new CRobotPlayer())
{
    ui->setupUi(this);

    QLabel la;
    //la.setLayout();
    setChessBoard(ui->chessBoardWidget);

    m_pixBg.load(":/img/backgrounimage.jpg");

    m_timerScheduler = new QTimer(this);
    m_timerScheduler->setInterval(1000);
    connect(m_timerScheduler, SIGNAL(timeout()), this, SLOT(slotTimerSchedulerTimeOut()));
}

CGobangGameWidget::~CGobangGameWidget()
{
    delete ui;
}


void CGobangGameWidget::on_btnStart_clicked()
{
    start();
    m_timerScheduler->start();
}

void CGobangGameWidget::on_btnTakeBackChess_clicked()
{

}

void CGobangGameWidget::slotTimerSchedulerTimeOut()
{
    playing();
}

void CGobangGameWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    if (m_pixBg.isNull())
    {
        return;
    }
    QPainter painter(this);
    painter.drawPixmap(rect(), m_pixBg);
}
