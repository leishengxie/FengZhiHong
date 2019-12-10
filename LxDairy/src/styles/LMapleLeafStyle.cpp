#include "LMapleLeafStyle.h"
#include <QAbstractButton>
#include <QAbstractSpinBox>
#include <QDialogButtonBox>
#include <QPainter>
#include <QStyleOption>
#include <qdrawutil.h>
#include <QStyleFactory>

CLMapleLeafStyle::CLMapleLeafStyle(QStyle* style)
    : QProxyStyle(QStyleFactory::create("WindowsVista")) // 默认windows风格
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
void CLMapleLeafStyle::polish(QPalette & palette)
{

}

