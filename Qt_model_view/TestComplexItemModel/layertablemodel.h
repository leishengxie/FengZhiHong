#ifndef LAYERLISTMODEL_H
#define LAYERLISTMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QList>
#include <QPixmap>
#include <QImage>
#include <QIcon>
#include <QDebug>
#include <QItemSelectionModel>

class LayerTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    LayerTableModel(QObject *parent = 0);
    ~LayerTableModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void deleteItem(int index);
    void addItem(const QString &layerName, QImage thumbnail, bool isShow = true);
    void refreshModel();
    QModelIndex selecttedIndex(int row);

    void setSelecttedRow(int row);
    int getSelecttedRow() const;


public slots:
    void changeLayerVisibility(const QModelIndex&);

private:
    struct LayerItem
    {
        QString layerName;
        QImage thumbnail;
        float transparence;
        bool isShow;
    };
    QList<LayerItem> layerList;

    int selectedRow;

};

#endif // LAYERLISTMODEL_H
