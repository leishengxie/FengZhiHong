#include "DairyMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CDairyMainWindow w;
    w.show();

    return a.exec();
}
