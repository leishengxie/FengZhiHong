#include "DairyApp.h"
#include <QtDebug>

T_UserInfo CDairyApp::s_tUserInfoLocal;
T_UserInfo CDairyApp::s_tUserInfoNet;
CDairyApp::E_LoginType CDairyApp::s_eLoginType = CDairyApp::EL_Local;

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

CDairyApp::setUserInfoLocal(const T_UserInfo &tUserInfo)
{
    s_tUserInfoLocal = tUserInfo;
    s_eLoginType = CDairyApp::EL_Local;
}

CDairyApp::setUserInfoNet(const T_UserInfo &tUserInfo)
{
    s_tUserInfoNet = tUserInfo;
    s_eLoginType = CDairyApp::EL_Net;
}

T_UserInfo CDairyApp::userInfoLocal()
{
    return s_tUserInfoLocal;
}

T_UserInfo CDairyApp::userInfoNet()
{
    return s_tUserInfoNet;
}

T_UserInfo CDairyApp::userInfo()
{
    if (s_eLoginType == CDairyApp::EL_Local)
    {
        return s_tUserInfoLocal;
    }
    return s_tUserInfoNet;
}

void CDairyApp::init()
{

}
