#ifndef CJOKEDELEGATE_H
#define CJOKEDELEGATE_H

#include <QStyledItemDelegate>

class CArticleDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    CArticleDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CJOKEDELEGATE_H
