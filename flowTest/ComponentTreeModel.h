#ifndef CDAIRYDATETREEMODEL_H
#define CDAIRYDATETREEMODEL_H

#include <QAbstractItemModel>
#include "Component.h"

class CComponentTreeModelPrivate;

class CComponentTreeModel: public QAbstractItemModel
{
    Q_OBJECT
public:

    enum E_ComponentRoles
    {
        EC_ComponentIconRole = Qt::DecorationRole,
        EC_ComponentNameRole = Qt::UserRole + 1,
    };

    CComponentTreeModel(QObject *parent);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    bool hasChildren(const QModelIndex &parent) const;

    // CComponentTreeModel specific API
//    void addContainer(const QString & strContainerParentName, const QString & strContainerName);
//    void addComponent(const QString & strContainerParentName, const CComponent & component);
//    void removeContainer(const QString & strContainerName);
    CComponent component(const QModelIndex &index) const;
    bool isContainer(const QModelIndex &index) const;


private:
    Q_DECLARE_PRIVATE(CComponentTreeModel)
    Q_DISABLE_COPY(CComponentTreeModel)

};

#endif // CDAIRYDATETREEMODEL_H
