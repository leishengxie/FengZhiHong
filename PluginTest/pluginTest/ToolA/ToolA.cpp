#include "ToolA.h"
#include <QApplication>
#include <QStyle>
#include <ToolAWidget.h>

ToolA::ToolA()
{
}

QString ToolA::name() const
{
    return "computer tool";
}

QIcon ToolA::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    //QApplication::style()->standardIcon(QStyle::SP_DriveCDIcon);
}

QWidget *ToolA::widget()
{
    CToolAWidget* widget = new CToolAWidget;
    return widget;
}
