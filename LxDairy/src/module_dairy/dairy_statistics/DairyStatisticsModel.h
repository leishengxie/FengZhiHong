#ifndef CDAIRYSTATISTICSMODEL_H
#define CDAIRYSTATISTICSMODEL_H

#include <QAbstractListModel>
#include "Dairy.h"

struct T_DairyStatisticsItem
{
    int did;
    QString strDate;
    QString strContent;

    T_DairyStatisticsItem()
    : did(-1)
    {

    }

    T_DairyStatisticsItem(int did, QString strDate, QString strContent)
        : did(did)
        , strDate(strDate)
        , strContent(strContent)
    {

    }
};
Q_DECLARE_METATYPE(T_DairyStatisticsItem)

class CDairyStatisticsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CDairyStatisticsModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QList<T_DairyStatisticsItem> lstDairyStatistics()
    {
        return m_lstDairyStatistics;
    }

    void showDairyStatistics(const QList<CDairy> &lstDairy);

private:
    void loadDairyTag();

private:
    // 标签数据
    QList<T_DairyStatisticsItem> m_lstDairyStatistics;
};




#endif // CDAIRYSTATISTICSMODEL_H
