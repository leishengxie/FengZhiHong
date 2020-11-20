#include "DailyScheduleListModel.h"
#include <QTimer>

CDailyScheduleListModel::CDailyScheduleListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_nPreItemIndex(-1)
    , m_nCurItemIndex(-1)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
    m_timer->start(1000);
}

int CDailyScheduleListModel::rowCount(const QModelIndex &parent) const
{
    return m_lstScheduleItem.count();
}

QVariant CDailyScheduleListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstScheduleItem.count())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    T_ScheduleItem tScheduleItem = m_lstScheduleItem.at(index.row());
    QVariant variant;
    variant.setValue(tScheduleItem);
    return variant;
}

void CDailyScheduleListModel::setDailySchedule(const QList<T_ScheduleItem> &lstScheduleItem)
{
    beginResetModel();
    m_lstScheduleItem = lstScheduleItem;
    endResetModel();

    m_nCurItemIndex = -1;
    m_nPreItemIndex = -1;
    emit sigCurScheduleChanged(T_ScheduleItem("无"));
}

void CDailyScheduleListModel::slot_timeout()
{
    if (m_lstScheduleItem.isEmpty())
    {
        return;
    }
    for(int i = 0; i < m_lstScheduleItem.count(); ++i)
    {
        if(m_lstScheduleItem.at(i).isContainsNow())
        {
            m_nCurItemIndex = i;
            break;
        }
    }
    if (m_nCurItemIndex != m_nPreItemIndex)
    {
        emit sigCurScheduleChanged(m_lstScheduleItem.at(m_nCurItemIndex));
        m_nPreItemIndex = m_nCurItemIndex;
    }
}
