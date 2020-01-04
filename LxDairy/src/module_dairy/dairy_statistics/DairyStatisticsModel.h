#ifndef CDAIRYSTATISTICSMODEL_H
#define CDAIRYSTATISTICSMODEL_H

#include <QAbstractListModel>
#include "Dairy.h"

class CDairyStatisticsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CDairyStatisticsModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QList<T_Dairy> dairList()
    {
        return m_lstDairy;
    }

    void showDairyStatistics(const QList<T_Dairy> &lstDairy);

private:
    void loadDairyTag();

private:
    // 标签数据
    QList<T_Dairy> m_lstDairy;
};




#endif // CDAIRYSTATISTICSMODEL_H
