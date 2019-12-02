#ifndef CDAIRYSTATISTICSDELEGATE_H
#define CDAIRYSTATISTICSDELEGATE_H

#include <QStyledItemDelegate>

class CDairyStatisticsDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    CDairyStatisticsDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // CDAIRYSTATISTICSDELEGATE_H
