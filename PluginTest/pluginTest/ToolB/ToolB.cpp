#include "ToolB.h"
#include <QApplication>
#include <QStyle>
#include <ToolBWidget.h>

CToolB::CToolB()
{
}

QString CToolB::name() const
{
    return "tool B";
}

QIcon CToolB::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_DriveCDIcon);
}

QWidget *CToolB::widget()
{
    CToolBWidget* widget = new CToolBWidget;
    return widget;
}
