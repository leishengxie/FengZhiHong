#ifndef CDAILYSCHEDULEBOOKMODEL_H
#define CDAILYSCHEDULEBOOKMODEL_H

#include "DailyScheduleModel.h"
#include <QAbstractListModel>

struct T_DailyScheduleBook
{
    QString strBookName;
    QString strCreateDateTime;
    QList<T_ScheduleItem> lstScheduleItem;
    T_DailyScheduleBook()
    {

    }
    T_DailyScheduleBook(const QString & strBookName
                        , const QString & strCreateDateTime
                        , const QList<T_ScheduleItem> & lstScheduleItem = QList<T_ScheduleItem>())
        : strBookName(strBookName)
        , strCreateDateTime(strCreateDateTime)
        , lstScheduleItem(lstScheduleItem)
    {

    }
};
Q_DECLARE_METATYPE(T_DailyScheduleBook)

class CDailyScheduleBookModel : public QAbstractListModel
{
public:
    explicit CDailyScheduleBookModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    T_DailyScheduleBook bookData(const QModelIndex& index);
signals:

private:
    QList<T_DailyScheduleBook> m_lstDailyScheduleBook;
};

#endif // CDAILYSCHEDULEBOOKMODEL_H
