#ifndef DAILYSCHEDULEWIDGET_H
#define DAILYSCHEDULEWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include "DailyScheduleBookModel.h"

namespace Ui {
class CDailyScheduleWidget;
}

class CMiniWidget;
class CDailyScheduleEditor;

class CDailyScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDailyScheduleWidget(QWidget *parent = 0);
    ~CDailyScheduleWidget();

protected:
    void closeEvent(QCloseEvent *event);
    virtual void changeEvent(QEvent *event);

private slots:
    void on_btnAdd_clicked();

    void slot_sysTrayIcon_activated(QSystemTrayIcon::ActivationReason reason);


    void slotShowWindows(bool checked = false);
    void slotExitApp(bool checked = false);

    void slotLoadDailySchedule(const T_DailySchedule & tDailySchedule);


private:
    Ui::CDailyScheduleWidget *ui;
    QSystemTrayIcon* m_pSystemTrayIcon;
    CMiniWidget* m_pMiniWidget;
    CDailyScheduleEditor* m_pDailyScheduleEditor;
};

#endif // DAILYSCHEDULEWIDGET_H
