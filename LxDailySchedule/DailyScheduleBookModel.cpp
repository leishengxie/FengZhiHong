#include "DailyScheduleBookModel.h"
#include <QDateTime>
#include <QPixmap>

CDailyScheduleBookModel::CDailyScheduleBookModel(QObject *parent)
    : QAbstractListModel(parent)
{
//    QList<T_ScheduleItem> lstScheduleItem;
//    lstScheduleItem << T_ScheduleItem() << T_ScheduleItem();

//    m_lstDailyScheduleBook << T_DailyScheduleBook("123", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), lstScheduleItem)
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
//    << T_DailyScheduleBook("456", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

}

int CDailyScheduleBookModel::rowCount(const QModelIndex &parent) const
{
    return m_lstDailySchedule.count();
}

QVariant CDailyScheduleBookModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstDailySchedule.count())
    {
        return QVariant();
    }

    T_DailySchedule tDailySchedule = m_lstDailySchedule.at(index.row());
    if(role == Qt::DecorationRole)
    {
        return QPixmap(":/img/tool_img/maple_leaf_book.png");
    }
    else if(role == Qt::DisplayRole)
    {
        return tDailySchedule.strScheduleName;
    }
    else if (role == Qt::ToolTipRole)
    {
        return tDailySchedule.strCreateDateTime;
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else if (role == Qt::SizeHintRole)
    {
        //return QSize(64,64);
    }

    return QVariant();

//    QVariant variant;
//    variant.setValue(tDailyScheduleBook);
    //    return variant;
}

T_DailySchedule CDailyScheduleBookModel::dailyScheduleData(const QModelIndex &index)
{
    if (!index.isValid())
    {
        return T_DailySchedule();
    }

    if (index.row() < 0 || index.row() >= m_lstDailySchedule.count())
    {
        return T_DailySchedule();
    }

    T_DailySchedule tDailySchedule = m_lstDailySchedule.at(index.row());
    return tDailySchedule;
}

void CDailyScheduleBookModel::saveDailySchedule(const T_DailySchedule &tDailySchedule)
{
//    if (tDailySchedule.isInvaild())
//    {
//        return;
//    }

    // 如果是新的则添加
    if (!m_lstDailySchedule.contains(tDailySchedule))
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_lstDailySchedule.append(tDailySchedule);
        endInsertRows();
        return;
    }

    // 这里因为没有数据库 id，直接根据name判定
    for (int i = 0; 0 < m_lstDailySchedule.count(); ++i)
    {
        if (m_lstDailySchedule.at(i).strScheduleName == tDailySchedule.strScheduleName)
        {
            m_lstDailySchedule.replace(i, tDailySchedule);
            emit dataChanged(index(i), index(i));
            break;
        }
    }

}

void CDailyScheduleBookModel::setDailyScheduleList(const QList<T_DailySchedule> &lstDailySchedule)
{
    //This also means that the current item and any selected items will become invalid.
    beginResetModel();
    m_lstDailySchedule = lstDailySchedule;
    endResetModel();
}
