#include "LStyleBase.h"

#include <QAbstractButton>
#include <QAbstractSpinBox>
#include <QDialogButtonBox>
#include <QPainter>
#include <QStyleOption>
#include <qdrawutil.h>
#include <QStyleFactory>

CLStyleBase::CLStyleBase(QStyle* style)
    : QProxyStyle(QStyleFactory::create("windows")) // 默认windows风格
{

}

//经常使用的颜色角色：
//QPalette::Window                    指定  窗口部件的背景色
//QPalette::WindowText                指定  窗口部件的前景色
//QPalette::Base                      文本输入窗口部件的背景色或者QComobBox下拉菜单的背景色
//QPalette::AlternateBase             主要是用于视图中各项的交替颜色
//QPalette::ToolTipBase               QToolTip QWhatThis的背景色
//QPalette::ToolTipText               QToolTip QWhatThis的前景色
//QPalette::Text                      与Base对照，主要是文本输入窗口的前景色
//QPalette::Button                    按钮的背景色
//QPalette::ButtonText                按钮的前景色
//QPalette::Highlight                 用于表示一个选中的item，默认为Qt::darkBlue
//QPalette::HighlightText             默认为white
//QPalette::Link                      未访问超链接的文本颜色
//QPalette::LinkVisited               已访问的超链接的文本颜色
//为了使得调色板具有3D效果，还有以下的颜色角色
//QPalette::Light
//QPalette::Midlight
//QPalette::Dark
//QPalette::Mid
//QPalette::Shadow
///
/// \brief CLColorStyle::polish     配置调色板
/// \param palette
///
void CLStyleBase::polish(QPalette & palette)
{
    // 测试黑色调色板
    //QPalette paDark;

//    QColor colorBronze = QColor(207, 155, 95);
//    QColor colorVeryLightBlue = QColor(239, 239, 247);
//    QColor colorLightBlue = QColor(223, 223, 239);
//    QColor colorDarkBlue = QColor(95, 95, 191);

//    //创建一个新的面板
//    palette = QPalette(colorBronze);
//    //设置背景
//    palette.setBrush(QPalette::Window, QColor("white"));
//    //设置背景框颜色
//    palette.setBrush(QPalette::Base, colorVeryLightBlue);
//    //设置加深的颜色
//    palette.setBrush(QPalette::AlternateBase, colorLightBlue);
//    //设置选中高亮的颜色
//    palette.setBrush(QPalette::Highlight, colorDarkBlue);

//    //设置禁用的样式
//    palette.setBrush(QPalette::Disabled, QPalette::Highlight, Qt::darkGray);

    QColor brown(212, 140, 95);
    QColor beige(236, 182, 120);
    QColor slightlyOpaqueBlack(0, 0, 0, 63);

    QPixmap backgroundImage(":/img/style/woodbackground.png");
    QPixmap buttonImage(":/img/style/woodbutton.png");
    QPixmap midImage = buttonImage;

    QPainter painter;
    painter.begin(&midImage);
    painter.setPen(Qt::NoPen);
    painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
    painter.end();

    palette = QPalette(brown);

    palette.setBrush(QPalette::BrightText, Qt::white);
    palette.setBrush(QPalette::Base, beige);
    palette.setBrush(QPalette::Highlight, Qt::darkGreen);
    setTexture(palette, QPalette::Button, buttonImage);
    setTexture(palette, QPalette::Mid, midImage);
    setTexture(palette, QPalette::Window, backgroundImage);

    QBrush brush = palette.background();
    brush.setColor(brush.color().dark());

    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);

//    return QProxyStyle::polish(palette);
}

void CLStyleBase::polish(QWidget* widget)
{

    if (qobject_cast<QAbstractButton*>(widget) || qobject_cast<QAbstractSpinBox*>(widget))
    {
        widget->setAttribute(Qt::WA_Hover, true);
    }
    //return QProxyStyle::polish(widget);
}

void CLStyleBase::unpolish(QWidget* widget)
{

    if (qobject_cast<QAbstractButton*>(widget) || qobject_cast<QAbstractSpinBox*>(widget))
    {
        widget->setAttribute(Qt::WA_Hover, false);
    }
    //return QProxyStyle::unpolish(widget);
}

///
/// \brief CLBronzeStyle::styleHint //返回一些关于样式外观的提示 --分别设置各种部件的布局，比如checkbox的text在左边或者在右边 --查询函数类
/// \param which
/// \param option
/// \param widget
/// \param returnData
/// \return
///
int CLStyleBase::styleHint(QStyle::StyleHint which, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
{
//    switch (which)
//    {
//        case SH_DialogButtonLayout:
//            return int(QDialogButtonBox::WinLayout);
//        default:
//            break;
//    }
    return QProxyStyle::styleHint(which, option, widget, returnData);
}

int CLStyleBase::pixelMetric(QStyle::PixelMetric which, const QStyleOption* option, const QWidget* widget) const
{
//    switch (which)
//    {
//    // 返回0是因为不希望在默认的按钮旁边保留额外的空间
//    case PM_ButtonDefaultIndicator:
//        return 0;
//        // 指示器大小是一个正方形
//    case PM_IndicatorWidth:
//    case PM_IndicatorHeight:
//        return 16;
//        // 控制指示器和其右边的文字之间的距离
//    case PM_CheckBoxLabelSpacing:
//        return 8;
//        // QFrame,QPushButton,QSpinBox以及其他的一些窗口部件的线宽.
//    case PM_DefaultFrameWidth:
//        return 2;
//        // 对于其他的PM_xxx值,从基类中继承像素规格的值
//    default:
//        break;
//    }
    return QProxyStyle::pixelMetric(which, option, widget);
}

void CLStyleBase::drawPrimitive(QStyle::PrimitiveElement which, const QStyleOption* option
                                     , QPainter* painter, const QWidget* widget) const
{
    switch (which)
    {
        case PE_FrameLineEdit:
            {
                painter->save();
                painter->setRenderHint(QPainter::Antialiasing, true);
                //painter->setPen(QPen(option->palette.foreground(), 1.0));
                //QColor("#636363");
                painter->setPen(QPen(QBrush(Qt::green), 1.0));
                painter->setBrush(Qt::NoBrush);
                painter->drawRoundedRect(option->rect, 5, 5);
                painter->restore();
                return;

                // 注意 commstyle源码里是这样的
//    case PE_FrameLineEdit:
//        proxy()->drawPrimitive(PE_Frame, opt, p, widget);
            }
        case PE_IndicatorCheckBox:
            {
                drawPECheckBoxIndicator(option, painter);
                return;
            }
        case PE_IndicatorRadioButton:
            {
                //return QProxyStyle::drawPrimitive(which, option, painter, widget);
                drawPERadioButtonIndicator(option, painter);
                return;
            }
        case PE_IndicatorArrowDown:
            {
                // 要自定制的话就应该和up,right, left一起，不然风格不一致就别扭
                break;
//        drawPEArrowDownIndicator(option, painter);
//        return;

            }
        case PE_PanelButtonCommand:
            {
                drawPEPanelButtonCommand(option, painter);
                return;
            }
        default:
            break;
    }
    return QProxyStyle::drawPrimitive(which, option, painter, widget);

}

void CLStyleBase::drawControl(QStyle::ControlElement element, const QStyleOption* option
                                   , QPainter* painter, const QWidget* widget) const
{
    //return QProxyStyle::drawControl(element, option, painter, widget);
    switch (element)
    {
        case CE_PushButtonLabel:
            {
                QStyleOptionButton myButtonOption;
                const QStyleOptionButton* buttonOption =
                    qstyleoption_cast<const QStyleOptionButton*>(option);
                if (buttonOption)
                {
                    myButtonOption = *buttonOption;
                    if (myButtonOption.palette.currentColorGroup()
                            != QPalette::Disabled)
                    {
                        if (myButtonOption.state & (State_Sunken | State_On))
                        {
                            myButtonOption.palette.setBrush(QPalette::ButtonText,
                                                            myButtonOption.palette.brightText());
                        }
                    }
                }
                QProxyStyle::drawControl(element, &myButtonOption, painter, widget);
            }
            break;
        default:
            QProxyStyle::drawControl(element, option, painter, widget);
    }
}

void CLStyleBase::drawComplexControl(QStyle::ComplexControl which, const QStyleOptionComplex* option
        , QPainter* painter, const QWidget* widget) const
{
    switch (which)
    {
        case CC_ComboBox:

            break;
        default:
            break;
    }
    return QProxyStyle::drawComplexControl(which, option, painter, widget);
}

QRect CLStyleBase::subControlRect(QStyle::ComplexControl whichControl, const QStyleOptionComplex* option
                                       , QStyle::SubControl whichSubControl, const QWidget* widget) const
{
    switch (whichControl)
    {
        case CC_ComboBox:
            {
                switch (whichSubControl)
                {
                    case SC_ComboBoxArrow:
                        break;
                    default:
                        break;
                }
                break;
            }
        default:
            break;
    }
    // 注意要习惯性的加上return, 以免出现不必要的错误，习惯好也可以加快速度
    return QProxyStyle::subControlRect(whichControl, option, whichSubControl, widget);
}

///
/// \brief CLMapleLeafStyle::standardPixmap     Qt内置了一批图标，一共有70个，不同的平台图标有差异
/// \param standardPixmap
/// \param opt
/// \param widget
/// \return
///
QPixmap CLStyleBase::standardPixmap(QStyle::StandardPixmap standardPixmap, const QStyleOption* opt
        , const QWidget* widget) const
{
    switch (standardPixmap)
    {
        case SP_ArrowDown:
            return QPixmap(":/img/css/array_down.png");
        default:
            break;
    }
    return QProxyStyle::standardPixmap(standardPixmap, opt, widget);
}

QIcon CLStyleBase::standardIcon(QStyle::StandardPixmap standardIcon, const QStyleOption* option
                                     , const QWidget* widget) const
{
    switch (standardIcon)
    {
        case SP_ArrowDown:
            return QIcon(":/img/css/array_down.png");
        default:
            break;
    }
    return QProxyStyle::standardIcon(standardIcon, option, widget);
}

bool CLStyleBase::event(QEvent* e)
{
    return QProxyStyle::event(e);
}

void CLStyleBase::drawPECheckBoxIndicator(const QStyleOption* option, QPainter* painter) const
{
    //commonstyle源码
//    if (opt->state & State_NoChange) {
//        p->setPen(opt->palette.foreground().color());
//        p->fillRect(opt->rect, opt->palette.brush(QPalette::Button));
//        p->drawRect(opt->rect);
//        p->drawLine(opt->rect.topLeft(), opt->rect.bottomRight());
//    } else {
//        qDrawShadePanel(p, opt->rect.x(), opt->rect.y(), opt->rect.width(), opt->rect.height(),
//                        opt->palette, opt->state & (State_Sunken | State_On), 1,
//                        &opt->palette.brush(QPalette::Button));
//    }


    // ohter
//    painter->save();
//    painter->setRenderHint(QPainter::Antialiasing, true);
//    if (option->state & State_MouseOver)
//    {
//        painter->setBrush(option->palette.alternateBase());
//    }
//    else
//    {
//        painter->setBrush(option->palette.base());
//    }
//    painter->drawRoundRect(option->rect.adjusted(+1, +1, -1, -1));

//    if (option->state & (State_On | State_NoChange))
//    {
//        QPixmap pixmap;
//        if (!(option->state & State_Enabled))
//        {
//            //pixmap.load(":/images/checkbox_checked_hover.png");
//            //pixmap.load(":/img/css/checkbox_checked.png");
//            //pixmap.load(":/images/checkbox_unchecked_hover.png");
//            // pixmap.load(":/img/css/checkbox_unchecked.png");
//            pixmap.load(":/images/checkmark-disabled.png");
//        }
//        else if (option->state & State_NoChange)
//        {
//            pixmap.load(":/images/checkmark-partial.png");
//        }
//        else
//        {
//            pixmap.load(":/images/checkmark.png");
//        }

//        QRect pixmapRect = pixmap.rect().translated(option->rect.topLeft()).translated(+2, -6);
//        QRect painterRect = visualRect(option->direction, option->rect, pixmapRect);
//        if (option->direction == Qt::RightToLeft)
//        {
//            painter->scale(-1.0, +1.0);
//            painterRect.moveLeft(-painterRect.right() - 1);
//        }
//        painter->drawPixmap(painterRect, pixmap);
//    }
//    painter->restore();


    // now
    QPixmap pixmap;
    if(option->state & State_On)
    {
//        if(option->state & State_MouseOver)
//        {
//            //pixmap.load(":/images/checkbox_checked_hover.png");
//        }
//        else
//        {
        pixmap.load(":/img/css/checkbox_fix_checked.png");
//        }
    }
    else
    {
//        if(option->state & State_MouseOver)
//        {
//            //pixmap.load(":/images/checkbox_unchecked_hover.png");
//        }
//        else
//        {
        pixmap.load(":/img/css/checkbox_fix_unchecked.png");
//        }

    }
    painter->drawPixmap(option->rect, pixmap);
}

void CLStyleBase::drawPERadioButtonIndicator(const QStyleOption* option, QPainter* painter) const
{
    // 源码
//    QRect ir = opt->rect;
//    p->setPen(opt->palette.dark().color());
//    p->drawArc(opt->rect, 0, 5760);
//    if (opt->state & (State_Sunken | State_On)) {
//        ir.adjust(2, 2, -2, -2);
//        p->setBrush(opt->palette.foreground());
//        bool oldQt4CompatiblePainting = p->testRenderHint(QPainter::Qt4CompatiblePainting);
//        p->setRenderHint(QPainter::Qt4CompatiblePainting);
//        p->drawEllipse(ir);
//        p->setRenderHint(QPainter::Qt4CompatiblePainting, oldQt4CompatiblePainting);
//    }

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPixmap(option->rect, QPixmap(":/img/css/radio_normal.png"));
    if (option->state & (State_Sunken | State_On))
    {
        painter->drawPixmap(option->rect, QPixmap(":/img/css/radio_selected.png"));
    }
    painter->restore();

}

void CLStyleBase::drawPEArrowDownIndicator(const QStyleOption* option, QPainter* painter) const
{

}

void CLStyleBase::drawPEPanelButtonCommand(const QStyleOption* option, QPainter* painter) const
{
    int delta = (option->state & State_MouseOver) ? 64 : 0;
    QColor slightlyOpaqueBlack(0, 0, 0, 63);
    QColor semiTransparentWhite(255, 255, 255, 127 + delta);
    QColor semiTransparentBlack(0, 0, 0, 127 - delta);

    int x, y, width, height;
    option->rect.getRect(&x, &y, &width, &height);
//! [12]

//! [13]
    QPainterPath roundRect = roundRectPath(option->rect);
//! [13] //! [14]
    int radius = qMin(width, height) / 2;
//! [14]

//! [15]
    QBrush brush;
//! [15] //! [16]
    bool darker;

    const QStyleOptionButton* buttonOption =
        qstyleoption_cast<const QStyleOptionButton*>(option);
    if (buttonOption
            && (buttonOption->features & QStyleOptionButton::Flat))
    {
        brush = option->palette.background();
        darker = (option->state & (State_Sunken | State_On));
    }
    else
    {
        if (option->state & (State_Sunken | State_On))
        {
            brush = option->palette.mid();
            darker = !(option->state & State_Sunken);
        }
        else
        {
            brush = option->palette.button();
            darker = false;
//! [16] //! [17]
        }
//! [17] //! [18]
    }
//! [18]

//! [19]
    painter->save();
//! [19] //! [20]
    painter->setRenderHint(QPainter::Antialiasing, true);
//! [20] //! [21]
    painter->fillPath(roundRect, brush);
//! [21] //! [22]
    if (darker)
//! [22] //! [23]
    {
        painter->fillPath(roundRect, slightlyOpaqueBlack);
    }
//! [23]

//! [24]
    int penWidth;
//! [24] //! [25]
    if (radius < 10)
    {
        penWidth = 3;
    }
    else if (radius < 20)
    {
        penWidth = 5;
    }
    else
    {
        penWidth = 7;
    }

    QPen topPen(semiTransparentWhite, penWidth);
    QPen bottomPen(semiTransparentBlack, penWidth);

    if (option->state & (State_Sunken | State_On))
    {
        qSwap(topPen, bottomPen);
    }
//! [25]

//! [26]
    int x1 = x;
    int x2 = x + radius;
    int x3 = x + width - radius;
    int x4 = x + width;

    if (option->direction == Qt::RightToLeft)
    {
        qSwap(x1, x4);
        qSwap(x2, x3);
    }

    QPolygon topHalf;
    topHalf << QPoint(x1, y)
            << QPoint(x4, y)
            << QPoint(x3, y + radius)
            << QPoint(x2, y + height - radius)
            << QPoint(x1, y + height);

    painter->setClipPath(roundRect);
    painter->setClipRegion(topHalf, Qt::IntersectClip);
    painter->setPen(topPen);
    painter->drawPath(roundRect);
//! [26] //! [32]

    QPolygon bottomHalf = topHalf;
    bottomHalf[0] = QPoint(x4, y + height);

    painter->setClipPath(roundRect);
    painter->setClipRegion(bottomHalf, Qt::IntersectClip);
    painter->setPen(bottomPen);
    painter->drawPath(roundRect);

    painter->setPen(option->palette.foreground().color());
    painter->setClipping(false);
    painter->drawPath(roundRect);

    painter->restore();
}

////绘制微调框向上向下按钮
//void CLBronzeStyle::drawBronzeSpinBoxButton(SubControl which, const QStyleOptionComplex *option
//                                            , QPainter *painter) const
//{
//    PrimitiveElement arrow = PE_IndicatorArrowLeft;
//    QRect buttonRect = option->rect;
//    if ((which == SC_SpinBoxUp) != (option->direction == Qt::RightToLeft))
//    {
//        arrow = PE_IndicatorArrowRight;
//        buttonRect.translate(buttonRect.width() / 2, 0);
//    }
//    buttonRect.setWidth((buttonRect.width() + 1) / 2);

//    QStyleOption buttonOpt(*option);

//    painter->save();
//    painter->setClipRect(buttonRect, Qt::IntersectClip);
//    if (!(option->activeSubControls & which))
//    {
//        buttonOpt.state &= ~(State_MouseOver | State_On | State_Sunken);
//    }
//    drawBronzeBevel(&buttonOpt, painter);

//    QStyleOption arrowOpt(buttonOpt);
//    arrowOpt.rect = subControlRect(CC_SpinBox, option, which).adjusted(+3, +3, -3, -3);
//    if (arrowOpt.rect.isValid())
//    {
//        drawPrimitive(arrow, &arrowOpt, painter);
//    }
//    painter->restore();
//}

///
/// \brief CLMapleLeafStyle::setTexture     修改调色板的Active, Disabled, Inactive三个状态的颜色
/// \param palette
/// \param role
/// \param pixmap
///
void CLStyleBase::setTexture(QPalette & palette, QPalette::ColorRole role,
                                  const QPixmap & pixmap)
{
    for (int i = 0; i < QPalette::NColorGroups; ++i)
    {
        QColor color = palette.brush(QPalette::ColorGroup(i), role).color();

        palette.setBrush(QPalette::ColorGroup(i), role, QBrush(color, pixmap));
    }
}

QPainterPath CLStyleBase::roundRectPath(const QRect & rect)
{
    int radius = qMin(rect.width(), rect.height()) / 2;
    int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);

    QPainterPath path;
    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
    path.closeSubpath();
    return path;
}
