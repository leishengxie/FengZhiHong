#include "ArticleSortFilterProxyModel.h"
#include "ArticleModel.h"

#include <QtDebug>

CArticleSortFilterProxyModel::CArticleSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_uid(-1)
{

}

void CArticleSortFilterProxyModel::setSortFilterUid(int uid)
{
    m_uid = uid;
    invalidateFilter();
}


bool CArticleSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (-1 == m_uid)
    {
		return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    }
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    T_Article tJoke = qvariant_cast<T_Article>(index.data());
    qDebug() << m_uid << tJoke.upUid;
    return m_uid == tJoke.upUid;

}
