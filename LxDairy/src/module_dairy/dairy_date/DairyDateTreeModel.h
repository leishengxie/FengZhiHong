#ifndef CDAIRYDATETREEMODEL_H
#define CDAIRYDATETREEMODEL_H

#include <QAbstractItemModel>
#include <QSet>
#include <set>
#include "Dairy.h"

#define TREE_LEVEL  3

using namespace std;
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

//当使用set容器存放对象指针时，不指定set第二个参数的情况下，默认是以指针的值得大小进行排序的
//2，当需要以指定的方法进行排序的时候需要指定set的第二个参数，
//使用一个仿函数进行绑定判断条件（重载对象的小于号操作符并不能使set排序，因为存放的是指针，并不是对象本身，对象本身的时候小于号操作符是有效的）

struct T_DairyDateItem
{
    struct T_DairyDateComparator
    {
        bool operator()(const T_DairyDateItem* left, const T_DairyDateItem* right)
        {
            // 必须同一类型才具可比性，否则不让插入
            if (left->eDairyDateNodeType != right->eDairyDateNodeType)
            {
                return false;
            }

            // 升序排序
            return left->value() < right->value();
        }
    };


    E_DairyDateNodeType eDairyDateNodeType;
    int did;
    QString strYear;
    QString strMonth;
    QString strDay;
    QString strTitle;

    // QSet, 因为指针的相等直接是地址的相等，QPointer, QSharedPointer实质也是指针， 所以重写insert
    //QSet<QPointer<T_DairyDateItem>> m_setChildItems;
    // stl的set, 不提供list的转换,其实自己写简单
    set<T_DairyDateItem*, T_DairyDateComparator> m_setChildItems;

    T_DairyDateItem* m_pParentItem;

public:
    T_DairyDateItem();
    T_DairyDateItem(E_DairyDateNodeType eDairyDateNodeType);
    T_DairyDateItem(E_DairyDateNodeType eDairyDateNodeType, T_Dairy dairy);
    ~T_DairyDateItem();

    void release();

    void init();

    // 显示的文本
    QString text();

    void dairyModify(const T_Dairy & dairyBefore, const T_Dairy & dairyAfter
                     , T_DairyDateItem *&pDairyDateItem);

    void findItemById(int did, T_DairyDateItem *&pDairyDateItem);

    // QSet所需
    bool operator == (const T_DairyDateItem &right) const;
    // 要知道指针的比较是不用重载的，你也没办法重载
    //bool operator == (const T_DairyDateItem* right) const;
    uint value() const; // 提供排序
    /// STL-set need this function
    //    bool operator<(const T_DairyDateItem & right)const;

    // std set

    // 节点操作
    void deleteChild(T_DairyDateItem *child);
    void deleteChildren();
    T_DairyDateItem *find(T_DairyDateItem* tDairyDateItem);  // 返回子节点的地址
    void insert(T_DairyDateItem* tDairyDateItem);
    //bool contains(T_DairyDateItem tDairyDateItem);
    //bool contains_ex(T_DairyDateItem* tDairyDateItem); 使用指针的苦楚
    QList<T_DairyDateItem *> values();
    T_DairyDateItem* parentItem();
    int row(); //对应treeModel的行
    int column(); //对应treeModel的列



};
Q_DECLARE_METATYPE(T_DairyDateItem*)
///申明为指针，如果把成员指针变量内存的释放放在析构函数，就会很危险，因为赋值给一个局部对象时，
/// 局部对象析构会释放里面指针所指内容，model还继续用会崩溃。 如果硬要继续使用指针，当前的解决办法是
/// 手动释放，写一个函数release，调用时release才delete孩子节点


///Qt QModelIndex的理解，QModelIndex对象具备很短的生命周期，如果在使用一个若干指令操作前已经存在的
/// QModelIndex，那么应该调用QModelIndex的isValid.

///2种实现数据模型:
/// 一种是重新实现QAbstractItemModel的被动接口，包括数据呈现
/// ，另一种是复用一个通用用途的数据模型，比如QStandardItemModel 填充其数据

// 定义排序规则Qset所需
//uint qHash(const T_DairyDateItem key, uint seed = 0);

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

    // 加载所有日记
    void loadDairyList(const QList<T_Dairy> &lstDairy);
    QList<T_Dairy> dairyList() const
    {
        return m_lstDairy;
    }

    void sortDairyByTag(const QString & strTagName);

    // 日记内容改变
    void dairyModify(const T_Dairy & dairyBefore, const T_Dairy & dairyAfter);

public slots:
    void expandDairy(int did);


signals:
    void loadTodayDairyFinished(const T_Dairy &dairy);
    void requireExpand(const QModelIndex & index);
    void sortDairyByTagFinished(const QString & strTagName, const QList<T_Dairy> &lstDairy);

private:
    // 根据日志列表完成树数据类型的转换
    void convertDiaryListToTree(const QList<T_Dairy> &lstDairy);
    void addDairyToTree(T_Dairy dairy);

private:
    QList<T_Dairy> m_lstDairy;   // 原始结构

    T_DairyDateItem* m_pDairyDateItemRoot;  // 树结构
};

#endif // CDAIRYDATETREEMODEL_H
