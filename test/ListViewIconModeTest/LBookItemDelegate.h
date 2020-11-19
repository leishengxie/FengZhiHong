#ifndef CLBOOKITEMDELEGATE_H
#define CLBOOKITEMDELEGATE_H

#include <QStyledItemDelegate>

class CLBookItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CLBookItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // CLBOOKITEMDELEGATE_H
