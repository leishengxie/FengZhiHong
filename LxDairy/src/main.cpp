#include "DairyMainWindow.h"
#include "LoginWidget.h"
#include "SqlOperate.h"
#include "SkinWidget.h"
#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!CSqlOperate::connect("LxDairy.db"))
    {
        QMessageBox::information(NULL, "ERROR", "数据库连接失败！");
        return -1;
    }
    CSqlOperate::createTable();
    CSkinWidget::loadQssStyle();

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
