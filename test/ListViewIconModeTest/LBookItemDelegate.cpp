#include "LBookItemDelegate.h"
#include <QApplication>
#include <QPainter>
#include <QCheckBox>

CLBookItemDelegate::CLBookItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void CLBookItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option
                               , const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    const QWidget* widget = opt.widget;
    QStyle* style = widget ? widget->style() : QApplication::style();
    if (opt.state & QStyle::State_MouseOver)
    {
        painter->fillRect(opt.rect, Qt::green);
    }

    QStyleOptionButton checkBoxOption;
    bool bChecked = index.data(Qt::CheckStateRole).toBool();
    checkBoxOption.state = bChecked ? QStyle::State_On : QStyle::State_Off;
    checkBoxOption.state |= QStyle::State_Enabled;
    checkBoxOption.rect = style->proxy()->subElementRect(QStyle::SE_ItemViewItemCheckIndicator, &opt, widget);

    QCheckBox checkBox;
    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &checkBoxOption, painter, &checkBox);

    QTextOption textOption;
    textOption.setAlignment(QStyle::visualAlignment(opt.direction, opt.displayAlignment));
    QRect rect = style->proxy()->subElementRect(QStyle::SE_ItemViewItemText, &opt, widget);
    painter->setPen(opt.palette.color(QPalette::Text));
    painter->drawText(rect, index.data().toString(), textOption);

    painter->setPen(QColor("#F0F0F0"));
    painter->drawLine(opt.rect.bottomLeft(), opt.rect.bottomRight());
}
