#include "DairyTagListModel.h"

CDairyTagListModel::CDairyTagListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    insetInnerTag();
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

void CDairyTagListModel::insetInnerTag()
{
    m_lstDairyTag.append(T_DairyTagItem("全部日记", 0));
    m_lstDairyTag.append(T_DairyTagItem("普通日记", 0));
    m_lstDairyTag.append(T_DairyTagItem("心得体会", 0));
    m_lstDairyTag.append(T_DairyTagItem("摘抄", 0));
    m_lstDairyTag.append(T_DairyTagItem("工作笔记", 0));
}
