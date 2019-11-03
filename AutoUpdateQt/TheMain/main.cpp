#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>

const QString c_strUpder = "LxUp_date.exe";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc == 1)
    {
        if(!QProcess::startDetached(c_strUpder))
        {
            QWidget widget;
            QMessageBox::warning(&widget,"警告信息","启动更新程序错误!\n可能主程序不存在或者被破坏!\n解决办法：重新安装程序!");
        }
        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
