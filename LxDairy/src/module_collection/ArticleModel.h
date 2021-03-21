#ifndef CJOKEMODEL_H
#define CJOKEMODEL_H
#include <QAbstractTableModel>
#include "Article.h"

class CArticleModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CArticleModel(QObject* parent = 0);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;

    QList<T_Article> listJoke()
    {
        return m_lstJoke;
    }

    void setListJoke(const QList<T_Article> & lstJoke);
    void appendListJoke(const QList<T_Article> & lstJoke);
    void clear();

private:


private:
    QList<T_Article> m_lstJoke;
    QStringList m_strlstHeader;
};

#endif // CJOKEMODEL_H
