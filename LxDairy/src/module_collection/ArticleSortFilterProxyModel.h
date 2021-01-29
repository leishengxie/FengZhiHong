#ifndef CLFILESELECTSORTMODEL_H
#define CLFILESELECTSORTMODEL_H
#include <QSortFilterProxyModel>

class CArticleSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CArticleSortFilterProxyModel(QObject *parent = 0);

    void setSortFilterUid(int uid);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;


private:
    int m_uid;

};
#endif // CLFILESELECTSORTMODEL_H
