#ifndef DAILYSCHEDULEEDITOR_H
#define DAILYSCHEDULEEDITOR_H

#include "DailyScheduleBookModel.h"
#include <QWidget>

namespace Ui {
class CDailyScheduleEditor;
}

class CDailyScheduleEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CDailyScheduleEditor(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~CDailyScheduleEditor();

signals:
    void sigSaveDailySchedule(const T_DailySchedule & tDailySchedule);

public slots:
    void slot_showWithAdd();
    void slot_showWithEdit(const T_DailySchedule & tDailySchedule);

private slots:
    void on_btnAdd_clicked();

    void on_btnSub_clicked();

    void on_btnSave_clicked();

private:
    Ui::CDailyScheduleEditor *ui;

    // 记录当前编辑的时间表id， -1表示新表
    int m_id;
};

#endif // DAILYSCHEDULEEDITOR_H
