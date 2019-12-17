#include "SqlOperate.h"
#include<QVariant>
#include<QCoreApplication>
#include<QDir>
#include<QPixmap>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <time.h>



CSqlOperate::CSqlOperate(QObject *parent) : QObject(parent)
{


}

bool CSqlOperate::connect(QString strDbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(strDbName);
    if ( !db.open())
    {
        return false;
    }
    //    QSqlQuery query;
    //    query.exec("create table zhanghao (zhanghao int primary key,mima varchar,"
    //               "wangming varchar,qianming varchar,beizhu varchar,touxiang varcher,"
    //               "ziti varcher,beijing varcher)");
    //    query.exec("create table mobile (zhanghao int ,time varchar,wather varchar,xinqing varchar,neirong varcher)");
    return true;
}

void CSqlOperate::createTable()
{
    QSqlQuery query;
    QString strSql=" CREATE TABLE IF NOT EXISTS tUser( " \
                   "uid INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
                   "user_name  varcher(32) NOT NULL," \
                   "passwd  varcher(16) NOT NULL)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    strSql = "CREATE TABLE IF NOT EXISTS tDairy(" \
    "did int PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
    "uid int NOT NULL," \
    "title varcher," \
    "datetime  varcher," \
    "weather varcher," \
    "tag varcher," \
    "content varcher," \
    "CONSTRAINT 'fk_user_uid' FOREIGN KEY ('uid') REFERENCES 'tUser' ('uid') ON DELETE CASCADE ON UPDATE CASCADE)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    strSql = "CREATE TABLE IF NOT EXISTS tAPasswd(" \
    "aid int PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
    "uid int NOT NULL," \
    "item varcher," \
    "account  varcher," \
    "passwd varcher," \
    "CONSTRAINT 'fk_user_uid' FOREIGN KEY ('uid') REFERENCES 'tUser' ('uid') ON DELETE CASCADE ON UPDATE CASCADE)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }
}


