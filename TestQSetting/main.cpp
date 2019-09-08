#include "mainwindow.h"
#include <QApplication>
#include "app.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    App::ConfigFile = QString("%1/%2.ini").arg(QUIHelper::appPath()).arg(QUIHelper::appName());
    App::readConfig();
    App::readSendData();
    App::readDeviceData();

    return a.exec();
}
