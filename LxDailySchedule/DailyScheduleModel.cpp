#include "DailyScheduleModel.h"
#include <QTime>
#include <list>
#define SCHEDULE_TIEM_FORMAT    "hh:mm"

///
/// \brief T_ScheduleItem::operator <
/// \param tScheduleItem
/// \return
///
bool T_ScheduleItem::operator <(const T_ScheduleItem &tScheduleItem) const
{
    QTime timeStart = QTime::fromString(strStartTime, SCHEDULE_TIEM_FORMAT);
    QTime timeStartRhs = QTime::fromString(tScheduleItem.strStartTime, SCHEDULE_TIEM_FORMAT);
    return timeStart < timeStartRhs;
}

bool T_ScheduleItem::isContainsNow() const
{
    QTime timeStart = QTime::fromString(strStartTime, SCHEDULE_TIEM_FORMAT);
    QTime timeEnd = QTime::fromString(strEndTime, SCHEDULE_TIEM_FORMAT);
    QTime timeNow = QTime::currentTime();
    return (timeStart <= timeNow) && (timeNow <= timeEnd);
}

QDataStream & operator>>(QDataStream &in, T_ScheduleItem &data)
{
    in >> data.strStartTime >> data.strEndTime >> data.strContent >> data.bUseAlarmClock;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_ScheduleItem &data)
{
    out << data.strStartTime << data.strEndTime << data.strContent << data.bUseAlarmClock;
    return out;
}




///
/// \brief CDailyScheduleModel::CDailyScheduleModel
/// \param parent
///
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
        return Qt::ItemIsEnabled| Qt::ItemIsSelectable | Qt::ItemIsEditable ;
    }
    else if (index.column() == 2)
    {
        return Qt::ItemIsEnabled| Qt::ItemIsSelectable | Qt::ItemIsUserCheckable; //| Qt::ItemIsSelectable
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

void CDailyScheduleModel::setDailySchedule(const QList<T_ScheduleItem> & lstScheduleItem)
{
    beginResetModel();
    m_lstScheduleItem = lstScheduleItem;
    endResetModel();
}

void CDailyScheduleModel::appendDailySchedule(const QList<T_ScheduleItem> &lstScheduleItem)
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

void CDailyScheduleModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_lstScheduleItem.removeAt(index.row());
    endRemoveRows();
}

void CDailyScheduleModel::orderByTime()
{
    //m_lstScheduleItem.
    std::sort(m_lstScheduleItem.begin(), m_lstScheduleItem.end());
    emit dataChanged(index(0,0), index(rowCount(), columnCount()));
}

// 按起始时间去除项之间的时间交错，会自动修改交错项的终止时间
void CDailyScheduleModel::fixCrossItem()
{
    if (m_lstScheduleItem.isEmpty() || m_lstScheduleItem.size() == 1)
    {
        return;
    }

    // 先排序
    std::sort(m_lstScheduleItem.begin(), m_lstScheduleItem.end());

    // 依次取当前项与其后一项检测是否有时间交错，有交错则把当前项的终止时间修改为后一项的起始时间
    QTime time_1st_end;
    QTime time_2nd_start;
    for (int i = 0; i < m_lstScheduleItem.size() - 1; ++i)
    {
        time_1st_end = QTime::fromString(m_lstScheduleItem.at(i).strEndTime, SCHEDULE_TIEM_FORMAT);
        time_2nd_start = QTime::fromString(m_lstScheduleItem.at(i + 1).strStartTime, SCHEDULE_TIEM_FORMAT);
        // 如果有交错
        if (time_1st_end > time_2nd_start)
        {
            m_lstScheduleItem[i].strEndTime = m_lstScheduleItem[i+1].strStartTime;
        }
    }
    emit dataChanged(index(0,0), index(rowCount(), columnCount()));
}



