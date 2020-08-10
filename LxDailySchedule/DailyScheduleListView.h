#ifndef CDAILYSCHEDULELISTVIEW_H
#define CDAILYSCHEDULELISTVIEW_H

#include <QListView>
#include "DailyScheduleBookModel.h"

class CDailyScheduleListModel;

class CDailyScheduleListView : public QListView
{
    Q_OBJECT
public:
    explicit CDailyScheduleListView(QWidget *parent = nullptr);

    void loadDailySchedule(const T_DailySchedule & tDailySchedule);

signals:
    void sigCurScheduleChanged(const QString & strContent);

protected:
    void paintEvent(QPaintEvent *e);

private:
    CDailyScheduleListModel* m_pDailyScheduleListModel;

};

#endif // CDAILYSCHEDULELISTVIEW_H
