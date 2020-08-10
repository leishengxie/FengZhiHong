#include "DailyScheduleListDelegate.h"
#include "DailyScheduleModel.h"
#include <QPainter>
#include <QApplication>


CDailyScheduleListDelegate::CDailyScheduleListDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void CDailyScheduleListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option
                                       , const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QStyledItemDelegate::paint(painter, option, index);
    }
    T_ScheduleItem tScheduleItem = qvariant_cast<T_ScheduleItem>(index.data());

    QStyleOptionViewItem  view_option(option);
    QRect rect = view_option.rect;

    // 定义QPalette的ColorRole
    auto role = QPalette::Text;
    // 获取QApplication的QPalette
    QPalette pa = QApplication::palette();
    if (view_option.state & QStyle::State_Selected)
    {
        role = QPalette::HighlightedText;
        painter->fillRect( view_option.rect, view_option.palette.highlight() );

    }
    else if (view_option.state & QStyle::State_MouseOver)
    {
        //painter->fillRect(view_option.rect, view_option.palette.light());
        painter->fillRect(view_option.rect, QColor( 247,252,255));
    }
    else
    {
        painter->fillRect(view_option.rect, qvariant_cast<QBrush>(index.data(Qt::BackgroundRole)));
    }

    painter->save();
    if (tScheduleItem.isContainsNow())
    {
        pa.setBrush(QPalette::HighlightedText, QBrush(Qt::red));
        pa.setBrush(QPalette::Text, QBrush(Qt::red));
        painter->setPen(QColor(Qt::red));
        QFont font = painter->font();
        font.setPointSize(font.pointSize() + 5);
        font.setBold(true);
        painter->setFont(font);
    }
    QFontMetrics fontMetrics = painter->fontMetrics();
    QString strStartAndEndRime = tScheduleItem.startAndEndRime() + ":";
    int nWidthStartEndTime = fontMetrics.width(strStartAndEndRime) + 5;
    QRect rectStartEndTime(rect.x(), rect.y(), nWidthStartEndTime, rect.height());
    QApplication::style()->drawItemText ( painter
                                          , rectStartEndTime
                                          , Qt::AlignLeft | Qt::AlignVCenter
                                          , pa
                                          , true
                                          , strStartAndEndRime
                                          , role);
//    QTextOption textOption(Qt::AlignLeft | Qt::AlignVCenter);
//    painter->drawText( rectStartEndTime, strStartAndEndRime, textOption);


    int nWidthClockIcon = 0;
    if (tScheduleItem.bUseAlarmClock)
    {
        QPixmap pix = QPixmap(":/img/alarm_clock.png").scaledToHeight(rect.height() - 2);
        nWidthClockIcon = pix.size().width();
        QRect rectIcon(rect.x() + nWidthStartEndTime, rect.y(), nWidthClockIcon, pix.size().height());
        QApplication::style()->drawItemPixmap(painter, rectIcon, Qt::AlignCenter, pix);
    }

    int nWidthContent = fontMetrics.width(tScheduleItem.strContent) + 5;
    QRect rectContent(rect.x() + nWidthStartEndTime + nWidthClockIcon, rect.y(), nWidthContent, rect.height());
    // 使用style已有的东西绘制
    QApplication::style()->drawItemText ( painter
                                          , rectContent
                                          , Qt::AlignLeft | Qt::AlignVCenter
                                          , pa
                                          , true
                                          , tScheduleItem.strContent
                                          , role);
    //painter->drawText( rectContent, tScheduleItem.strContent, textOption);
    painter->restore();

    painter->save();
    painter->setPen(QColor(233,237,243));
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->restore();
}

QSize CDailyScheduleListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(50);
    return size;
}
