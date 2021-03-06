#include "DairyStatisticsDelegate.h"
#include <QPainter>
#include <QApplication>
#include "DairyStatisticsModel.h"


CDairyStatisticsDelegate::CDairyStatisticsDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void CDairyStatisticsDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
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
        painter->fillRect(option.rect, QColor( 247, 252, 255));
    }
    painter->save();
    QVariant var = index.data(Qt::DisplayRole);
    T_Dairy dairy = var.value<T_Dairy>();
    QString strDate = dairy.strDateTime.left(10);
    QString strContent = dairy.strTitle + " - " + dairy.strContent;
    // item 矩形区域
        QFontMetrics fontMetrics(painter->font());
        int nWidth = fontMetrics.width(strDate);

    QRectF rect;
    rect.setX(option.rect.x());
    rect.setY(option.rect.y());
    rect.setWidth(option.rect.width() - 1);
    rect.setHeight(option.rect.height() - 1);

    QRect rectDate = QRect(rect.left() + 5, rect.top(), nWidth, rect.height());
    QRect rectContent = QRect(rect.left() + 5 + nWidth + 15, rect.top(), rect.width() - nWidth - 20, rect.height());
    QApplication::style()->drawItemText ( painter
                                          , rectDate
                                          , Qt::AlignLeft | Qt::AlignVCenter
                                          , QApplication::palette()
                                          , true
                                          , strDate);
    QApplication::style()->drawItemText ( painter
                                          , rectContent
                                          , Qt::AlignLeft | Qt::AlignVCenter
                                          , QApplication::palette()
                                          , true
                                          , strContent);
    painter->restore();
}

QSize CDairyStatisticsDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}
