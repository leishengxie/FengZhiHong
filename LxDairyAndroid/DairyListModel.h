#ifndef CDAIRYLISTMODEL_H
#define CDAIRYLISTMODEL_H

#include "Dairy.h"
#include <QAbstractListModel>

class CDairyListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int curIndex READ curIndex WRITE setCurIndex NOTIFY curIndexChanged)

public:
    enum E_DairyRole {
        ED_Did,
        ED_title,
        ED_Date,
        ED_Content
    };

    CDairyListModel(QObject* parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

signals:
    void curIndexChanged();

public:
    Q_INVOKABLE QVariant dataCurRow() const;

    void loadDairyList(const QList<T_Dairy> & lstDairy);

    int curIndex() const
    {
        return m_nCurIndex;
    }

    void setCurIndex(int nCurIndex)
    {
        if (nCurIndex != m_nCurIndex)
        {
            m_nCurIndex = nCurIndex;
            emit curIndexChanged();
        }
    }


private:

    // 饮品类队列
    QList<T_Dairy> m_lstDairy;

    int m_nCurIndex;

};

#endif // CDAIRYLISTMODEL_H
