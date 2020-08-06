#ifndef CDAILYSCHEDULEBOOKLISTVIEW_H
#define CDAILYSCHEDULEBOOKLISTVIEW_H

#include "DailyScheduleBookModel.h"
#include <QListView>

class CDailyScheduleBookListView : public QListView
{
    Q_OBJECT
public:
    explicit CDailyScheduleBookListView(QWidget *parent = nullptr);

    // 类似Android的列表为空提示
    //void setListEmptyText(QString strTip);
public slots:
    void slotReqSaveDailySchedule(const T_DailySchedule & tDailySchedule);

public:
    void saveDailySchedule(const T_DailySchedule & tDailySchedule);


signals:
    void sigBookClicked(const T_DailySchedule & book);

protected:
    void paintEvent(QPaintEvent *e);

private slots:
    void onListViewClicked(const QModelIndex &index);

private:
    CDailyScheduleBookModel* m_pDailyScheduleBookModel;

};

#endif // CDAILYSCHEDULEBOOKLISTVIEW_H
