#include "LMapleLeafStyle.h"
#include <QAbstractButton>
#include <QAbstractSpinBox>
#include <QDialogButtonBox>
#include <QPainter>
#include <QStyleOption>
#include <qdrawutil.h>

CLMapleLeafStyle::CLMapleLeafStyle(QStyle *style)
    : QProxyStyle(style)
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
void CLMapleLeafStyle::polish(QPalette &palette)
{


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

    return QProxyStyle::polish(palette);
}

void CLMapleLeafStyle::polish(QWidget *widget)
{

//    if (qobject_cast<QAbstractButton *>(widget) || qobject_cast<QAbstractSpinBox *>(widget))
//    {
//        widget->setAttribute(Qt::WA_Hover, true);
//    }
     return QProxyStyle::polish(widget);
}

void CLMapleLeafStyle::unpolish(QWidget *widget)
{

//    if (qobject_cast<QAbstractButton *>(widget) || qobject_cast<QAbstractSpinBox *>(widget))
//    {
//        widget->setAttribute(Qt::WA_Hover, false);
//    }
     return QProxyStyle::unpolish(widget);
}

///
/// \brief CLBronzeStyle::styleHint //返回一些关于样式外观的提示 --分别设置各种部件的布局，比如checkbox的text在左边或者在右边 --查询函数类
/// \param which
/// \param option
/// \param widget
/// \param returnData
/// \return
///
int CLMapleLeafStyle::styleHint(QStyle::StyleHint which, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    switch (which) {
    case SH_DialogButtonLayout:
        return int(QDialogButtonBox::WinLayout);
    default:
        break;
    }
    return QProxyStyle::styleHint(which, option, widget,
                                   returnData);
}

int CLMapleLeafStyle::pixelMetric(QStyle::PixelMetric which, const QStyleOption *option, const QWidget *widget) const
{
    switch (which)
    {
    // 返回0是因为不希望在默认的按钮旁边保留额外的空间
    case PM_ButtonDefaultIndicator:
        return 0;
        // 指示器大小是一个正方形
    case PM_IndicatorWidth:
    case PM_IndicatorHeight:
        return 16;
        // 控制指示器和其右边的文字之间的距离
    case PM_CheckBoxLabelSpacing:
        return 8;
        // QFrame,QPushButton,QSpinBox以及其他的一些窗口部件的线宽.
    case PM_DefaultFrameWidth:
        return 2;
        // 对于其他的PM_xxx值,从基类中继承像素规格的值
    default:
        break;
    }
    return QProxyStyle::pixelMetric(which, option, widget);
}

void CLMapleLeafStyle::drawPrimitive(QStyle::PrimitiveElement which, const QStyleOption *option
                                     , QPainter *painter, const QWidget *widget) const
{
    switch (which) {
    //会被QCheckBox,QGroupBox和QItemDelegate用来绘制选择指示器
//    case PE_IndicatorCheckBox:
//        drawBronzeCheckBoxIndicator(option, painter);
//        break;
//    case PE_PanelButtonCommand:
//        drawBronzeBevel(option, painter);
//        break;
//    case PE_Frame:
//        drawBronzeFrame(option, painter);
//        break;
    case PE_FrameLineEdit:
    {
        // 注意 commstyle源码里是这样的

//    case PE_FrameLineEdit:
//        proxy()->drawPrimitive(PE_Frame, opt, p, widget);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(QPen(option->palette.foreground(), 1.0));
        painter->drawRoundedRect(option->rect, 5, 5);
        painter->restore();

//        if (const QStyleOptionFrame *frame = qstyleoption_cast<const QStyleOptionFrame *>(opt)) {
//            if (pe == PE_FrameMenu || (frame->state & State_Sunken) || (frame->state & State_Raised)) {
//                qDrawShadePanel(painter, frame->rect, frame->palette, frame->state & State_Sunken,
//                                frame->lineWidth);
//            } else {
//                qDrawPlainRect(painter, frame->rect, frame->palette.foreground().color(), frame->lineWidth);
//            }
//        }
        break;
    }
    default:
       break;
    }
     QProxyStyle::drawPrimitive(which, option, painter, widget);

}

void CLMapleLeafStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option
                                   , QPainter *painter, const QWidget *widget) const
{
    QProxyStyle::drawControl(element, option, painter, widget);
}

void CLMapleLeafStyle::drawComplexControl(QStyle::ComplexControl which, const QStyleOptionComplex *option
                                          , QPainter *painter, const QWidget *widget) const
{
    QProxyStyle::drawComplexControl(which, option, painter, widget);
}

QRect CLMapleLeafStyle::subControlRect(QStyle::ComplexControl whichControl, const QStyleOptionComplex *option
                                       , QStyle::SubControl whichSubControl, const QWidget *widget) const
{
    QProxyStyle::subControlRect(whichControl, option, whichSubControl, widget);
}
