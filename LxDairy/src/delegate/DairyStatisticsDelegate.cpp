#include "DairyStatisticsDelegate.h"
#include <QPainter>
#include <QApplication>
#include "model/DairyStatisticsModel.h"


CDairyStatisticsDelegate::CDairyStatisticsDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void CDairyStatisticsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return;
    }
    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, QColor("#e3e3e5"));
    }
    else if (option.state & QStyle::State_MouseOver)
    {
        painter->fillRect(option.rect, QColor( 247,252,255));
    }
    painter->save();
    QVariant var = index.data(Qt::DisplayRole);
    T_DairyStatisticsItem tDairyStatisticsItem = var.value<T_DairyStatisticsItem>();

    // item 矩形区域
    QRectF rect;
    rect.setX(option.rect.x());
    rect.setY(option.rect.y());
    rect.setWidth(option.rect.width()-1);
    rect.setHeight(option.rect.height()-1);

//    QFontMetrics fontWidth(painter->font());
//    int nFontHeight = fontWidth.height();
    QRect rectDate = QRect(rect.left()+5, rect.top(), 80, rect.height());
    QRect rectContent = QRect(rect.left()+5+80+15, rect.top(), rect.width() - 100, rect.height());
    QApplication::style()->drawItemText ( painter
                                          , rectDate
                                          , Qt::AlignLeft | Qt::AlignVCenter
                                          , QApplication::palette()
                                          , true
                                          , tDairyStatisticsItem.strDate);
    QApplication::style()->drawItemText ( painter
                                          , rectContent
                                          , Qt::AlignLeft | Qt::AlignVCenter
                                          , QApplication::palette()
                                          , true
                                          , tDairyStatisticsItem.strContent);
    painter->restore();
}

QSize CDairyStatisticsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}
