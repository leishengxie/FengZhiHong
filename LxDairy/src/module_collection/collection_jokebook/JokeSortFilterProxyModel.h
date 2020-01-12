#ifndef CLFILESELECTSORTMODEL_H
#define CLFILESELECTSORTMODEL_H
#include <QSortFilterProxyModel>

class CJokeSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CJokeSortFilterProxyModel(QObject *parent = 0);

    void setSortFilterUid(int uid);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;


private:
    int m_uid;

};
#endif // CLFILESELECTSORTMODEL_H
