#include "InductiveBookWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CInductiveBookWidget w;
    w.show();

    return a.exec();
}
