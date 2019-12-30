#include "DairyDateTreeModel.h"
#include <QDateTime>

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
    did = dairy.getDid();
    strTitle = dairy.getTitle();
    QString strDateTime = dairy.getDateTime();
    strYear = strDateTime.mid(0, 4);
    strMonth = strDateTime.mid(5, 2);
    strDay = strDateTime.mid(8, 2);
}

void T_DairyDateItem::init()
{
    did = INVAILD_DAIRY_ID;
    eDairyDateNodeType = ED_Invalid;
    m_setChildItems.clear();
    m_pParentItem = NULL;
}

T_DairyDateItem::~T_DairyDateItem()
{
    /*
    if (m_setChildItems.size() < 1)
    {
        return;
    }
    qDeleteAll(m_setChildItems);
    m_setChildItems.clear();
    */
}

void T_DairyDateItem::release()
{
    deleteChildren();
    delete this;
}

bool T_DairyDateItem::operator ==(const T_DairyDateItem & right) const
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

//bool T_DairyDateItem::operator ==(const T_DairyDateItem *right) const
//{
//    return *this == *right;
//}


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

void T_DairyDateItem::deleteChild(T_DairyDateItem* child)
{
//    set<T_DairyDateItem*, T_DairyDateComparator>::iterator iter = m_setChildItems.begin();
//    for (;iter != m_setChildItems.end(); ++iter)
//    {
//        return *iter;
//    }
    m_setChildItems.erase(child);
    delete child;
    child = NULL;
}

void T_DairyDateItem::deleteChildren()
{
//    if (m_setChildItems.size() < 1)
//    {
//        return;
//    }
//    qDeleteAll(m_setChildItems);
//    m_setChildItems.clear();
    set<T_DairyDateItem*, T_DairyDateComparator>::iterator iter = m_setChildItems.begin();
    while (iter != m_setChildItems.end())
    {
        ((T_DairyDateItem*)(*iter))->release(); // 注意，只是释放内存，没有erase迭代器
        ++iter;
    }
    m_setChildItems.clear(); // 移除容器所有项
}

T_DairyDateItem* T_DairyDateItem::find(T_DairyDateItem* tDairyDateItem)
{

    set<T_DairyDateItem*, T_DairyDateComparator>::iterator iter = m_setChildItems.find(tDairyDateItem);
    if (iter != m_setChildItems.end())
    {
        return *iter;
    }
    return NULL;
}

void T_DairyDateItem::insert(T_DairyDateItem* tDairyDateItem)
{
    tDairyDateItem->m_pParentItem = this;
    m_setChildItems.insert(tDairyDateItem);
}

//bool T_DairyDateItem::contains(T_DairyDateItem tDairyDateItem)
//{
//    return m_setChildItems.contains(tDairyDateItem);
//}

//bool T_DairyDateItem::contains_ex(T_DairyDateItem *tDairyDateItem)
//{
//    if (m_setChildItems.isEmpty())
//    {
//        return false;
//    }
//    QSet<T_DairyDateItem*>::iterator iter;
//    for(iter = m_setChildItems.begin(); iter != m_setChildItems.end(); ++iter)
//    {
//         if( *(*iter) == *tDairyDateItem)
//         {
//             return true;
//         }
//    }
//    return false;
//}

QList<T_DairyDateItem*> T_DairyDateItem::values()
{
    QList<T_DairyDateItem*> lstDairyDateItem;
    for (auto pItem : m_setChildItems)
    {
        lstDairyDateItem.append(pItem);
    }
//    return m_setChildItems.values();

    return lstDairyDateItem;
}

T_DairyDateItem* T_DairyDateItem::parentItem()
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
/// \brief T_DairyDateItem::dairyModify 递归找到更新节点
/// \param dairyBefore
/// \param dairyAfter
///
void T_DairyDateItem::dairyModify(const CDairy & dairyBefore, const CDairy & dairyAfter
                                  , T_DairyDateItem* & pDairyDateItem)
{
    if (did == dairyBefore.getDid() && eDairyDateNodeType == ED_Day)
    {
        did = dairyAfter.getDid();
        strTitle = dairyAfter.getTitle();
        pDairyDateItem = this;
    }
    if (m_setChildItems.empty())
    {
        return;
    }
    for (T_DairyDateItem* pItem : m_setChildItems)
    {
        pItem->dairyModify(dairyBefore, dairyAfter, pDairyDateItem);
    }
}

void T_DairyDateItem::findItemById(int did, T_DairyDateItem* & pDairyDateItem)
{
    if (this->did == did && eDairyDateNodeType == ED_Day)
    {
        pDairyDateItem = this;
    }
    if (m_setChildItems.empty())
    {
        return;
    }
    for (T_DairyDateItem* pItem : m_setChildItems)
    {
        pItem->findItemById(did, pDairyDateItem);
    }
}


//uint qHash(const T_DairyDateItem key, uint seed)
//{
//    Q_UNUSED(seed);
//    return key.value();
//}





///
/// \brief CDairyDateTreeModel::CDairyDateTreeModel
///
CDairyDateTreeModel::CDairyDateTreeModel(QObject* parent = 0)
    : QAbstractItemModel(parent)
    , m_pDairyDateItemRoot(NULL)
{

}

int CDairyDateTreeModel::rowCount(const QModelIndex & parent) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return 0;
    }

    T_DairyDateItem* pParentItem;
    if (!parent.isValid())
    {
        pParentItem = m_pDairyDateItemRoot;
    }
    else
    {
        pParentItem = static_cast<T_DairyDateItem*>(parent.internalPointer());
    }

    return pParentItem->values().size();
}

int CDairyDateTreeModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    // 此处不是3,因为指定了父节点
    return 1;
}

QVariant CDairyDateTreeModel::data(const QModelIndex & index, int role) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return QVariant();
    }

    if (!index.isValid())
    {
        return QVariant();
    }

    T_DairyDateItem* pItem = static_cast<T_DairyDateItem*>(index.internalPointer());
    if(role == Qt::DecorationRole && index.column() == 0)
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
    {
        return QVariant();
    }

    QVariant variant;
    variant.setValue(pItem);
    return variant;
    //return pItem->text();
    //return pItem->data(index.column());
}

Qt::ItemFlags CDairyDateTreeModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

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

QModelIndex CDairyDateTreeModel::index(int row, int column, const QModelIndex & parent) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return QModelIndex();
    }

    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    T_DairyDateItem* parentItem;
    if (!parent.isValid())
    {
        parentItem = m_pDairyDateItemRoot;
    }
    else
    {
        parentItem = static_cast<T_DairyDateItem*>(parent.internalPointer());
    }

    T_DairyDateItem* childItem =  parentItem->values().at(row);
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

QModelIndex CDairyDateTreeModel::parent(const QModelIndex & index) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return QModelIndex();
    }

    if (!index.isValid())
    {
        return QModelIndex();
    }

    T_DairyDateItem* childItem = static_cast<T_DairyDateItem*>(index.internalPointer());
    T_DairyDateItem* parentItem = childItem->parentItem();

    if (parentItem == m_pDairyDateItemRoot)
    {
        return QModelIndex();
    }

    //int nColmun = index.column() > 0 ? index.column() - 1 : 0;
    return createIndex(parentItem->row(), parentItem->column(), parentItem);
}

bool CDairyDateTreeModel::hasChildren(const QModelIndex & parent) const
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return false;
    }

    T_DairyDateItem* parentItem;

    if (!parent.isValid())
    {
        parentItem = m_pDairyDateItemRoot;
    }
    else
    {
        parentItem = static_cast<T_DairyDateItem*>(parent.internalPointer());
    }

    int nCount = parentItem->values().size();
    return nCount > 0;
}



void CDairyDateTreeModel::loadDairyList(const QList<CDairy> & lstDairy)
{
    m_lstDairy = lstDairy;

    // 如果列表中没有今天的日记则添加今天的空日记
    bool bHaveTodayDairy = false;
    QString strDateTime = QDateTime::currentDateTime().toString(FORMAT_DATETIME);

    CDairy dairyToday;
    foreach (CDairy dairy, m_lstDairy)
    {
        if (dairy.getDateTime().mid(0, 10) == strDateTime.mid(0, 10))
        {
            bHaveTodayDairy = true;
            dairyToday = dairy;
            break;
        }
    }
    if (!bHaveTodayDairy)
    {
        m_lstDairy.append(dairyToday);
    }
    emit loadTodayDairyFinished(dairyToday);
    convertDiaryListToTree(m_lstDairy);
}

void CDairyDateTreeModel::sortDairyByTag(const QString & strTagName)
{
    QList<CDairy> lstDairySort;
    if ( "全部日记" == strTagName)
    {
        lstDairySort = m_lstDairy;
    }
    else
    {
        for (CDairy dairy : m_lstDairy)
        {
            if (strTagName == dairy.getTag())
            {
                lstDairySort.append(dairy);
            }
        }
    }
    emit sortDairyByTagFinished(strTagName, lstDairySort);
    convertDiaryListToTree(lstDairySort);
}

void CDairyDateTreeModel::convertDiaryListToTree(const QList<CDairy> & lstDairy)
{
    if (NULL == m_pDairyDateItemRoot)
    {
        m_pDairyDateItemRoot = new T_DairyDateItem(ED_Root);
    }
    m_pDairyDateItemRoot->deleteChildren();
    beginResetModel();
    foreach (CDairy dairy, lstDairy)
    {
        addDairyToTree(dairy);
    }
    endResetModel();
}

void CDairyDateTreeModel::addDairyToTree(CDairy dairy)
{
    T_DairyDateItem* pItemYear = new T_DairyDateItem(ED_Year, dairy);
    T_DairyDateItem* pItemMonth = new T_DairyDateItem(ED_Month, dairy);
    T_DairyDateItem* pItemDay = new T_DairyDateItem(ED_Day, dairy);

    T_DairyDateItem* pItemParent = m_pDairyDateItemRoot;
    T_DairyDateItem* pItemChild = NULL;

    Q_ASSERT(pItemParent);
    pItemChild = pItemParent->find(pItemYear);
    if (pItemChild)
    {
        delete pItemYear;
        pItemParent = pItemChild;
    }
    else
    {
        pItemParent->insert(pItemYear);
        pItemParent = pItemYear;
    }

    Q_ASSERT(pItemParent);
    pItemChild = pItemParent->find(pItemMonth);
    if (pItemChild)
    {
        delete pItemMonth;
        pItemParent = pItemChild;
    }
    else
    {
        pItemParent->insert(pItemMonth);
        pItemParent = pItemMonth;
    }

    Q_ASSERT(pItemParent);
    pItemChild = pItemParent->find(pItemDay);
    if (pItemChild)
    {
        delete pItemDay;
        pItemParent = pItemChild;
    }
    else
    {
        pItemParent->insert(pItemDay);
    }

}

void CDairyDateTreeModel::dairyModify(const CDairy & dairyBefore, const CDairy & dairyAfter)
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return;
    }

    T_DairyDateItem* pDairyDateItem = NULL;
    m_pDairyDateItemRoot->dairyModify(dairyBefore, dairyAfter, pDairyDateItem);
    //endResetModel();
    //QModelIndex indexTopleft = index(0, 0);
    //emit(dataChanged(indexChanged, indexChanged));
    // 没有找到就不用更新
    if (pDairyDateItem == NULL)
    {
        return;
    }
    QModelIndex indexModify = createIndex(pDairyDateItem->row(), 0, pDairyDateItem);
    emit(dataChanged(indexModify, indexModify));
}

void CDairyDateTreeModel::expandDairy(int did)
{
    if (m_pDairyDateItemRoot == NULL)
    {
        return;
    }
    T_DairyDateItem* pDairyDateItem = NULL;
    m_pDairyDateItemRoot->findItemById(did, pDairyDateItem);
    if (pDairyDateItem == NULL)
    {
        return;
    }
    QModelIndex indexExpand = createIndex(pDairyDateItem->row(), 0, pDairyDateItem);
    emit requireExpand(indexExpand);

}





