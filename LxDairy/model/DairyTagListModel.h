#ifndef CDAIRYTAGLISTMODEL_H
#define CDAIRYTAGLISTMODEL_H

#include <QAbstractListModel>


struct T_DairyTagItem
{
    QString strTagName;
    int nNum;

    T_DairyTagItem()
        : nNum(0)
    {

    }

    T_DairyTagItem(QString strTagName, int nNum)
        : strTagName(strTagName)
        , nNum(nNum)
    {

    }
};
Q_DECLARE_METATYPE(T_DairyTagItem)

///下面几个类的选择
//类QabstractItemModel，QabstractListModel，QAbstractTableModel不保存数据，用户需要从这些类派生出子类，并在子类中定义某种数据结构来保存数据。
//与此不同，类QStandardItemModel负责保存数据，每个数据项被表示为类QStandardItem的对象。
//QStandardItem用来保存一个数据项，再使用QStandardItemModel将这些数据项组织起来，形成列表、表格或者树，以供其他视图类显示。

//如果你需要一个model，该model用于view的item。比如QML List View的元素或者C++ widgets的QListView，QTableView，
//此时你应该考虑子类化QAbstractListModel或QAbstractTableModel而不是类QabstractItemModel。

//如果数据项固定而且不用于QML用QStandarItemModel

class CDairyTagListModel : public QAbstractListModel
{
        Q_OBJECT
public:
    CDairyTagListModel(QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;


private:
    void insetInnerTag();

private:
    QList<T_DairyTagItem> m_lstDairyTag;
};

#endif // CDAIRYTAGLISTMODEL_H
