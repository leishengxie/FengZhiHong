#include "DairyStatisticsModel.h"



CDairyStatisticsModel::CDairyStatisticsModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int CDairyStatisticsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_lstDairy.count();
}

QVariant CDairyStatisticsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstDairy.count())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    T_Dairy dairy = m_lstDairy.at(index.row());
    QVariant variant;
    variant.setValue(dairy);
    return variant;

}

void CDairyStatisticsModel::showDairyStatistics(const QList<T_Dairy> & lstDairy)
{
    beginResetModel();
    m_lstDairy = lstDairy;

    endResetModel();
}


