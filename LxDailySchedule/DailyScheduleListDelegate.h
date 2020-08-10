#ifndef CDAILYSCHEDULELISTDELEGATE_H
#define CDAILYSCHEDULELISTDELEGATE_H

#include <QStyledItemDelegate>

class CDailyScheduleListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CDailyScheduleListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

};

#endif // CDAILYSCHEDULELISTDELEGATE_H
