#include "DailyScheduleEditor.h"
#include "ui_DailyScheduleEditor.h"
#include <QMessageBox>

CDailyScheduleEditor::CDailyScheduleEditor(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f)
  , ui(new Ui::CDailyScheduleEditor)
  , m_id(-1)
{
    ui->setupUi(this);

    connect(ui->tableView, SIGNAL(sigSelectedChanged(bool)), ui->btnSub, SLOT(setEnabled(bool)));
}

CDailyScheduleEditor::~CDailyScheduleEditor()
{
    delete ui;
}

void CDailyScheduleEditor::slot_showWithAdd()
{
    m_id = -1;
    ui->btnSub->setEnabled(false);
    ui->leScheduleName->clear();
    ui->tableView->clear();
    show();
}

void CDailyScheduleEditor::slot_showWithEdit(const T_DailySchedule &tDailySchedule)
{
    m_id = tDailySchedule.id;
    ui->btnSub->setEnabled(false);
    ui->leScheduleName->setText(tDailySchedule.strScheduleName);
    ui->tableView->slotLoadDailySchedule(tDailySchedule);
    show();
}

void CDailyScheduleEditor::on_btnAdd_clicked()
{
    ui->tableView->addItem();
}

void CDailyScheduleEditor::on_btnSub_clicked()
{
    ui->tableView->slot_delete();
}

void CDailyScheduleEditor::on_btnSave_clicked()
{
    if(ui->leScheduleName->text().isEmpty())
    {
        QMessageBox::warning(this, "提示", "请输入标题");
        return;
    }
    if (ui->tableView->scheduleItemList().isEmpty())
    {
        QMessageBox::warning(this, "提示", "作息时间表至少要有一项时间安排项");
        return;
    }

    T_DailySchedule tDailySchedule;
    tDailySchedule.id = m_id;
    tDailySchedule.strScheduleName = ui->leScheduleName->text();
    tDailySchedule.lstScheduleItem = ui->tableView->scheduleItemList();

    emit sigSaveDailySchedule(tDailySchedule);
    close();
}
