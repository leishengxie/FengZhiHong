#include "RenameWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CRenameWidget w;
    w.show();

    return a.exec();
}
