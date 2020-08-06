#ifndef CDAILYSCHEDULETABLEVIEW_H
#define CDAILYSCHEDULETABLEVIEW_H

#include "DailyScheduleBookModel.h"
#include <QTableView>

class CDailyScheduleModel;
class QMenu;

class CDailyScheduleTableView : public QTableView
{
    Q_OBJECT
public:
    explicit CDailyScheduleTableView(QWidget *parent = nullptr);

    void addItem();
    QList<T_ScheduleItem> scheduleItemList();
    void clear();

public slots:
    void slotLoadDailySchedule(const T_DailySchedule & tDailySchedule);

signals:

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void paintEvent(QPaintEvent *e);

private slots:
    void slotOrderByTime();
    void slotFixCrossItem();

private:
    CDailyScheduleModel* m_pDailyScheduleModel;
    QMenu *m_menu;

};

#endif // CDAILYSCHEDULETABLEVIEW_H
