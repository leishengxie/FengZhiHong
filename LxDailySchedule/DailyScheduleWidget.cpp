#include "DailyScheduleWidget.h"
#include "ui_DailyScheduleWidget.h"
#include "DailyScheduleDelegate.h"
#include "DailyScheduleModel.h"
#include <QTime>

CDailyScheduleWidget::CDailyScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDailyScheduleWidget)
{
    ui->setupUi(this);
    CDailyScheduleModel* pDailyScheduleModel = new CDailyScheduleModel(this);
    CDailyScheduleDelegate* pDailyScheduleDelegate = new CDailyScheduleDelegate;
    ui->tableView->setModel(pDailyScheduleModel);
    ui->tableView->setItemDelegate(pDailyScheduleDelegate);
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

CDailyScheduleWidget::~CDailyScheduleWidget()
{
    delete ui;
}

void CDailyScheduleWidget::on_btnAdd_clicked()
{
    ((CDailyScheduleModel*)ui->tableView->model())->addDefaultScheduleItem();
}

void CDailyScheduleWidget::on_btnSub_clicked()
{
    //((CDairyStatisticsModel*)ui->tableView->model())->showDairyStatistics(lstDairy);
}
