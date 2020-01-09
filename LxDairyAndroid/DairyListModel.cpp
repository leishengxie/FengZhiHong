#include "DairyListModel.h"


CDairyListModel::CDairyListModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_nCurIndex(-1)
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
    else if (ED_Weather == role)
    {
        return tDairy.strWeather;
    }
    else if (ED_Tag == role)
    {
        return tDairy.strTag;
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
    roles[ED_Weather]  = "weather";
    roles[ED_Tag]  = "tag";
    roles[ED_Content]  = "content";
    return roles;
}

QVariantMap CDairyListModel::dataCurRow() const
{
    QVariantMap map;

    //return data(index(m_nCurIndex), role);
    if (m_nCurIndex < 0 || m_nCurIndex >= m_lstDairy.size())
    {
        return map;
    }
    const T_Dairy& tDairy = m_lstDairy[m_nCurIndex];
    map.insert("did", tDairy.did);
    map.insert("title", tDairy.strTitle);
    map.insert("date", tDairy.strDateTime);
    map.insert("content", tDairy.strContent);

    return map;
}

void CDairyListModel::loadDairyList(const QList<T_Dairy> &lstDairy)
{
    beginResetModel();
    m_lstDairy = lstDairy;
    endResetModel();
}



