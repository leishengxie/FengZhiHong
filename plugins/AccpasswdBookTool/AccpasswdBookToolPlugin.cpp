#include "AccpasswdBookToolPlugin.h"
#include <QApplication>
#include <QStyle>
#include "AccPasswdWidget.h"

CAccpasswdBookToolPlugin::CAccpasswdBookToolPlugin(QObject *parent) : QObject(parent)
{

}

QString CAccpasswdBookToolPlugin::name() const
{
    return "账号密码簿";
}

QIcon CAccpasswdBookToolPlugin::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_DriveCDIcon);
}

QWidget *CAccpasswdBookToolPlugin::widget()
{
    CAccPasswdWidget* widget = new CAccPasswdWidget;
    return widget;
}
