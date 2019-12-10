#include "LTabBarVStyle.h"
#include <QPainter>
#include <QStyleOptionTab>

CLTabBarVStyle::CLTabBarVStyle(QStyle *style)
    : QProxyStyle(style)
{

}

QSize CLTabBarVStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option
                                    , const QSize &size, const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab)
    {
        s.transpose();
        s.rwidth() = 128;             // 设置每个tabBar中item的大小
        s.rheight() = 97;
    }
    return s;
}

void CLTabBarVStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option
                              , QPainter *painter, const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel)
    {
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
        {
            QRect allRect = tab->rect; allRect.setWidth(allRect.width() - 5);
            allRect.setHeight(allRect.height() - 2);
            //选中状态
            if (tab->state & QStyle::State_Selected)
            {
                //save用以保护坐标，restore用来退出状态
                painter->save();
                painter->setBrush(QBrush(0xeed7c1));
                //矩形
                painter->drawRect(allRect.adjusted(0, 0, 10, 10));
                painter->restore();
            }
            //hover状态
            else if(tab->state & QStyle::State_MouseOver)
            {
                painter->save();
                painter->setBrush(QBrush(0xeed7c1));
                //painter->drawRoundedRect(tab->rect, 8, 8);
                painter->drawRect(allRect.adjusted(0, 0, 10, 10));
                painter->restore();
            }
            else
            {
                painter->save();
                painter->setBrush(QBrush(0x78aadc));
                //painter->drawRoundedRect(tab->rect 8, 8);
                painter->drawRect(allRect.adjusted(0, 0, 10, 10));
                painter->restore();
            }
            QTextOption option;
            option.setAlignment(Qt::AlignCenter);
            painter->setFont(QFont("楷体", 18, QFont::Bold));
            //painter->setPen(0xffffff);
            painter->drawText(allRect, tab->text, option);
            return;
        }
    }
    if (element == CE_TabBarTab)
    {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}
