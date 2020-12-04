#include "GobangGameWidget.h"
#include "ui_GobangGameWidget.h"

#include <QLabel>
#include <QTimer>

CGobangGameWidget::CGobangGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CGobangGameWidget)
    //, CGobangGame()
{
    ui->setupUi(this);

    QLabel la;
    //la.setLayout();

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
