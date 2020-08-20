#include "RenameToolPlugin.h"
#include <QApplication>
#include <QStyle>
#include "RenameWidget.h"

CRenameToolPlugin::CRenameToolPlugin(QObject *parent)
    : QObject(parent)
{

}

QString CRenameToolPlugin::name() const
{
    return "批量重命名";
}

QIcon CRenameToolPlugin::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    //QApplication::style()->standardIcon(QStyle::SP_DriveCDIcon);
}

QWidget *CRenameToolPlugin::widget()
{
    CRenameWidget* widget = new CRenameWidget;
    return widget;
}
