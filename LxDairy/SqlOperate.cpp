#include "SqlOperate.h"
#include<QVariant>
#include<QCoreApplication>
#include<QDir>
#include<QPixmap>
#include<QDebug>
#include <QSqlQuery>

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
    QSqlQuery query;
     query.exec("create table zhanghao (zhanghao int primary key,mima varchar,"
                "wangming varchar,qianming varchar,beizhu varchar,touxiang varcher,"
                "ziti varcher,beijing varcher)");
     query.exec("create table mobile (zhanghao int ,time varchar,wather varchar,xinqing varchar,neirong varcher)");
     return true;
}

bool isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
        return true;
    }
    else
    {
        bool ok = dir.mkdir(fullPath);//只创建一级子目录，即必须保证上级目录存在
        return ok;
    }
}
bool CSqlOperate::WriteData(QString zhanghao, QString time,QString wather,QString xinqing,QString neirong)
{
    QSqlQuery query;
    bool ok=query.prepare("INSERT INTO mobile (zhanghao,time,wather,xinqing,neirong) "
                          "VALUES (?, ?, ?,?, ?)");
    query.bindValue(0, zhanghao.toInt());
    query.bindValue(1, time);
    query.bindValue(2, wather);
    query.bindValue(3, xinqing);
    query.bindValue(4, neirong);
    query.exec();
    return ok;
}
QStringList CSqlOperate::shuaxin(QString zhanghao)
{
    QSqlQuery query;
    QStringList list;
    query.exec("select * from mobile");
    while (query.next())
    {
        if(zhanghao.toInt()==query.value(0).toInt())
        {
            list.append(query.value(1).toString());  //时间
        }
    }
    return list;
}
QStringList CSqlOperate::huoquqita(QString zhanghao, QString riqi)
{
    QSqlQuery query;
    QStringList list;
    query.exec("select * from mobile");
    while (query.next())
    {
        if(query.value(0).toInt()==zhanghao.toInt()&&query.value(1).toString()==riqi)
        {
            list<<query.value(2).toString()<<query.value(3).toString()<<query.value(4).toString();
        }
    }
    return list;
}

int CSqlOperate::registerAccount(QString strUserName,QString strPasswd)
{
    QSqlQuery query;

    query.exec("select * from tUser");
    while (query.next())
    {
        if(query.value(0).toString() == strUserName)
        {
            return 1; // user name already existes
        }
    }

    query.prepare("INSERT INTO tUser (strUserName, strPasswd) VALUES (?, ?)");
    query.bindValue(0, strUserName);
    query.bindValue(1, strPasswd);
    query.exec();
    return 0;
}

QString CSqlOperate::wangjimima(QString zhanghao,QString beizhu,QString mima)
{
    QSqlQuery query;
    query.exec("select * from zhanghao");
    while (query.next())
    {
        if(query.value(0).toInt()==zhanghao.toInt()&&query.value(4).toString()==beizhu)
        {
            query.exec(QString("update zhanghao set [mima]='%1' where [zhanghao]='%2';").arg(mima).arg(zhanghao));
            return "OK!修改完成！！";
        }
    }
    return "账号或备注不正确！请检查！！";
}
bool CSqlOperate::login(QString strUserName, QString strPasswd)
{
    QSqlQuery query;
    query.exec("select * from tUser");
    while (query.next())
    {
        if(query.value(0).toString() == strUserName
                && query.value(1).toString() == strPasswd)
        {
            return true;
        }
    }
    return false;
}
QStringList CSqlOperate::zhumaintongbu(QString zhanghao)
{
    QSqlQuery query;
    query.exec("select * from zhanghao");
    QStringList list;
    while (query.next())
    {
        if(query.value(0).toInt()==zhanghao.toInt())
        {
            //网名 签名 头像 字体 背景
            list<<query.value(2).toString()<<query.value(3).toString()
               <<query.value(5).toString()<<query.value(6).toString()
              <<query.value(7).toString();
        }
    }
    return list;
}
void CSqlOperate::setziti(QString zhanghao,QString ziti)
{
    QSqlQuery query;
    query.exec("select * from zhanghao");
    while (query.next())
    {
        if(query.value(0).toInt()==zhanghao.toInt())
        {
            query.exec(QString("update zhanghao set [ziti]='%1' where [zhanghao]='%2';").arg(ziti).arg(zhanghao));
            return;
        }
    }
}
void CSqlOperate::SetXinXi(QString zhanghao, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian)
{
    QString path=QCoreApplication::applicationDirPath()+"/file";
    isDirExist(path);
    QString tupian=path+QString("/%1.png").arg(zhanghao);
    QPixmap(touxiang).save(tupian,"png");
    QSqlQuery query;
    query.exec("select * from zhanghao");
    while (query.next())
    {
        if(query.value(0).toInt()==zhanghao.toInt())
        {//zhanghao,mima,wangming,qianming,beizhu,touxiang,ziti，beijing
            query.exec(QString("update zhanghao set [ziti]='%1' where [zhanghao]='%2';").arg(ziti).arg(zhanghao));
            query.exec(QString("update zhanghao set [beijing]='%1' where [zhanghao]='%2';").arg(beijing).arg(zhanghao));
            query.exec(QString("update zhanghao set [touxiang]='%1' where [zhanghao]='%2';").arg(tupian).arg(zhanghao));
            query.exec(QString("update zhanghao set [wangming]='%1' where [zhanghao]='%2';").arg(wangming).arg(zhanghao));
            query.exec(QString("update zhanghao set [qianming]='%1' where [zhanghao]='%2';").arg(geqian).arg(zhanghao));
            return;
        }
    }
}
