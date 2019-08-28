#include "mysql.h"
#include<QVariant>
#include<QCoreApplication>
#include<QDir>
#include<QPixmap>
#include<QDebug>

#include <time.h>
MySql::MySql()
{
    

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
bool MySql::WriteData(QString zhanghao, QString time,QString wather,QString xinqing,QString neirong)
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
QStringList MySql::shuaxin(QString zhanghao)
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
QStringList MySql::huoquqita(QString zhanghao, QString riqi)
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
int MySql::zhanghao(QString mima,QString beizhu,QString wangming,QString qianming,QString touxiang)
{
    QSqlQuery query;
    qsrand(time(NULL));
    bool ok=true;
    while (ok) {
        int zhanghao=111111111+qrand()%2000000000;
        query.exec("select * from zhanghao");
        bool ok1=false;
        while (query.next())
        {
            if(query.value(0).toInt()==zhanghao)
            {
                ok1=true;
            }
        }
        if(ok1==false)
        {
          ok=false;
          QString ziti="华文楷体,14,-1,5,50,0,0,0,0,0,Regular";//编辑界面初始化字体
          QString beijing=":/image/1.jpg";//初始化背景
    QString path=QCoreApplication::applicationDirPath()+"/file";
    isDirExist(path);
    QString tupian=path+QString("/%1.png").arg(zhanghao);
    QPixmap(touxiang).save(tupian,"png");
        query.prepare("INSERT INTO zhanghao (zhanghao,mima,wangming,qianming,beizhu,touxiang,ziti,beijing) "
                             "VALUES (?, ?, ?,?, ?, ?,?,?)");
               query.bindValue(0, zhanghao);
               query.bindValue(1, mima);
               query.bindValue(2, wangming);
               query.bindValue(3, qianming);
               query.bindValue(4, beizhu);
               query.bindValue(5, tupian);
               query.bindValue(6, ziti);
               query.bindValue(7, beijing);
               query.exec();
               return zhanghao;
        }
    }

}
QString MySql::wangjimima(QString zhanghao,QString beizhu,QString mima)
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
bool MySql::yanzheng(QString zhanghao,QString mima)
{
    QSqlQuery query;
    query.exec("select * from zhanghao");
    while (query.next())
    {
        if(query.value(0).toInt()==zhanghao.toInt()&&query.value(1).toString()==mima)
        {
              return true;
        }
    }
    return false;
}
QStringList MySql::zhumaintongbu(QString zhanghao)
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
void MySql::setziti(QString zhanghao,QString ziti)
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
void MySql::SetXinXi(QString zhanghao, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian)
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
