#include "ArticleListModel.h"

CArticleListModel::CArticleListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int CArticleListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_lstInductiveArticle.count();
}

QVariant CArticleListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstInductiveArticle.count())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    T_InductiveArticle tInductiveArticle = m_lstInductiveArticle.at(index.row());
    QString strArticle = QString("%1   %2 - %3")
            .arg(tInductiveArticle.strDate)
            .arg(tInductiveArticle.strTitle)
            .arg(tInductiveArticle.strContent);
    QVariant variant;
    variant.setValue(strArticle);
    return variant;

}

void CArticleListModel::onSrcListArticleChanged(const QList<T_InductiveArticle> &lstOther)
{
    beginResetModel();
    m_lstInductiveArticle = lstOther;
    endResetModel();
}

void CArticleListModel::onAddArticle(const T_InductiveArticle &tInductiveArticle)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_lstInductiveArticle.append(tInductiveArticle);
    endInsertRows();
}



