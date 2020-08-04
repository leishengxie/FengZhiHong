#ifndef CDAILYSCHEDULEBOOKMODEL_H
#define CDAILYSCHEDULEBOOKMODEL_H

#include "DailyScheduleModel.h"
#include <QAbstractListModel>

struct T_DailySchedule
{
    QString strScheduleName;
    QString strCreateDateTime;
    QList<T_ScheduleItem> lstScheduleItem;
    T_DailySchedule()
    {

    }
    T_DailySchedule(const QString & strScheduleName
                        , const QString & strCreateDateTime
                        , const QList<T_ScheduleItem> & lstScheduleItem = QList<T_ScheduleItem>())
        : strScheduleName(strScheduleName)
        , strCreateDateTime(strCreateDateTime)
        , lstScheduleItem(lstScheduleItem)
    {

    }
};
Q_DECLARE_METATYPE(T_DailySchedule)


struct T_DailyScheduleBook
{
    QString strBookName;
    QString strCreateDateTime;
    QList<T_DailySchedule> lstDailySchedule;
};

///
/// \brief The CDailyScheduleBookModel class 作息时间簿model
///
class CDailyScheduleBookModel : public QAbstractListModel
{
public:
    explicit CDailyScheduleBookModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    T_DailySchedule bookData(const QModelIndex& index);
signals:

private:
    // 作息时间表列表
    QList<T_DailySchedule> m_lstDailySchedule;
};

#endif // CDAILYSCHEDULEBOOKMODEL_H
