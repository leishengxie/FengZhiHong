#ifndef DAILYSCHEDULEWIDGET_H
#define DAILYSCHEDULEWIDGET_H

#include <QWidget>

namespace Ui {
class CDailyScheduleWidget;
}

class CDailyScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDailyScheduleWidget(QWidget *parent = 0);
    ~CDailyScheduleWidget();

private slots:
    void on_btnAdd_clicked();

    void on_btnSub_clicked();

private:
    Ui::CDailyScheduleWidget *ui;
};

#endif // DAILYSCHEDULEWIDGET_H
