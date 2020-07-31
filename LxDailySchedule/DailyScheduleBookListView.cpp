#include "DailyScheduleBookListView.h"



CDailyScheduleBookListView::CDailyScheduleBookListView(QWidget *parent)
    : QListView(parent)
{
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setFlow(QListView::LeftToRight);
    setWrapping(false);
    //setSpacing(5);

    m_pDailyScheduleBookModel = new CDailyScheduleBookModel(this);
    setModel(m_pDailyScheduleBookModel);
    //QListView
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onListViewClicked(QModelIndex)));
}

void CDailyScheduleBookListView::onListViewClicked(const QModelIndex &index)
{
    emit sigBookClicked(m_pDailyScheduleBookModel->bookData(index));
}
