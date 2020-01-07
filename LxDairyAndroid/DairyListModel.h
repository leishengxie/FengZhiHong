#ifndef CDAIRYLISTMODEL_H
#define CDAIRYLISTMODEL_H

#include "Dairy.h"
#include <QAbstractListModel>

class CDairyListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum E_DairyRole {
        ED_title,
        ED_Date,
    };

    CDairyListModel(QObject* parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

public:
    void loadDairyList(const QList<T_Dairy> & lstDairy);


private:

    // 饮品类队列
    QList<T_Dairy> m_lstDairy;

};

#endif // CDAIRYLISTMODEL_H
