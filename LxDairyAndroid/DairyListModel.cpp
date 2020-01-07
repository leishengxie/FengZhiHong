#include "DairyListModel.h"


CDairyListModel::CDairyListModel(QObject* parent)
    : QAbstractListModel(parent)
{


}


int CDairyListModel::rowCount(const QModelIndex& parent) const
{
    return m_lstDairy.count();
}

QVariant CDairyListModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() > m_lstDairy.count())
    {
        return QVariant();
    }

    const T_Dairy& tDairy = m_lstDairy[index.row()];

    if (ED_Did == role)
    {
        return tDairy.did;
    }
    else if (ED_title == role)
    {
        return tDairy.strTitle;
    }
    else if (ED_Date == role)
    {
        return tDairy.strDateTime;
    }
    else if (ED_Content == role)
    {
        return tDairy.strContent;
    }
    return QVariant();
}


QHash<int, QByteArray> CDairyListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ED_Did]  = "did";
    roles[ED_title]  = "title";
    roles[ED_Date]  = "date";
    roles[ED_Content]  = "content";
    return roles;
}

void CDairyListModel::loadDairyList(const QList<T_Dairy> &lstDairy)
{
    beginResetModel();
    m_lstDairy = lstDairy;
    endResetModel();
}



