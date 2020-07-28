#ifndef CDAILYSCHEDULEMODEL_H
#define CDAILYSCHEDULEMODEL_H
#include <QAbstractTableModel>

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

    QString startAndEndRime()const
    {
        return strStartTime + "-" + strEndTime;
    }
};
Q_DECLARE_METATYPE(T_ScheduleItem)


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

    QList<T_ScheduleItem> listScheduleItem()
    {
        return m_lstScheduleItem;
    }

    void setStartEndTimeData(const QModelIndex & index, const QString &strStartTime, const QString &strEndTime);
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    void addDefaultScheduleItem();
    void setListJoke(const QList<T_ScheduleItem> & lstScheduleItem);
    void appendListJoke(const QList<T_ScheduleItem> & lstScheduleItem);
    void clear();

    // 在当前行前插入行
    // 在当前行后插入行
    // 按起始时间排序
    // 按起始时间去除项之间的时间交错，会自动修改交错项的终止时间

private:


private:
    QList<T_ScheduleItem> m_lstScheduleItem;
    QStringList m_strlstHeader;
};

#endif // CDAILYSCHEDULEMODEL_H
