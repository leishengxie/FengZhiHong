#include "DailyScheduleBookListView.h"
#include <QPainter>


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

void CDailyScheduleBookListView::paintEvent(QPaintEvent *e)
{
    int row = m_pDailyScheduleBookModel->rowCount();
    if (row > 0)
    {
        return QListView::paintEvent(e);
    }

    QPainter painter(viewport());
    painter.drawText(rect(), Qt::AlignCenter, "请创建日作息时间表");
}

void CDailyScheduleBookListView::onListViewClicked(const QModelIndex &index)
{
    emit sigBookClicked(m_pDailyScheduleBookModel->bookData(index));
}
