#include "DailyScheduleWidget.h"
#include <QApplication>
#include <QMessageBox>
#include <QStandardPaths>
#include "DailyScheduleSqlOperate.h"

/***
 *
 *  日作息时间表
 *
 *
*/

static const QString s_strDocDirDB = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + "LxDailySchedule.db";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!CDailyScheduleSqlOperate::getInstance()->connectSqlite(s_strDocDirDB))
    {
        QMessageBox::information(NULL, "ERROR", "数据库连接失败！");
        return -1;
    }
    CDailyScheduleSqlOperate::getInstance()->createTable();

    CDailyScheduleWidget w;
    w.show();

    return a.exec();
}
