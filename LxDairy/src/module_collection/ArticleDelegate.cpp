#include "ArticleDelegate.h"
#include <QPainter>
#include <QApplication>
#include "ArticleModel.h"
#include "StarEditor.h"

#define LINE_COLOR      QColor(233,237,243)

CArticleDelegate::CArticleDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void CArticleDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return;
    }

    T_Article tJoke = qvariant_cast<T_Article>(index.data());

    QStyleOptionViewItem  view_option(option);
    QRect rect = view_option.rect;

    auto role = QPalette::Text;
    if (view_option.state & QStyle::State_Selected)
    {
        role = QPalette::HighlightedText;
        painter->fillRect( view_option.rect, view_option.palette.highlight() );

    }
    else if (view_option.state & QStyle::State_MouseOver)
    {
        painter->fillRect(view_option.rect, view_option.palette.light());
    }
    else
    {
        painter->fillRect(view_option.rect, qvariant_cast<QBrush>(index.data(Qt::BackgroundRole)));
    }


    if (index.column() == 0)
    {
        QApplication::style()->drawItemText ( painter
                                              , rect
                                              , Qt::AlignLeft | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , tJoke.strTitle
                                              , role);
    }

    if (index.column() == 1)
    {
        QApplication::style()->drawItemText ( painter
                                              , rect
                                              , Qt::AlignLeft | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , tJoke.strNickname
                                              , role);
    }
    if (index.column() == 2)
    {
        QApplication::style()->drawItemText ( painter
                                              , rect
                                              , Qt::AlignLeft | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , tJoke.strDate
                                              , role);
    }
    else if (index.column() == 3)
    {
        QFontMetrics fontMetrics(painter->font());
        QString strContent = fontMetrics.elidedText(tJoke.strContent, Qt::ElideRight, rect.width() - 10);
        QApplication::style()->drawItemText ( painter
                                              , rect
                                              , Qt::AlignLeft | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , strContent
                                              , role);
    }
    else if (index.column() == 4)
    {
        //tJoke.dRating;
        CStarEditor::drawFiveStarRating(painter, rect, option.palette, tJoke.dRatingAverageScore, true);
    }

    painter->save();
    painter->setPen(LINE_COLOR);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->restore();
}

QSize CArticleDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}
