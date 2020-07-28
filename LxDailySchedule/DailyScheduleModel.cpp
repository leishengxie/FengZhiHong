#include "DailyScheduleModel.h"
#include <QTime>
#define SCHEDULE_TIEM_FORMAT    "hh:mm"

CDailyScheduleModel::CDailyScheduleModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    m_strlstHeader.clear();
    m_strlstHeader << "起止时间" << "内容" << "是否启动闹钟";
}

int CDailyScheduleModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_lstScheduleItem.count();
}

int CDailyScheduleModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_strlstHeader.size();
}

QVariant CDailyScheduleModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstScheduleItem.count())
    {
        return QVariant();
    }

    T_ScheduleItem tScheduleItem = m_lstScheduleItem.at(index.row());

    if (role == Qt::EditRole)
    {
        if (index.column() == 1)
        {
            return tScheduleItem.strContent;
        }
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    QVariant variant;
    variant.setValue(tScheduleItem);
    return variant;

}

QVariant CDailyScheduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(role == Qt::TextAlignmentRole)
    {
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if(orientation == Qt::Horizontal)
    {
        return m_strlstHeader.at(section);
    }

    return QAbstractTableModel::headerData(section,orientation,role);

    //    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
    //            return m_header[section];
    //        return QAbstractTableModel::headerData(section,orientation,role);

}

Qt::ItemFlags CDailyScheduleModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    //    ItemIsSelectable = 1,
    //    ItemIsEditable = 2,
    //    ItemIsDragEnabled = 4,
    //    ItemIsDropEnabled = 8,
    //    ItemIsUserCheckable = 16,
    //    ItemIsEnabled = 32,
    if (index.column() == 0 || index.column() == 1)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable ;
    }
    else if (index.column() == 2)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable; //| Qt::ItemIsSelectable
    }

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return QAbstractTableModel::flags(index);
    //Qt::ItemFlags flag = QAbstractTableModel::flags(index);

    //return  flag;
}

void CDailyScheduleModel::setStartEndTimeData(const QModelIndex &index, const QString & strStartTime, const QString & strEndTime)
{
//    T_ScheduleItem tScheduleItem = m_lstScheduleItem.at(index.row());
//    tScheduleItem.strStartTime = strStartTime;
//    tScheduleItem.strEndTime = strEndTiem;
//    setData(index, QVariant::fromValue(tScheduleItem));

    int nRow = index.row();
    //T_ScheduleItem tScheduleItem = m_lstScheduleItem.at(index.row());
    m_lstScheduleItem[nRow].strStartTime = strStartTime;
    m_lstScheduleItem[nRow].strEndTime = strEndTime;
    emit dataChanged(index, index);
}

bool CDailyScheduleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
            return false;
    }
        int nColumn = index.column();
        T_ScheduleItem tScheduleItem = m_lstScheduleItem.at(index.row());
        switch (role)
        {
        case Qt::DisplayRole:
        {
//            if (nColumn == File_PATH_COLUMN)
//            {
//                tScheduleItem.strFilePath = value.toString();

//                m_recordList.replace(index.row(), tScheduleItem);
//                emit dataChanged(index, index);
//                return true;
//            }
        }
        case Qt::CheckStateRole:
        case Qt::EditRole:
        {
            if (nColumn == 2)
            {
                tScheduleItem.bUseAlarmClock = value.toBool();

                m_lstScheduleItem.replace(index.row(), tScheduleItem);
                emit dataChanged(index, index);
                return true;
            }
            else if (nColumn == 1)
            {
                tScheduleItem.strContent = value.toString();
                m_lstScheduleItem.replace(index.row(), tScheduleItem);
                emit dataChanged(index, index);
                return true;
            }
        }
        default:
            return false;
        }
        return false;
    //return QAbstractTableModel::setData(index, value, role);
}

void CDailyScheduleModel::addDefaultScheduleItem()
{
    T_ScheduleItem tScheduleItem;
    QTime timeStart(7, 45);
    QTime timeEnd;
    if (!m_lstScheduleItem.isEmpty())
    {
        timeStart = QTime::fromString(m_lstScheduleItem.last().strEndTime, SCHEDULE_TIEM_FORMAT);
    }
    timeEnd = timeStart.addSecs(30 * 60);
    tScheduleItem.strStartTime = timeStart.toString(SCHEDULE_TIEM_FORMAT);
    tScheduleItem.strEndTime = timeEnd.toString(SCHEDULE_TIEM_FORMAT);
    beginInsertRows(QModelIndex(), m_lstScheduleItem.size(), m_lstScheduleItem.size());
    m_lstScheduleItem.append(tScheduleItem);
    endInsertRows();

}

void CDailyScheduleModel::setListJoke(const QList<T_ScheduleItem> & lstScheduleItem)
{
    beginResetModel();
    m_lstScheduleItem = lstScheduleItem;
    endResetModel();
}

void CDailyScheduleModel::appendListJoke(const QList<T_ScheduleItem> &lstScheduleItem)
{
    if (lstScheduleItem.isEmpty())
    {
        return;
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + lstScheduleItem.count() - 1);
    m_lstScheduleItem.append(lstScheduleItem);
    endInsertRows();
}

void CDailyScheduleModel::clear()
{
    beginResetModel();
    m_lstScheduleItem.clear();
    endResetModel();
}

