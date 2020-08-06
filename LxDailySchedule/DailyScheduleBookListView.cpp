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

// 如果有后台应该向后台请求保存数据
void CDailyScheduleBookListView::slotReqSaveDailySchedule(const T_DailySchedule &tDailySchedule)
{
    saveDailySchedule(tDailySchedule);
}

void CDailyScheduleBookListView::saveDailySchedule(const T_DailySchedule &tDailySchedule)
{
    m_pDailyScheduleBookModel->saveDailySchedule(tDailySchedule);
}

void CDailyScheduleBookListView::paintEvent(QPaintEvent *e)
{
    int row = m_pDailyScheduleBookModel->rowCount();
    if (row > 0)
    {
        return QListView::paintEvent(e);
    }

    QPainter painter(viewport());
    QTextOption textOption(Qt::AlignLeft | Qt::AlignVCenter);
    textOption.setWrapMode(QTextOption::WordWrap);//设置换行,在单独的QWidget能实现,这里没有生效，估计是不让修改
    painter.save();
    painter.setPen(QColor(0, 160, 230));
    painter.drawText(rect(), "请创建日作息时间表", textOption);
    painter.restore();
}

void CDailyScheduleBookListView::onListViewClicked(const QModelIndex &index)
{
    emit sigBookClicked(m_pDailyScheduleBookModel->bookData(index));
}

