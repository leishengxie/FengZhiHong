#ifndef CARTICLELISTMODEL_H
#define CARTICLELISTMODEL_H

#include <QAbstractListModel>

struct T_InductiveArticle
{
    int iid;    // 预留id
    QString strTitle;
    QString strDate;
    QString strContent;
};


class CArticleListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CArticleListModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;


public slots:
    // 数据源数据发生变化
    void onSrcListArticleChanged(const QList<T_InductiveArticle> &lstOther);

    void onAddArticle(const T_InductiveArticle & tInductiveArticle);

private:

private:
    QList<T_InductiveArticle> m_lstInductiveArticle;
};



#endif // CARTICLELISTMODEL_H
