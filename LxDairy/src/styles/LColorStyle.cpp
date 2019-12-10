#include "LColorStyle.h"

CLColorStyle::CLColorStyle(QStyle *style)
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
void CLColorStyle::polish(QPalette &palette)
{

    //设置按钮颜色
    QColor bronze(207, 155, 95);
    //设置背景框颜色
    QColor veryLightBlue(239, 239, 247);
    //要加深的颜色
    QColor lightBlue(223, 223, 239);
    //选中后的颜色
    QColor darkBlue(95, 95, 191);

    //创建一个新的面板
    palette = QPalette(bronze);
    //设置背景
    palette.setBrush(QPalette::Window, QColor("white"));
    //设置背景框颜色
    palette.setBrush(QPalette::Base, veryLightBlue);
    //设置加深的颜色
    palette.setBrush(QPalette::AlternateBase, lightBlue);
    //设置选中高亮的颜色
    palette.setBrush(QPalette::Highlight, darkBlue);
    //设置禁用的样式
    palette.setBrush(QPalette::Disabled, QPalette::Highlight, Qt::darkGray);
}

void CLColorStyle::polish(QWidget *widget)
{
    return QProxyStyle::polish(widget);
}

void CLColorStyle::unpolish(QWidget *widget)
{
    return QProxyStyle::unpolish(widget);
}

