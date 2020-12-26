#include "GobangGameWidget.h"
#include "ui_GobangGameWidget.h"

#include "core/Player.h"
#include "core/Judge.h"
#include "ChessBoardWidget.h"

#include <QLabel>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>

CGobangGameWidget::CGobangGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CGobangGameWidget)
    , CGobangGame(new CChessBoardWidget(this), new CHumanPlayer(), new CRobotPlayer())
{
    ui->setupUi(this);
    ui->hLayMain->insertWidget(0, (CChessBoardWidget*)m_pChessBoard);

    m_pixBg.load(":/img/backgrounimage.jpg");

    m_timerScheduler = new QTimer(this);
    m_timerScheduler->setInterval(1000);
    connect(m_timerScheduler, SIGNAL(timeout()), this, SLOT(slotTimerSchedulerTimeOut()));
}

CGobangGameWidget::~CGobangGameWidget()
{
    delete ui;
}

void CGobangGameWidget::onGameStart()
{
    CGobangGame::onGameStart();
    m_timerScheduler->start();
    ui->btnStart->setEnabled(false);
    ui->btnTakeBackChess->setEnabled(false);
    ui->btnRestart->setEnabled(true);
}

void CGobangGameWidget::onGameInOnesTurn()
{
    CGobangGame::onGameInOnesTurn();
    ui->btnTakeBackChess->setEnabled(true);
    ((CChessBoardWidget*)m_pChessBoard)->update();
}

void CGobangGameWidget::onGameOver()
{
    CGobangGame::onGameOver();
    m_timerScheduler->stop();
    bool bWin = CJudge::getInstance()->winner()->isRobot() ? false : true;
    QString strTip;
    if(bWin)
    {
        strTip = "你赢了";
    }
    else
    {
        strTip = "你输了";
    }
    QMessageBox::warning(this, "提示", "游戏结束," + strTip);
    ui->btnTakeBackChess->setEnabled(false);

}


void CGobangGameWidget::on_btnStart_clicked()
{
    CJudge::getInstance()->onEventGameStart();

}

void CGobangGameWidget::on_btnTakeBackChess_clicked()
{

}

void CGobangGameWidget::slotTimerSchedulerTimeOut()
{
    CJudge::getInstance()->onEventInOnesTurn();


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

void CGobangGameWidget::on_btnRestart_clicked()
{
    CJudge::getInstance()->onEventGameRestart();
}
