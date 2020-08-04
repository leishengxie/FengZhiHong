#include "DailyScheduleEditor.h"
#include "ui_DailyScheduleEditor.h"

CDailyScheduleEditor::CDailyScheduleEditor(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
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
    T_DailySchedule tDailySchedule;
    tDailySchedule.strScheduleName = ui->leScheduleName->text();
    tDailySchedule.lstScheduleItem = ui->tableView->scheduleItemList();

    emit sigSaveDailySchedule(tDailySchedule);
    close();
}
