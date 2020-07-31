#ifndef CDAILYSCHEDULEBOOKLISTVIEW_H
#define CDAILYSCHEDULEBOOKLISTVIEW_H

#include "DailyScheduleBookModel.h"
#include <QListView>

class CDailyScheduleBookListView : public QListView
{
    Q_OBJECT
public:
    explicit CDailyScheduleBookListView(QWidget *parent = nullptr);


signals:
    void sigBookClicked(const T_DailyScheduleBook & book);

private slots:
    void onListViewClicked(const QModelIndex &index);

private:
    CDailyScheduleBookModel* m_pDailyScheduleBookModel;

};

#endif // CDAILYSCHEDULEBOOKLISTVIEW_H
