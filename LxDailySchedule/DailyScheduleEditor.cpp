#include "DailyScheduleEditor.h"
#include "ui_DailyScheduleEditor.h"

CDailyScheduleEditor::CDailyScheduleEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDailyScheduleEditor)
{
    ui->setupUi(this);
}

CDailyScheduleEditor::~CDailyScheduleEditor()
{
    delete ui;
}

void CDailyScheduleEditor::on_btnAdd_clicked()
{
    ui->tableView->addItem();
}

void CDailyScheduleEditor::on_btnSub_clicked()
{
    //((CDairyStatisticsModel*)ui->tableView->model())->showDairyStatistics(lstDairy);
}

void CDailyScheduleEditor::on_btnSave_clicked()
{

}
