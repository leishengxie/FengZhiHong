#include "JokeSortFilterProxyModel.h"
#include "JokeModel.h"

#include <QtDebug>

CJokeSortFilterProxyModel::CJokeSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_uid(-1)
{

}

void CJokeSortFilterProxyModel::setSortFilterUid(int uid)
{
    m_uid = uid;
    invalidateFilter();
}


bool CJokeSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (-1 == m_uid)
    {
		return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    }
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    T_Joke tJoke = qvariant_cast<T_Joke>(index.data());
    qDebug() << m_uid << tJoke.upUid;
    return m_uid == tJoke.upUid;

}
