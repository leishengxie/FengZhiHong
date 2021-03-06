#ifndef CDAIRYTAGLISTMODEL_H
#define CDAIRYTAGLISTMODEL_H

#include <QAbstractListModel>
#include "Dairy.h"

// 标签节点
struct T_DairyTagItem
{
    QString strTagName;
    int nNum;

    T_DairyTagItem()
        : nNum(0)
    {

    }

    T_DairyTagItem(QString strTagName)
        : strTagName(strTagName)
        , nNum(0)
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

///
/// \brief The CDairyTagListModel class 标签model
///
class CDairyTagListModel : public QAbstractListModel
{
        Q_OBJECT
public:
    CDairyTagListModel(QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QList<T_DairyTagItem> listDairyTag()
    {
        return m_lstDairyTag;
    }

    QStringList listDairyTagNames() const;
    static QStringList listSysDefaultDairyTagNames();


    // 从数据库中加载用户自定义标签
    void loadCustomDairyTag(const QStringList &strlstTagName);

    // 加载日记刷新标签
    void loadDiaryList(const QList<T_Dairy> &lstDairy);



private:
    // 加载系统默认标签
    void loadSysDefaultTag();

private:

    // 标签数据
    QList<T_DairyTagItem> m_lstDairyTag;
};

#endif // CDAIRYTAGLISTMODEL_H
