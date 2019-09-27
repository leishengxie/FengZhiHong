#include "DairyTagListModel.h"
#include "User.h"

CDairyTagListModel::CDairyTagListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadDairyTag();
}

int CDairyTagListModel::rowCount(const QModelIndex &parent) const
{
    return m_lstDairyTag.count();
}

QVariant CDairyTagListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstDairyTag.count())
    {
        return QVariant();
    }

    T_DairyTagItem tDairyTagItem = m_lstDairyTag.at(index.row());
    switch (role)
    {
    case Qt::TextColorRole:
        break;
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        break;
    case Qt::DisplayRole:
    {
        QVariant variant;
        variant.setValue(tDairyTagItem);
        return variant;
    }
    }
    //return QAbstractListModel::data(index, role);
}

void CDairyTagListModel::loadDairyTag()
{
    QStringList strlstDairyTag = CUser::getInstance()->getLstDairyTag();
    QList<CDairy> lstDairy = CUser::getInstance()->getLstDairy();

    m_lstDairyTag.append(T_DairyTagItem("全部日记", lstDairy.size()));

    foreach (QString dairyTag, strlstDairyTag)
    {
        m_lstDairyTag.append(T_DairyTagItem(dairyTag, 0));
    }
    foreach (CDairy dairy, lstDairy)
    {
        for (int i = 0; i < m_lstDairyTag.size(); ++i)
        {
            if (m_lstDairyTag[i].strTagName == dairy.getTag())
            {
                ++m_lstDairyTag[i].nNum;
            }
        }
    }
}
