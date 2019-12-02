#include "DairyDateDelegate.h"
#include <QApplication>
#include "DairyDateTreeModel.h"

CDairyDateDelegate::CDairyDateDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void CDairyDateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    T_DairyDateItem* tDairyTagItem = qvariant_cast<T_DairyDateItem*>(index.data());
    QApplication::style()->drawItemText ( painter
                                          , option.rect
                                          , Qt::AlignLeft | Qt::AlignVCenter
                                          , QApplication::palette()
                                          , true
                                          , tDairyTagItem->text());
}

QSize CDairyDateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    return QSize(size.width(), 20);
}
