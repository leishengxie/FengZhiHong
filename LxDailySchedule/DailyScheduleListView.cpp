#include "DailyScheduleListView.h"
#include "DailyScheduleListDelegate.h"
#include "DailyScheduleListModel.h"
#include <QPainter>

CDailyScheduleListView::CDailyScheduleListView(QWidget *parent)
    : QListView(parent)
{
    m_pDailyScheduleListModel = new CDailyScheduleListModel(this);
    CDailyScheduleListDelegate* pDelegate = new CDailyScheduleListDelegate;
    setModel(m_pDailyScheduleListModel);
    setItemDelegate(pDelegate);

    connect(m_pDailyScheduleListModel, SIGNAL(sigCurScheduleChanged(QString))
            , this, SIGNAL(sigCurScheduleChanged(QString)));
}

void CDailyScheduleListView::loadDailySchedule(const T_DailySchedule &tDailySchedule)
{
    m_pDailyScheduleListModel->setDailySchedule(tDailySchedule.lstScheduleItem);
}

void CDailyScheduleListView::paintEvent(QPaintEvent *e)
{
    if (m_pDailyScheduleListModel->rowCount() > 0)
    {
        return QListView::paintEvent(e);
    }

    QPainter painter(viewport());
    painter.drawText(rect(), Qt::AlignCenter, "请选择一个日作息时间表");
}
