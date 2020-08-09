#ifndef CDAILYSCHEDULEBOOKMODEL_H
#define CDAILYSCHEDULEBOOKMODEL_H

#include "DailyScheduleModel.h"
#include <QAbstractListModel>

struct T_DailySchedule
{
    int id;
    QString strScheduleName;
    QString strCreateDateTime;
    QList<T_ScheduleItem> lstScheduleItem;
    T_DailySchedule()
        : id(-1)
    {

    }
    T_DailySchedule(const QString & strScheduleName
                        , const QString & strCreateDateTime
                        , const QList<T_ScheduleItem> & lstScheduleItem = QList<T_ScheduleItem>())
        : id(-1)
        , strScheduleName(strScheduleName)
        , strCreateDateTime(strCreateDateTime)
        , lstScheduleItem(lstScheduleItem)
    {

    }

    bool isInvaild() const
    {
        return -1 == id;
    }

    bool isNew() const
    {
        return -1 == id;
    }

    bool operator ==(const T_DailySchedule & rhs)
    {
        //return id == rhs.id;
        return strScheduleName == rhs.strScheduleName;
    }


    // 序列化ScheduleItemList
    QByteArray serializaScheduleItemList() const
    {
        QByteArray byteArray;
        QDataStream out(&byteArray, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        out << lstScheduleItem;
        return byteArray;
    }


    // 反序列化ScheduleItemList
    void deserializationScheduleItemList(const QByteArray & byteArray)
    {
        lstScheduleItem.clear();
        QByteArray byteArrayTemp = byteArray;
        QDataStream in(&byteArrayTemp, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_6);
        in >> lstScheduleItem;
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

    void saveDailySchedule(const T_DailySchedule & tDailySchedule);

    void setDailyScheduleList(const QList<T_DailySchedule> & lstDailySchedule);
signals:

private:
    // 作息时间表列表
    QList<T_DailySchedule> m_lstDailySchedule;
};

#endif // CDAILYSCHEDULEBOOKMODEL_H
