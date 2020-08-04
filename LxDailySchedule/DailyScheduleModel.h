#ifndef CDAILYSCHEDULEMODEL_H
#define CDAILYSCHEDULEMODEL_H
#include <QAbstractTableModel>

///
/// \brief The T_ScheduleItem struct 时间项
///
struct T_ScheduleItem
{
    QString strStartTime;
    QString strEndTime;
    QString strContent;
    bool bUseAlarmClock;
    T_ScheduleItem()
        : strStartTime("00:00")
        , strEndTime("00:00")
        , bUseAlarmClock(false)
    {

    }


    // std::sort指针
//    bool operator() (const T_ScheduleItem & tScheduleItem)
//    {
//        return false;
//    }

    // std::sort对象
    bool operator < (const T_ScheduleItem & tScheduleItem) const;

    QString startAndEndRime()const
    {
        return strStartTime + "-" + strEndTime;
    }

    bool isContainsNow();

};
Q_DECLARE_METATYPE(T_ScheduleItem)



///
/// \brief The CDailyScheduleModel class
/// 作息时间表model
///
class CDailyScheduleModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CDailyScheduleModel(QObject* parent = 0);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;

    QList<T_ScheduleItem> scheduleItemList()
    {
        return m_lstScheduleItem;
    }

    void setStartEndTimeData(const QModelIndex & index, const QString &strStartTime, const QString &strEndTime);
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    void addDefaultScheduleItem();
    void setDailySchedule(const QList<T_ScheduleItem> & lstScheduleItem);
    void appendDailySchedule(const QList<T_ScheduleItem> & lstScheduleItem);
    void clear();

    // 在当前行前插入行
    // 在当前行后插入行
    // 按起始时间排序
    void orderByTime();
    // 按起始时间去除项之间的时间交错，会自动修改交错项的终止时间
    void fixCrossItem();

private:


private:
    QList<T_ScheduleItem> m_lstScheduleItem;
    QStringList m_strlstHeader;
};

#endif // CDAILYSCHEDULEMODEL_H
