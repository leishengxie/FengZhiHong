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

private slots:
    void on_btnAdd_clicked();

    void on_btnSub_clicked();

    void on_btnSave_clicked();

private:
    Ui::CDailyScheduleEditor *ui;
};

#endif // DAILYSCHEDULEEDITOR_H
