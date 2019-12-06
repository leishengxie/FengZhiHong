#ifndef CCOLLECTIONMODEL_H
#define CCOLLECTIONMODEL_H

#include <QAbstractListModel>

struct T_CollectionItem
{
    QString strName;
    QString strIconPath;
    QString strTip;

    T_CollectionItem()
    {

    }

    T_CollectionItem(const QString & strName, const QString & strIconPath, const QString & strTip)
        : strName(strName)
        , strIconPath(strIconPath)
        , strTip(strTip)
    {

    }
};
Q_DECLARE_METATYPE(T_CollectionItem)



class CCollectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CCollectionModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;


private:
    // 标签数据
    QList<T_CollectionItem> m_lstCollectionItem;
};
#endif // CCOLLECTIONMODEL_H
