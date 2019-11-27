#include "JokeDelegate.h"
#include <QPainter>
#include <QApplication>
#include "JokeModel.h"
#include "StarEditor.h"

#define FONT_Microsoft_YaHei    "Microsoft YaHei UI"
#define SELECTED_COLOR  QColor(251,251,251)
#define LINE_COLOR      QColor(233,237,243)
#define TEXT_COLOR      QColor(102,114,137)
#define NAME_COLOR      QColor(51,51,51)

CJokeDelegate::CJokeDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void CJokeDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return;
    }

    T_Joke tJoke = qvariant_cast<T_Joke>(index.data());

    QStyleOptionViewItem  view_option(option);
    QRect rect = view_option.rect;
    //    if (view_option.state & QStyle::State_HasFocus)
    //    {
    //        view_option.state = view_option.state ^ QStyle::State_HasFocus;
    //    }

    //    if (view_option.state & QStyle::State_Selected)
    //    {
    //        painter->save();
    //        painter->fillRect(rect, QColor(248,250,254));
    //        //painter->setBrush(QColor(220,231,254));
    //        painter->setPen(QColor(220,231,254));
    //        painter->drawRect(rect);
    //        painter->restore();
    //    }
    //    else
    //    {
    if (view_option.state & QStyle::State_Selected)
    {
        painter->fillRect(view_option.rect, SELECTED_COLOR);
    }
    else
    {
        painter->fillRect(view_option.rect, qvariant_cast<QBrush>(index.data(Qt::BackgroundRole)));
    }
    //    }

    if (option.state & QStyle::State_MouseOver)
    {
        //painter->fillRect(view_option.rect, QColor( 247,252,255));
        //painter->fillRect(view_option.rect, qvariant_cast<QBrush>(index.data(Qt::BackgroundRole)));
        //view_option.backgroundBrush = qvariant_cast<QBrush>(index.data(Qt::BackgroundRole));
        //CLItemDelegateListBase::paint(painter, view_option, index);
    }


    if (index.column() == 0)
    {

    }

    if (index.column() == 1)
    {

    }
    else if (index.column() == 2)
    {

    }
    else if (index.column() == 3)
    {
        //tJoke.dRating;
        CStarEditor::drawFiveStarRating(painter, rect, option.palette, tJoke.dRating, true);
    }

    painter->save();
    painter->setPen(LINE_COLOR);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->restore();
}

QSize CJokeDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}
