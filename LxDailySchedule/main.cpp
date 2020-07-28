#include "DailyScheduleWidget.h"
#include <QApplication>

/***
 *
 *  日作息时间表
 *
 *
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CDailyScheduleWidget w;
    w.show();

    return a.exec();
}
