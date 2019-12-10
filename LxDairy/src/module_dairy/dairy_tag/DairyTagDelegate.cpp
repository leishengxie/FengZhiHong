#include "DairyTagDelegate.h"
#include "DairyTagListModel.h"
#include <QPainter>
#include <QApplication>
#include <QListWidgetItem>

CDairyTagDelegate::CDairyTagDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void CDairyTagDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    // 源码 QStyledItemDelegate
    //Q_ASSERT(index.isValid());
//    QStyleOptionViewItem opt = option;
//    initStyleOption(&opt, index);

//    const QWidget *widget = QStyledItemDelegatePrivate::widget(option);
//    QStyle *style = widget ? widget->style() : QApplication::style();
//    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);

    // 跟踪到源码 QCommonStyle.cpp
    //找到实现的
    /**
    case CE_ItemViewItem:
            if (const QStyleOptionViewItem *vopt = qstyleoption_cast<const QStyleOptionViewItem *>(opt)) {
                p->save();
                p->setClipRect(opt->rect);

                QRect checkRect = proxy()->subElementRect(SE_ItemViewItemCheckIndicator, vopt, widget);
                QRect iconRect = proxy()->subElementRect(SE_ItemViewItemDecoration, vopt, widget);
                QRect textRect = proxy()->subElementRect(SE_ItemViewItemText, vopt, widget);

                // draw the background
                proxy()->drawPrimitive(PE_PanelItemViewItem, opt, p, widget);

                // draw the check mark
                if (vopt->features & QStyleOptionViewItem::HasCheckIndicator) {
                    QStyleOptionViewItem option(*vopt);
                    option.rect = checkRect;
                    option.state = option.state & ~QStyle::State_HasFocus;

                    switch (vopt->checkState) {
                    case Qt::Unchecked:
                        option.state |= QStyle::State_Off;
                        break;
                    case Qt::PartiallyChecked:
                        option.state |= QStyle::State_NoChange;
                        break;
                    case Qt::Checked:
                        option.state |= QStyle::State_On;
                        break;
                    }
                    proxy()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &option, p, widget);
                }

                // draw the icon
                QIcon::Mode mode = QIcon::Normal;
                if (!(vopt->state & QStyle::State_Enabled))
                    mode = QIcon::Disabled;
                else if (vopt->state & QStyle::State_Selected)
                    mode = QIcon::Selected;
                QIcon::State state = vopt->state & QStyle::State_Open ? QIcon::On : QIcon::Off;
                vopt->icon.paint(p, iconRect, vopt->decorationAlignment, mode, state);

                // draw the text
                /// -- 重点
                if (!vopt->text.isEmpty()) {
                    QPalette::ColorGroup cg = vopt->state & QStyle::State_Enabled
                                          ? QPalette::Normal : QPalette::Disabled;
                    if (cg == QPalette::Normal && !(vopt->state & QStyle::State_Active))
                        cg = QPalette::Inactive;

                    if (vopt->state & QStyle::State_Selected) {
                        p->setPen(vopt->palette.color(cg, QPalette::HighlightedText));
                    } else {
                        p->setPen(vopt->palette.color(cg, QPalette::Text));
                    }
                    if (vopt->state & QStyle::State_Editing) {
                        p->setPen(vopt->palette.color(cg, QPalette::Text));
                        p->drawRect(textRect.adjusted(0, 0, -1, -1));
                    }

                    d->viewItemDrawText(p, vopt, textRect);
                }

                // draw the focus rect
                 if (vopt->state & QStyle::State_HasFocus) {
                    QStyleOptionFocusRect o;
                    o.QStyleOption::operator=(*vopt);
                    o.rect = proxy()->subElementRect(SE_ItemViewItemFocusRect, vopt, widget);
                    o.state |= QStyle::State_KeyboardFocusChange;
                    o.state |= QStyle::State_Item;
                    QPalette::ColorGroup cg = (vopt->state & QStyle::State_Enabled)
                                  ? QPalette::Normal : QPalette::Disabled;
                    o.backgroundColor = vopt->palette.color(cg, (vopt->state & QStyle::State_Selected)
                                                 ? QPalette::Highlight : QPalette::Window);
                    proxy()->drawPrimitive(QStyle::PE_FrameFocusRect, &o, p, widget);
                }

                 p->restore();
            }
            break;
            */



    Q_ASSERT(index.isValid());
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);


    // 20191210 优化
    auto role = QPalette::Text;
    if (viewOption.state & QStyle::State_Selected)
    {
        role = QPalette::HighlightedText;
        painter->fillRect( viewOption.rect, viewOption.palette.highlight() );
        //painter->fillRect(option.rect, QColor("#e3e3e5"));
    }
    else if (viewOption.state & QStyle::State_MouseOver)
    {
        painter->fillRect(viewOption.rect, viewOption.palette.light());
    }


        painter->save();
        QVariant var = index.data(Qt::DisplayRole);
        T_DairyTagItem tDairyTagItem = var.value<T_DairyTagItem>();
        // 或者 T_DairyTagItem tDairyTagItem = qvariant_cast<T_DairyTagItem>(index.data());

        // item 矩形区域
        QRectF rect;
        rect.setX(viewOption.rect.x());
        rect.setY(viewOption.rect.y());
        rect.setWidth(viewOption.rect.width()-1);
        rect.setHeight(viewOption.rect.height()-1);

//        QPainterPath path;
//        path.moveTo(rect.topRight());
//        path.lineTo(rect.topLeft());
//        path.quadTo(rect.topLeft(), rect.topLeft());
//        path.lineTo(rect.bottomLeft());
//        path.quadTo(rect.bottomLeft(), rect.bottomLeft());
//        path.lineTo(rect.bottomRight());
//        path.quadTo(rect.bottomRight(), rect.bottomRight());
//        path.lineTo(rect.topRight());
//        path.quadTo(rect.topRight(), rect.topRight());

//        // 鼠标悬停或者选中时改变背景色
//        if (option.state.testFlag(QStyle::State_MouseOver)) {
//            painter->setPen(QPen(QColor("#ebeced")));
//            painter->setBrush(QColor("#ebeced"));
//            painter->drawPath(path);
//        }
//        if (option.state.testFlag(QStyle::State_Selected)) {
//            painter->setPen(QPen(QColor("#e3e3e5")));
//            painter->setBrush(QColor("#e3e3e5"));
//            painter->drawPath(path);
//        }

        // 绘制图片，歌手，数量位置区域
//        QRectF iconRect = QRect(rect.left()+5, rect.top()+5, 40, 40);
//        QRectF singerRect = QRect(iconRect.right()+5, iconRect.top(), rect.width()-10-iconRect.width(), 20);
//        QRectF songNbRect = QRect(singerRect.left(), singerRect.bottom()+5, rect.width()-10-iconRect.width(), 20);

//        painter->drawImage(iconRect, QImage(itemData.iconPath));
//        painter->setPen(QPen(Qt::black));
//        painter->setFont(QFont("Microsoft Yahei", 10));
//        painter->drawText(singerRect, itemData.singer);

//        painter->setPen(QPen(Qt::gray));
//        painter->drawText(songNbRect, itemData.songsNb);

        QFontMetrics fontWidth(painter->font());
        int nFontHeight = fontWidth.height();
        QRect rectTagName = QRect(rect.left()+5, rect.top(), rect.width() - 5, rect.height());
        QRect rectTagNum = QRect(rect.left()+5, rect.top(), rect.width() - 10, rect.height());
        //painter->drawText(songNbRect, itemData.songsNb);
        QApplication::style()->drawItemText ( painter
                                              , rectTagName
                                              , Qt::AlignLeft | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , tDairyTagItem.strTagName
                                              , role);
        QApplication::style()->drawItemText ( painter
                                              , rectTagNum
                                              , Qt::AlignRight | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , "(" + QString::number(tDairyTagItem.nNum) + ")"
                                              , role);
        painter->restore();

}

QSize CDairyTagDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}
