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

T_DailySchedule CDailyScheduleBookModel::bookData(const QModelIndex &index)
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
