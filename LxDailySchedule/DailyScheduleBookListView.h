#ifndef CDAILYSCHEDULEBOOKLISTVIEW_H
#define CDAILYSCHEDULEBOOKLISTVIEW_H

#include "DailyScheduleBookModel.h"
#include <QListView>

class QMenu;

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
    void sigDailyScheduleClicked(const T_DailySchedule & book);
    void sigDailyScheduleEdit(const T_DailySchedule & book);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void paintEvent(QPaintEvent *e);

private slots:
    void onListViewClicked(const QModelIndex &index);
    void slot_edit();
    void slot_delete();

private:
    CDailyScheduleBookModel* m_pDailyScheduleBookModel;
    QMenu *m_menu;

};

#endif // CDAILYSCHEDULEBOOKLISTVIEW_H
