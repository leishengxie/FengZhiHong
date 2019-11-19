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

class CArticleListModel
{
public:
    CArticleListModel();
};

#endif // CARTICLELISTMODEL_H
