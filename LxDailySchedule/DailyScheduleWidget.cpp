#include "DailyScheduleWidget.h"
#include "ui_DailyScheduleWidget.h"


CDailyScheduleWidget::CDailyScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDailyScheduleWidget)
{
    ui->setupUi(this);
    connect(ui->listView, SIGNAL(sigBookClicked(T_DailyScheduleBook)), ui->tableView, SLOT(slotLoadBook(T_DailyScheduleBook)));
}

CDailyScheduleWidget::~CDailyScheduleWidget()
{
    delete ui;
}

void CDailyScheduleWidget::on_btnAdd_clicked()
{
    ui->tableView->addItem();
}

void CDailyScheduleWidget::on_btnSub_clicked()
{
    //((CDairyStatisticsModel*)ui->tableView->model())->showDairyStatistics(lstDairy);
}
