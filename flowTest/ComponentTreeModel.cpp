#include "ComponentTreeModel.h"
#include "private/qabstractitemmodel_p.h"
#include <QApplication>
#include <QStyle>

#if defined(Q_OS_WIN)
class CComponentKey : public QString
{
public:
    CComponentKey() {}
    CComponentKey(const QString &other) : QString(other) {}
    CComponentKey(const CComponentKey &other) : QString(other) {}
    bool operator==(const CComponentKey &other) const { return !compare(other, Qt::CaseInsensitive); }
};

Q_DECLARE_TYPEINFO(CComponentKey, Q_MOVABLE_TYPE);

inline uint qHash(const CComponentKey &key) { return qHash(key.toCaseFolded()); }
#else // Q_OS_WIN
typedef QString CComponentKey;
#endif

///
/// \brief The CComponentNode class
/// 仅供内部实现的节点
///
class CComponentNode
{
public:
    // 构建容器节点
    CComponentNode(const QString & strName = QString(), CComponentNode *pParent = nullptr)
        : strName(strName)
        , parent(pParent)
    {

    }

    // 构建组件节点
    CComponentNode(const CComponent &component, CComponentNode *pParent = nullptr)
        : parent(pParent)
    {
        pComponent = new CComponent();
        (*pComponent) = component;
        strName = pComponent->name();
    }

    ~CComponentNode()
    {
        qDeleteAll(children);
        delete pComponent;
    }


    inline bool isContainer() const { return nullptr == pComponent; }
    inline bool isComponent() const { return nullptr != pComponent; }

    void populate(const CComponent &component)
    {
        if (!pComponent)
        {
            pComponent = new CComponent();
        }
        (*pComponent) = component;
    }

    int indexOfChildren(const QString &strName)
    {
        return children.keys().indexOf(strName);
    }

    CComponentNode* at(int row)
    {
        QString strChildName = children.keys().at(row);
        return children.value(strChildName);
    }

    inline QIcon icon() const
    {
        if (pComponent)
        {
            return pComponent->icon();
        }
        return QApplication::style()->standardIcon(QStyle::SP_DirIcon);
    }

    inline CComponent component() const { if (pComponent) return *pComponent; return CComponent(); }

    // member var
    QString strName;
    CComponent *pComponent = nullptr;

    QHash<CComponentKey, CComponentNode *> children;
    CComponentNode *parent;

};


///
/// \brief The CComponentTreeModelPrivate class
///
class Q_AUTOTEST_EXPORT CComponentTreeModelPrivate : public QAbstractItemModelPrivate
{
    Q_DECLARE_PUBLIC(CComponentTreeModel)
public:
    enum { NumColumns = 1 };
    CComponentTreeModelPrivate();

    QModelIndex index(const CComponentNode *node, int column = 0) const;
    CComponentNode* addNode(CComponentNode *parentNode, const QString &strName);
    CComponentNode* addNode(CComponentNode *parentNode, const CComponent &component);
    CComponentNode *node(const QModelIndex &index) const;
    void removeNode(CComponentNode *parentNode, const QString &strName);

    inline bool indexValid(const QModelIndex &index) const
    {
        Q_Q(const CComponentTreeModel);
        return (index.row() >= 0) && (index.column() >= 0) && (index.model() == q);
    }

    QIcon icon(const QModelIndex &index) const;
    QString name(const QModelIndex &index) const;

    void setupDefaultModelData();

    // 根 实例
    CComponentNode root;
};

CComponentTreeModelPrivate::CComponentTreeModelPrivate()
{
    setupDefaultModelData();
}

QModelIndex CComponentTreeModelPrivate::index(const CComponentNode *node, int column) const
{
    Q_Q(const CComponentTreeModel);
    CComponentNode *parentNode = (node ? node->parent : 0);
    if (node == &root || !parentNode)
        return QModelIndex();

    int row = parentNode->indexOfChildren(node->strName);
    return q->createIndex(row, column, const_cast<CComponentNode*>(node));
}

CComponentNode *CComponentTreeModelPrivate::addNode(CComponentNode *parentNode
                                                    , const QString &strName)
{
    CComponentNode *node = new CComponentNode(strName, parentNode);
    Q_ASSERT(!parentNode->children.contains(strName));
    parentNode->children.insert(strName, node);
    return node;
}

CComponentNode *CComponentTreeModelPrivate::addNode(CComponentNode *parentNode, const CComponent &component)
{
    CComponentNode *node = new CComponentNode(component, parentNode);
    Q_ASSERT(!parentNode->children.contains(component.name()));
    parentNode->children.insert(node->strName, node);
    return node;
}

CComponentNode *CComponentTreeModelPrivate::node(const QModelIndex &index) const
{
    if (!index.isValid())
        return const_cast<CComponentNode*>(&root);
    CComponentNode *indexNode = static_cast<CComponentNode*>(index.internalPointer());
    Q_ASSERT(indexNode);
    return indexNode;
}

void CComponentTreeModelPrivate::removeNode(CComponentNode *parentNode, const QString &strName)
{
    Q_Q(CComponentTreeModel);
    QModelIndex parent = index(parentNode);
    int row = parentNode->indexOfChildren(strName);

    q->beginRemoveRows(parent, row, row);
    CComponentNode * node = parentNode->children.take(strName);
    delete node;
    q->endRemoveRows();
}

QIcon CComponentTreeModelPrivate::icon(const QModelIndex &index) const
{
    if (!index.isValid())
        return QIcon();
    return node(index)->icon();
}

QString CComponentTreeModelPrivate::name(const QModelIndex &index) const
{
    if (!index.isValid())
        return QString();
    CComponentNode *dirNode = node(index);
    return dirNode->strName;
}

void CComponentTreeModelPrivate::setupDefaultModelData()
{
    addNode(&root, "最近");
    CComponentNode* nodeAble = addNode(&root, "可用");
    CComponentNode* nodeGen = addNode(nodeAble, "通用模块");
    addNode(nodeGen, CComponent("登录"));
    addNode(nodeGen, CComponent("判断"));
    addNode(nodeAble, "对话框");
}


///
/// \brief CDairyDateTreeModel::CDairyDateTreeModel
///
CComponentTreeModel::CComponentTreeModel(QObject* parent = 0)
    : QAbstractItemModel(*new CComponentTreeModelPrivate, parent)
{

}


int CComponentTreeModel::rowCount(const QModelIndex & parent) const
{
    Q_D(const CComponentTreeModel);
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return d->root.children.count();

    const CComponentNode *parentNode = d->node(parent);
    return parentNode->children.count();
}

int CComponentTreeModel::columnCount(const QModelIndex & parent) const
{
    return (parent.column() > 0) ? 0 : CComponentTreeModelPrivate::NumColumns;
}

QVariant CComponentTreeModel::data(const QModelIndex & index, int role) const
{
    Q_D(const CComponentTreeModel);
    if (!index.isValid() || index.model() != this)
        return QVariant();

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0: return d->name(index);
            //        case 1: return d->size(index);
            //        case 2: return d->type(index);
            //        case 3: return d->time(index);
        default:
            qWarning("data: invalid display value column %d", index.column());
            break;
        }
        break;
        //    case FilePathRole:
        //        return filePath(index);
        //    case FileNameRole:
        //        return d->name(index);
    case Qt::DecorationRole:
        if (index.column() == 0) {
            QIcon icon = d->icon(index);
            return icon;
        }
        break;
    case Qt::TextAlignmentRole:
        if (index.column() == 1)
            return QVariant(Qt::AlignTrailing | Qt::AlignVCenter);
        break;
        //    case FilePermissions:
        //        int p = permissions(index);
        //        return p;
    }

    return QVariant();
}

Qt::ItemFlags CComponentTreeModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    Qt::ItemFlags flag = QAbstractItemModel::flags(index);


    return flag;
}

QVariant CComponentTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

QModelIndex CComponentTreeModel::index(int row, int column, const QModelIndex & parent) const
{

    Q_D(const CComponentTreeModel);
    if (row < 0 || column < 0 || row >= rowCount(parent) || column >= columnCount(parent))
        return QModelIndex();

    // get the parent node
    CComponentNode *parentNode = (d->indexValid(parent) ? d->node(parent)
                                                        : const_cast<CComponentNode*>(&d->root));
    Q_ASSERT(parentNode);
    const CComponentNode *indexNode = parentNode->at(row);
    Q_ASSERT(indexNode);

    return createIndex(row, column, const_cast<CComponentNode*>(indexNode));
}

QModelIndex CComponentTreeModel::parent(const QModelIndex & index) const
{

    Q_D(const CComponentTreeModel);
    if (!d->indexValid(index))
        return QModelIndex();

    CComponentNode *indexNode = d->node(index);
    Q_ASSERT(indexNode != 0);
    CComponentNode *parentNode = indexNode->parent;
    if (parentNode == 0 || parentNode == &d->root)
        return QModelIndex();

    // get the parent's row
    CComponentNode *grandParentNode = parentNode->parent;
    Q_ASSERT(grandParentNode->children.contains(parentNode->strName));
    int nParentRow = grandParentNode->indexOfChildren(parentNode->strName);
    if (nParentRow == -1)
        return QModelIndex();
    return createIndex(nParentRow, 0, parentNode);
}

bool CComponentTreeModel::hasChildren(const QModelIndex & parent) const
{
    Q_D(const CComponentTreeModel);
    if (parent.column() > 0)
        return false;

    if (!parent.isValid()) // drives
        return true;

    const CComponentNode *indexNode = d->node(parent);
    Q_ASSERT(indexNode);
    return (indexNode->isContainer());
}

CComponent CComponentTreeModel::component(const QModelIndex &index) const
{
    Q_D(const CComponentTreeModel);
    return d->node(index)->component();
}

bool CComponentTreeModel::isContainer(const QModelIndex &index) const
{
    Q_D(const CComponentTreeModel);
    if (!index.isValid())
        return true;
    CComponentNode *n = d->node(index);
    return n->isContainer();
}




