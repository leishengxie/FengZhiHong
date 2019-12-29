#include "DairyTagListModel.h"


CDairyTagListModel::CDairyTagListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    loadSysDefaultTag();
}

int CDairyTagListModel::rowCount(const QModelIndex & parent) const
{
    return m_lstDairyTag.count();
}

QVariant CDairyTagListModel::data(const QModelIndex & index, int role) const
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

QStringList CDairyTagListModel::listDairyTagNames() const
{
    QStringList strlistDairyTagNames;
    foreach (T_DairyTagItem dairyTag, m_lstDairyTag)
    {
        strlistDairyTagNames.append(dairyTag.strTagName);
    }
}

QStringList CDairyTagListModel::listSysDefaultDairyTagNames()
{
    return {"普通日记", "心得体会", "摘抄", "工作笔记"};
}

void CDairyTagListModel::loadSysDefaultTag()
{
    m_lstDairyTag.append(T_DairyTagItem("全部日记"));
    QStringList strlstSysDairyTagNames = listSysDefaultDairyTagNames();
    foreach (QString dairyTagName, strlstSysDairyTagNames)
    {
        m_lstDairyTag.append(T_DairyTagItem(dairyTagName));
    }
}

void CDairyTagListModel::loadCustomDairyTag(const QStringList & strlstTagName)
{
    foreach (QString dairyTag, strlstTagName)
    {
        m_lstDairyTag.append(T_DairyTagItem(dairyTag));
    }

}

void CDairyTagListModel::loadDiaryList(const QList<CDairy> & lstDairy)
{
    if (m_lstDairyTag.isEmpty())
    {
        return;
    }

    m_lstDairyTag[0].nNum = lstDairy.size();
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
    emit dataChanged(index(0), index(m_lstDairyTag.size()));
}
