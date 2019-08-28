#include "mainwindow.h"
#include <QApplication>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include"denglv.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("data.db");
    if ( !db.open()){   
    return 0;
    }//if
    QSqlQuery query;
     query.exec("create table zhanghao (zhanghao int primary key,mima varchar,"
                "wangming varchar,qianming varchar,beizhu varchar,touxiang varcher,"
                "ziti varcher,beijing varcher)");
     query.exec("create table mobile (zhanghao int ,time varchar,wather varchar,xinqing varchar,neirong varcher)");
    denglv w;
    w.show();

    return a.exec();
}
