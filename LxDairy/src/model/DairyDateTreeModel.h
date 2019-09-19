#ifndef CDAIRYDATETREEMODEL_H
#define CDAIRYDATETREEMODEL_H

#include <QAbstractItemModel>
#include <QSet>
#include "Dairy.h"

#define TREE_LEVEL  3

// 节点类型
enum E_DairyDateNodeType
{
    ED_Root,
    ED_Year,
    ED_Month,
    ED_Day,
    ED_Invalid
};

//QSet和STL的set是有本质区别的，虽然它们的名字很像，前者是基于哈希表的，后者是红黑树的变种
//QSet是基于哈希算法的，这就要求自定义的结构体Type必须提供：
//1. bool operator == (const Type &b) const
//2. 一个全局的uint qHash(Type key)函数
struct T_DairyDateItem
{
    E_DairyDateNodeType eDairyDateNodeType;
    int did;
    QString strYear;
    QString strMonth;
    QString strDay;
    QString strTitle;
    QSet<T_DairyDateItem*> m_setChildItems;
    T_DairyDateItem *m_pParentItem;

    T_DairyDateItem();
    T_DairyDateItem(E_DairyDateNodeType eDairyDateNodeType);
    T_DairyDateItem(E_DairyDateNodeType eDairyDateNodeType, CDairy dairy);

    void init();

    // 显示的文本
    QString text();

    // QSet所需
    bool operator == (const T_DairyDateItem &right) const;
    uint value() const; // 提供排序
    /// STL-set need this function
    //    bool operator<(const T_DairyDateItem & right)const;

    // 节点操作
    void erase(T_DairyDateItem *child);
    void eraseAll();
    T_DairyDateItem *find(T_DairyDateItem* tDairyDateItem);
    void insert(T_DairyDateItem* tDairyDateItem);
    bool contains(T_DairyDateItem* tDairyDateItem);
    QList<T_DairyDateItem*> values();
    T_DairyDateItem* parentItem();
    int row(); //对应treeModel的行
    int column(); //对应treeModel的列


};
Q_DECLARE_METATYPE(T_DairyDateItem)

uint qHash(const T_DairyDateItem* key, uint seed = 0);

class CDairyDateTreeModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    CDairyDateTreeModel(QObject *parent);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    bool hasChildren(const QModelIndex &parent) const;

    void loadDairy();
    // 根据日志列表整理成树
    void createDateTree(QList<CDairy> m_lstDairy);

    void insetDairy(CDairy dairy);

signals:
    void loadTodayDairyFinished(const CDairy &dairy);

private:
    T_DairyDateItem* m_pDairyDateItemRoot;
};

#endif // CDAIRYDATETREEMODEL_H
