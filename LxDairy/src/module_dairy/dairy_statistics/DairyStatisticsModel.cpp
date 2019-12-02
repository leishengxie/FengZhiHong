#include "DairyStatisticsModel.h"



CDairyStatisticsModel::CDairyStatisticsModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int CDairyStatisticsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_lstDairyStatistics.count();
}

QVariant CDairyStatisticsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstDairyStatistics.count())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    T_DairyStatisticsItem tDairyStatisticsItem = m_lstDairyStatistics.at(index.row());
    QVariant variant;
    variant.setValue(tDairyStatisticsItem);
    return variant;

}

void CDairyStatisticsModel::showDairyStatistics(const QList<CDairy> & lstDairy)
{
    beginResetModel();
    m_lstDairyStatistics.clear();
    foreach (CDairy dairy, lstDairy)
    {
        m_lstDairyStatistics.append(T_DairyStatisticsItem(dairy.getDid()
                                                          , dairy.getDateTime().left(10)
                                                          , dairy.getTitle() + " - " + dairy.getContent()));
    }
    endResetModel();
}


