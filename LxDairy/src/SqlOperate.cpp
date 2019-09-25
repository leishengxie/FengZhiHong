#include "SqlOperate.h"
#include<QVariant>
#include<QCoreApplication>
#include<QDir>
#include<QPixmap>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <time.h>
#include "User.h"


CSqlOperate::CSqlOperate(QObject *parent) : QObject(parent)
{
    //    model = new QSqlRelationalTableModel (this);
    //    model->setTable("stations_train_pass"); //要打开的表
    //    // 模型中的所有更改将被缓存,直到submitAll()或revertAll()！
    //    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    //    model->setRelation(1,QSqlRelation("stations","sid","sname"));
    //    model->select();

    //       model->revertAll(); //撤销上次sql操作
    //       model->submitAll(); //提交上次sql操作
    //model->setFilter(QObject::tr("snumber like '%1'").arg("%"));

    //    model->setFilter(QObject::tr("tid= '%1'").arg(name));
    //        model->select();
    //            QTableView *view = new QTableView;
    //            view->setModel(model);
    //            view->show();

    //    ui->tvMainList->setModel(model);
    //    //格式化表
    //    this->model->removeColumn(this->model->fieldIndex("fid"));
    //    this->model->removeColumn(this->model->fieldIndex("flag"));
    //    this->model->setHeaderData(0,Qt::Horizontal,tr("名称"));
    //    this->model->setHeaderData(1,Qt::Horizontal,tr("类型"));
    //    this->model->setHeaderData(2,Qt::Horizontal,tr("价格"));
    //    this->model->setHeaderData(3,Qt::Horizontal,tr("热度"));

    //按热度值获取表中数据 并按降序排列
    //    this->model->setFilter("fhot_count>10 order by fhot_count desc");
    //    this->model->select();

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
                   "user_name  TEXT(32) NOT NULL," \
                   "passwd  TEXT(16) NOT NULL)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    strSql = "CREATE TABLE IF NOT EXISTS tDairy(" \
    "did INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
    "uid INTEGER NOT NULL," \
    "title TEXT," \
    "datetime  TEXT," \
    "weather TEXT," \
    "tag TEXT," \
    "content TEXT," \
    "CONSTRAINT 'fk_user_uid' FOREIGN KEY ('uid') REFERENCES 'tUser' ('uid') ON DELETE CASCADE ON UPDATE CASCADE)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }
}




int CSqlOperate::registerAccount(QString strUserName, QString strPasswd)
{
    QSqlQuery query;

    // 检查账号是否已经存在
    query.exec("select * from tUser");
    while (query.next())
    {
        if(query.value("user_name").toString() == strUserName)
        {
            return 1; // user name already existes
        }
    }
    //INSERT INTO tUser(user_name, passwd) VALUES('leisx', '0406aaaaa');

    // test1
    //    query.prepare("INSERT INTO tUser(user_name, passwd) VALUES(:user_name, :passwd)");
    //    query.bindValue(":user_name", strUserName);
    //    query.bindValue(":passwd", strPasswd);

    // test2
    query.prepare("INSERT INTO tUser(user_name, passwd) VALUES(?, ?)");
    query.bindValue(0, strUserName);
    query.bindValue(1, strPasswd);

    //    QString strSql = "INSERT INTO tUser(user_name, passwd) VALUES('" +
    //            strUserName + "', '" +
    //            strPasswd + "')";
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return 2;
    }
    return 0;
}


bool CSqlOperate::login(QString strUserName, QString strPasswd)
{
    QSqlQuery query;
    query.exec("select * from tUser");
    while (query.next())
    {
        if(query.value("user_name").toString() == strUserName
                && query.value("passwd").toString() == strPasswd)
        {
            int uid = query.value("uid").toInt();
            CUser::getInstance()->setUid(uid);
            CUser::getInstance()->setUserName(strUserName);

            getDairyList(uid);
            return true;
        }
    }
    return false;
}

    // 读取日记
void CSqlOperate::getDairyList(int uid)
{
    QSqlQuery query;
    QList<CDairy> lstDairy;
    query.exec("select * from tDairy where uid = '" + QString::number(uid) + "'");
    while (query.next())
    {
        //为避免内存占用只需要did和datetime
        CDairy dairy;
        dairy.setDid(query.value("did").toInt());
        dairy.setTitle(query.value("title").toString());
        dairy.setDateTime(query.value("datetime").toString());
//                dairy.setTag(query.value("tag").toString());
//                dairy.setWeather(query.value("weather").toString());
//                dairy.setContent(query.value("content").toString());
        lstDairy.append(dairy);
        CUser::getInstance()->setLstDairy(lstDairy);
        //CUser::getInstance()->loadDairyList(lstDairy);
    }
}

CDairy CSqlOperate::getDairy(int did, bool &bOk)
{
    CDairy dairy;
    QSqlQuery query;
    query.exec("select * from tDairy where uid = '"
               + QString::number(CUser::getInstance()->getUid())
               + "' and did = '" + QString::number(did) + "'");
    if (query.next())
    {
        bOk = true;
        dairy.setDid(query.value("did").toInt());
        dairy.setTitle(query.value("title").toString());
        dairy.setDateTime(query.value("datetime").toString());
        dairy.setTag(query.value("tag").toString());
        dairy.setWeather(query.value("weather").toString());
        dairy.setContent(query.value("content").toString());
    }
    else
    {
        bOk = false;
    }
    return dairy;
}

QList<CDairy> CSqlOperate::getListDairyByDate(QString strFormatDate)
{
    // eg: select * from tDairy where substr(date(datetime),1,7) = '2019-09';
    //
    QList<CDairy> lstDairy;
    QSqlQuery query;
    QString strSql = QString("select * from tDairy where substr(date(datetime),1,%1) = '%2'")
                     .arg(strFormatDate.length())
                     .arg(strFormatDate);
    bool ok = query.exec(strSql);

    if (!ok)
    {
        qDebug() << query.lastError();
        return lstDairy;
    }
    while (query.next())
    {
        CDairy dairy;
        dairy.setDid(query.value("did").toInt());
        dairy.setTitle(query.value("title").toString());
        dairy.setDateTime(query.value("datetime").toString());
        dairy.setTag(query.value("tag").toString());
        dairy.setWeather(query.value("weather").toString());
        dairy.setContent(query.value("content").toString());
        lstDairy.append(dairy);
    }
    return lstDairy;
}

void CSqlOperate::saveDairy(CDairy dairy)
{
    QSqlQuery query;
    if (dairy.isNewDairy())
    {
        bool ok = query.prepare("INSERT INTO tDairy(uid, title,datetime,tag,weather,content) "
                                "VALUES (?, ?, ?, ?, ?, ?)");
        query.bindValue(0, CUser::getInstance()->getUid());
        query.bindValue(1, dairy.getTitle());
        query.bindValue(2, dairy.getDateTime());
        query.bindValue(3, dairy.getTag());
        query.bindValue(4, dairy.getWeather());
        query.bindValue(5, dairy.getContent());
        ok = query.exec();
        if (!ok)
        {
            qDebug() << query.lastError();
            return;
        }

        // 重新获取今天的日记
        //select max(did) from tDairy
        //select * from tDairy WHERE did = (select max(did) from tDairy)
        //select top 1 * From tDairy Order by did Desc #sqlite没有top函数
        getDairyList(CUser::getInstance()->getUid());
    }
    else
    {
        QString strSql = QString("update tDairy set title='%1', tag='%2', weather='%3', content='%4' where did='%5'")
                         .arg(dairy.getTitle())
                         .arg(dairy.getTag())
                         .arg(dairy.getWeather())
                         .arg(dairy.getContent())
                         .arg(dairy.getDid());
        bool ok = query.exec(strSql);

        if (!ok)
        {
            qDebug() << query.lastError();
        }
    }
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

void CSqlOperate::test()
{
    QSqlQuery query;
    query.exec("select max(did) from tDairy");
    while (query.next())
    {
        qDebug() << "maxid = " << query.value(0).toInt();
    }

}
