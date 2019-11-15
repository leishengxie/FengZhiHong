#ifndef CDAIRYTAGDELEGATE_H
#define CDAIRYTAGDELEGATE_H

#include <QStyledItemDelegate>

class CDairyTagDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CDairyTagDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;


};

#endif // CDAIRYTAGDELEGATE_H
