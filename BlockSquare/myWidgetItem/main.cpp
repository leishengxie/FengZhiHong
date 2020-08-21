#include "LoginWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    CLoginWidget w;
    w.show();

    return a.exec();
}



