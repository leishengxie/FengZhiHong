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
    init();
}
#else
CDairyAndroidApp::CDairyAndroidApp(int &argc, char **argv, int nQtVersion)
    : QApplication(argc, argv, nQtVersion)
{
    init();
}
#endif

CDairyAndroidApp::~CDairyAndroidApp()
{

}

//bool CDairyAndroidApp::notify(QObject *obj, QEvent *e)
//{
//    return QApplication::notify(obj, e);
//}



void CDairyAndroidApp::setUserInfo(const T_UserInfo &tUserInfo)
{
    s_tUserInfo = tUserInfo;
}



T_UserInfo CDairyAndroidApp::userInfo()
{

    return s_tUserInfo;
}

void CDairyAndroidApp::init()
{
    // qml使用settings所需
    setApplicationName("LxDairyAndroid"); // 1
    setOrganizationDomain("lx.com"); //2
    setOrganizationName("Lx"); // 3


    setAttribute(Qt::AA_EnableHighDpiScaling);
}
