#include "DairyDateTreeModel.h"
#include <QDateTime>
#include "User.h"

T_DairyDateItem::T_DairyDateItem()
{
    init();
}

T_DairyDateItem::T_DairyDateItem(E_DairyDateNodeType eDairyDateNodeType)
{
    init();
    this->eDairyDateNodeType = eDairyDateNodeType;
}

T_DairyDateItem::T_DairyDateItem(E_DairyDateNodeType eDairyDateNodeType, CDairy dairy)
{
    init();
    this->eDairyDateNodeType = eDairyDateNodeType;
    //QMultiMap
    //"2010-07-02 17:35:00";
    QString strDateTime = dairy.getDateTime();
    strYear = strDateTime.mid(0, 4);
    strMonth = strDateTime.mid(5, 2);
    strDay = strDateTime.mid(8, 2);
}

void T_DairyDateItem::init()
{
    eDairyDateNodeType = ED_Invalid;
    m_setChildItems.clear();
    m_pParentItem = NULL;
}

bool T_DairyDateItem::operator ==(const T_DairyDateItem &right) const
{
    // 必须同一类型才具可比性，否则不让插入
    if (eDairyDateNodeType != right.eDairyDateNodeType)
    {
        return true;
    }
    switch (eDairyDateNodeType)
    {
    case ED_Year:
        return strYear.toInt() == right.strYear.toInt();
    case ED_Month:
        return strMonth.toInt() == right.strMonth.toInt();
    case ED_Day:
        return strDay.toInt() == right.strDay.toInt();
        break;
    default:
        break;
    }
    return true;
}

uint T_DairyDateItem::value() const
{
    uint nValue = 0;
    switch (eDairyDateNodeType)
    {
    case ED_Year:
        nValue = strYear.toUInt() * 366;
        break;
    case ED_Month:
        nValue = strMonth.toUInt() * 31;
        break;
    case ED_Day:
        nValue = strDay.toUInt();
        break;
    default:
        break;
    }
    return nValue;
}

void T_DairyDateItem::erase(T_DairyDateItem *child)
{

}

void T_DairyDateItem::eraseAll()
{

}

T_DairyDateItem * T_DairyDateItem::find(T_DairyDateItem *tDairyDateItem)
{
    QSet<T_DairyDateItem*>::iterator iter = m_setChildItems.find(tDairyDateItem);
    return (*iter);
}

void T_DairyDateItem::insert(T_DairyDateItem* tDairyDateItem)
{
    tDairyDateItem->m_pParentItem = this;
    m_setChildItems.insert(tDairyDateItem);
}

bool T_DairyDateItem::contains(T_DairyDateItem* tDairyDateItem)
{
    return m_setChildItems.contains(tDairyDateItem);
}

QList<T_DairyDateItem *> T_DairyDateItem::values()
{
    return m_setChildItems.values();
}

T_DairyDateItem *T_DairyDateItem::parentItem()
{
    return m_pParentItem;
}

int T_DairyDateItem::row()
{
    if (m_pParentItem)
    {
        return m_pParentItem->values().indexOf(const_cast<T_DairyDateItem*>(this));
    }
    return 0;
}

int T_DairyDateItem::column()
{
    return eDairyDateNodeType - 1;
}

/*
bool T_DairyDateItem::operator<(const T_DairyDateItem &right) const
{
    // 必须同一类型才具可比性，才能插入
    if (eDairyDateType != right.eDairyDateType)
    {
        return false;
    }
    // 排序
    switch (eDairyDateType)
    {
    case ED_Year:
        return strYear.toInt() < right.strYear.toInt();
    case ED_Month:
        return strMonth.toInt() < right.strMonth.toInt();
    case ED_Day:
        return strDay.toInt() < right.strDay.toInt();
    default:
        break;
    }
    return false;
}
*/



QString T_DairyDateItem::text()
{
    QString strText;
    switch (eDairyDateNodeType)
    {
    case ED_Year:
        strText = strYear + "年";
        break;
    case ED_Month:
        strText = strMonth + "月";
        break;
    case ED_Day:
        if (strTitle.isEmpty())
        {
            strText = strDay + "日";
        }
        else
        {
            strText = strDay + "日 - " + strTitle;
        }
        break;
    default:
        break;
    }
    return strText;
}





///
/// \brief CDairyDateTreeModel::CDairyDateTreeModel
///
CDairyDateTreeModel::CDairyDateTreeModel(QObject *parent = 0)
    : QAbstractItemModel(parent)
    , m_pDairyDateItemRoot(NULL)
{
    loadDairy();
}

int CDairyDateTreeModel::rowCount(const QModelIndex &parent) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return 0;
    }

    T_DairyDateItem *pParentItem;
    if (!parent.isValid())
    {
        pParentItem = m_pDairyDateItemRoot;
    }
    else
    {
        pParentItem = static_cast<T_DairyDateItem*>(parent.internalPointer());
    }

    QList<T_DairyDateItem*> lstItem = pParentItem->values();
    return lstItem.size();
}

int CDairyDateTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // 此处不是3,因为指定了父节点
    return 1;
}

QVariant CDairyDateTreeModel::data(const QModelIndex &index, int role) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return QVariant();
    }

    if (!index.isValid())
    {
        return QVariant();
    }

    T_DairyDateItem *pItem = static_cast<T_DairyDateItem*>(index.internalPointer());
    if(role == Qt::DecorationRole && index.column()==0)
    {
//        if (pItem->isFixedItem())
//        {
//            return CLFileItem::dirIcon(pItem->getFilleInfo().strFileName);
//        }
//        else
//        {
//            return QIcon(":/image/main/ico_folder@0.5x.png");
//        }
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    QVariant variant;
    variant.setValue(*pItem);
    return variant;
    //return pItem->text();
    //return pItem->data(index.column());
}

Qt::ItemFlags CDairyDateTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flag = QAbstractItemModel::flags(index);


    return flag;
}

QVariant CDairyDateTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

QModelIndex CDairyDateTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return QModelIndex();
    }

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    T_DairyDateItem *parentItem;
    if (!parent.isValid())
        parentItem = m_pDairyDateItemRoot;
    else
        parentItem = static_cast<T_DairyDateItem*>(parent.internalPointer());

    T_DairyDateItem *childItem = parentItem->values().at(row);
    if (childItem)
    {
//        int nAbleColumn = childItem->column();
//        if (nAbleColumn == column)
//        {
            return createIndex(row, column, childItem);
//        }
    }
    return QModelIndex();
}

QModelIndex CDairyDateTreeModel::parent(const QModelIndex &index) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return QModelIndex();
    }

    if (!index.isValid())
        return QModelIndex();

    T_DairyDateItem *childItem = static_cast<T_DairyDateItem*>(index.internalPointer());
    T_DairyDateItem *parentItem = childItem->parentItem();

    if (parentItem == m_pDairyDateItemRoot)
    {
        return QModelIndex();
    }

    //int nColmun = index.column() > 0 ? index.column() - 1 : 0;
    return createIndex(parentItem->row(), parentItem->column(), parentItem);
}

bool CDairyDateTreeModel::hasChildren(const QModelIndex &parent) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return false;
    }

    T_DairyDateItem *parentItem;

    if (!parent.isValid())
        parentItem = m_pDairyDateItemRoot;
    else
        parentItem = static_cast<T_DairyDateItem*>(parent.internalPointer());

    int nCount = parentItem->values().size();
    return nCount > 0;
}

void CDairyDateTreeModel::loadDairy()
{
    QList<CDairy> lstDairy = CUser::getInstance()->getLstDairy();

    // 如果列表中没有今天的日记则添加今天的空日记
    bool bHaveTodayDairy = false;
    QString strDateTime = QDateTime::currentDateTime().toString(FORMAT_DATETIME);
    foreach (CDairy dairy, lstDairy)
    {
        if (dairy.getDateTime() == strDateTime)
        {
            bHaveTodayDairy = true;
            break;
        }
    }
    if (!bHaveTodayDairy)
    {
        CDairy dairyEmpty;
        lstDairy.append(dairyEmpty);
    }
    createDateTree(lstDairy);
}

void CDairyDateTreeModel::createDateTree(QList<CDairy> m_lstDairy)
{
    m_pDairyDateItemRoot = new T_DairyDateItem(ED_Root);
    foreach (CDairy dairy, m_lstDairy)
    {
        insetDairy(dairy);
    }
}

void CDairyDateTreeModel::insetDairy(CDairy dairy)
{
    T_DairyDateItem* pItemYear = new T_DairyDateItem(ED_Year, dairy);
    T_DairyDateItem* pItemMonth = new T_DairyDateItem(ED_Month, dairy);
    T_DairyDateItem* pItemDay = new T_DairyDateItem(ED_Day, dairy);
    if (m_pDairyDateItemRoot->contains(pItemYear))
    {

        T_DairyDateItem* pItem = m_pDairyDateItemRoot->find(pItemYear);
        delete pItemYear;
        pItemYear = pItem;
    }
    else
    {
        m_pDairyDateItemRoot->insert(pItemYear);
    }

    if (pItemYear->contains(pItemMonth))
    {

        T_DairyDateItem* pItem = pItemYear->find(pItemMonth);
        delete pItemMonth;
        pItemMonth = pItem;
    }
    else
    {
        pItemYear->insert(pItemMonth);
    }

    if (pItemMonth->contains(pItemDay))
    {

        T_DairyDateItem* pItem = pItemMonth->find(pItemDay);
        delete pItemDay;
        pItemDay = pItem;
    }
    else
    {
        pItemMonth->insert(pItemDay);
    }
}



uint qHash(const T_DairyDateItem *key, uint seed)
{
    Q_UNUSED(seed);
    return key->value();
}
