#ifndef CDAIRYDATEDELEGATE_H
#define CDAIRYDATEDELEGATE_H
#include <QStyledItemDelegate>

class CDairyDateDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CDairyDateDelegate(QObject *parent = 0);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};


#endif // CDAIRYDATEDELEGATE_H
