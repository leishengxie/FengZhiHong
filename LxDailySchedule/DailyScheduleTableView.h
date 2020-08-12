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
    void slot_delete();

signals:
    void sigSelectedChanged(bool bHaveSelected);

protected:
    void contextMenuEvent(QContextMenuEvent *event);


private slots:
    void slotOrderByTime();
    void slotFixCrossItem();

    void slot_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    CDailyScheduleModel* m_pDailyScheduleModel;
    QMenu *m_menu;

};

#endif // CDAILYSCHEDULETABLEVIEW_H
