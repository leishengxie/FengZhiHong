#include "DairyApp.h"
#include <QtDebug>


T_UserInfo CDairyApp::s_tUserInfo;

CDairyApp::CDairyApp(int argc, char *argv[])
    : QApplication(argc, argv)
{
    init();
}

CDairyApp::~CDairyApp()
{

}

bool CDairyApp::notify(QObject *obj, QEvent *e)
{
    return QApplication::notify(obj, e);
}



void CDairyApp::setUserInfo(const T_UserInfo &tUserInfo)
{
    s_tUserInfo = tUserInfo;
}



T_UserInfo CDairyApp::userInfo()
{

    return s_tUserInfo;
}

void CDairyApp::init()
{

}
