#ifndef CCOLLECTIONDELEGATE_H
#define CCOLLECTIONDELEGATE_H

#include <QStyledItemDelegate>

class CCollectionDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    CCollectionDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CCOLLECTIONDELEGATE_H
