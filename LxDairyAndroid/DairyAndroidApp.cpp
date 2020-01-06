#include "DairyAndroidApp.h"
#include <QtDebug>


T_UserInfo CDairyAndroidApp::s_tUserInfo;

//CDairyAndroidApp::CDairyAndroidApp(int argc, char *argv[])
//    : QApplication(argc, argv)
//{

//}
#ifdef Q_QDOC
CDairyAndroidApp::CDairyAndroidApp(int &argc, char **argv)
    : QApplication(argc, argv)
{
}
#else
CDairyAndroidApp::CDairyAndroidApp(int &argc, char **argv, int nQtVersion)
    : QApplication(argc, argv, nQtVersion)
{

}
#endif

CDairyAndroidApp::~CDairyAndroidApp()
{

}

//bool CDairyAndroidApp::notify(QObject *obj, QEvent *e)
//{
//    return QApplication::notify(obj, e);
//}



CDairyAndroidApp::setUserInfo(const T_UserInfo &tUserInfo)
{
    s_tUserInfo = tUserInfo;
}



T_UserInfo CDairyAndroidApp::userInfo()
{

    return s_tUserInfo;
}

void CDairyAndroidApp::init()
{

}
