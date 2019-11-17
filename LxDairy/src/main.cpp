#include "DairyMainWindow.h"
#include "LoginWidget.h"
#include "SqlOperate.h"
#include "SkinWidget.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>
#include <QStandardPaths>


static const QString s_strUpder = "LxDairyUpd.exe";

static const QString s_strDataDirDB = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + "LxDairy.db";
static const QString s_strUserDirDB = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/" + "LxDairy.db";
static const QString s_strDocDirDB = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + "LxDairy.db";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef QT_NO_DEBUG
    //release mode
    if (argc == 1)
    {
        if(!QProcess::startDetached(s_strUpder))
        {
            QWidget widget;
            QMessageBox::warning(&widget,"警告信息","启动更新程序错误!\n可能主程序不存在或者被破坏!\n解决办法：重新安装程序!");
        }
        return 0;
    }
#else

#endif

    // 为了保证用户卸载程序时，不删除用户的数据,本程序使用用户文档路径
    //static const QString s_strAppDirDB = QCoreApplication::applicationDirPath() + "/" + "LxDairy.db";
    if (!CSqlOperate::connect(s_strDocDirDB))
    {
        QMessageBox::information(NULL, "ERROR", "数据库连接失败！");
        return -1;
    }
    CSqlOperate::createTable();
    CSkinWidget::loadQssStyle();

//    QApplication::setOrganizationName("Lx");
//    QApplication::setApplicationName("LxDairy");
//    QApplication::setApplicationVersion("0.1.0");

    CLoginWidget l;
    l.show();

    //    CDairyMainWindow w;
    //    w.show();


    //另一种登录，主界面注销切换方式
    //    CLoginWidget l;
    //    l.show();
    //    QObject::connect(&l, SIGNAL(mainshow()), &w, SLOT(receiverLander()));
    //    QObject::connect(&w, SIGNAL(landerShow()), &l, SLOT(receiverLogout()));



    // 应用程序消息循环
    return a.exec();
}
