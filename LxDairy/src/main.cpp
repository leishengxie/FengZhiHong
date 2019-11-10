#include "DairyMainWindow.h"
#include "LoginWidget.h"
#include "SqlOperate.h"
#include "SkinWidget.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>


static const QString s_strUpder = "LxDairyUpd.exe";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc == 1)
    {
        if(!QProcess::startDetached(s_strUpder))
        {
            QWidget widget;
            QMessageBox::warning(&widget,"警告信息","启动更新程序错误!\n可能主程序不存在或者被破坏!\n解决办法：重新安装程序!");
        }
        return 0;
    }

    if (!CSqlOperate::connect("LxDairy.db"))
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
