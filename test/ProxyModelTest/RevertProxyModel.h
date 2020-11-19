#ifndef REVERTPROXYMODEL_H
#define REVERTPROXYMODEL_H


#include <QAbstractProxyModel>
#include <QVector>
class RevertProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    RevertProxyModel(QObject *parent = 0);
    QModelIndex mapToSource(const QModelIndex &proxy_index) const;
    QModelIndex mapFromSource(const QModelIndex &source_index) const;
    QModelIndex index(int row,int column,const QModelIndex &proxy_index) const;
    QModelIndex parent(const QModelIndex & proxy_child) const;
    int rowCount(const QModelIndex &proxy_parent) const;
    int columnCount(const QModelIndex &proxy_parent) const;
private:
    int register_index(const QModelIndex &source_index) const;
    mutable QVector<QModelIndex> vector; //为使5个重载的常量函数能够修改vector，必须mutable
};
//在此没有重载data()函数，因为QAbstractProxyModel已经实现了该函数

/**
    QVariant QAbstractProxyModel::data(const QModelIndex &proxyIndex,
                                       int role) const{
        Q_D(const QAbstractProxyModel);
        return d->model->data(mapToSource(proxyIndex), role);
    }
**/

#endif // REVERTPROXYMODEL_H
