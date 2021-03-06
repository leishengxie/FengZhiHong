#include "CollectionModel.h"


CCollectionModel::CCollectionModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_lstCollectionItem.append(T_CollectionItem("笑话集"
                                                , ":/img/tool_img/maple_leaf_book.png"
                                                , "你可以将自己自创或收集到的开心的事上传到系统，这样你的朋友或\"世界\"的人都能得到你分享的快乐。" \
                                                "系统将对你上传的作品做查重，评分，排行等服务"));
}

int CCollectionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_lstCollectionItem.count();
}

QVariant CCollectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstCollectionItem.count())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    T_CollectionItem tCollectionItem = m_lstCollectionItem.at(index.row());
    QVariant variant;
    variant.setValue(tCollectionItem);
    return variant;

}

