#ifndef CJOKEDELEGATE_H
#define CJOKEDELEGATE_H

#include <QStyledItemDelegate>

class CJokeDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    CJokeDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CJOKEDELEGATE_H
