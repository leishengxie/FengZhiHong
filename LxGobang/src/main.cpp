#include "GobangGameWidget.h"

//#include "core/Judge.h"
//#include "core/Player.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CGobangGameWidget w;
    w.show();
    int nRet = a.exec();
    return nRet;
}
