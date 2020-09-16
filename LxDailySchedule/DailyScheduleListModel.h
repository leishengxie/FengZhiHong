#ifndef CDAILYSCHEDULELISTMODEL_H
#define CDAILYSCHEDULELISTMODEL_H

#include "DailyScheduleModel.h"
#include <QAbstractListModel>

class QTimer;

class CDailyScheduleListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CDailyScheduleListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    void setDailySchedule(const QList<T_ScheduleItem> & lstScheduleItem);

signals:
    // 用于通知其他部件内容已改变，如小浮窗
    void sigCurScheduleChanged(const T_ScheduleItem & tScheduleItem);

private slots:
    void slot_timeout();

private:
    // 作息时间表列表
    QList<T_ScheduleItem> m_lstScheduleItem;
    QTimer* m_timer;

    int m_nPreItemIndex;
    int m_nCurItemIndex;  // 当前时间执行的ScheduleItem所在列表的index
};

#endif // CDAILYSCHEDULELISTMODEL_H
