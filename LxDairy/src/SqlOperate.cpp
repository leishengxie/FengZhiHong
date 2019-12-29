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

    strSql = "CREATE TABLE IF NOT EXISTS tAPasswd(" \
    "aid INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
    "uid INTEGER NOT NULL," \
    "item TEXT," \
    "account  TEXT," \
    "passwd TEXT," \
    "CONSTRAINT 'fk_user_uid' FOREIGN KEY ('uid') REFERENCES 'tUser' ('uid') ON DELETE CASCADE ON UPDATE CASCADE)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }
}




bool CSqlOperate::registerAccount(QString strUserName, QString strPasswd, QString & strErr)
{
    QSqlQuery query;

    // 检查账号是否已经存在
    query.exec("select * from tUser");
    while (query.next())
    {
        if(query.value("user_name").toString() == strUserName)
        {
            strErr = "该用户名已经被注册！！";
            return false;
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

//    query.prepare("INSERT INTO tUser(user_name, passwd, nick_name) VALUES(?, ?, ?)");
//    query.bindValue(0, strUserName);
//    query.bindValue(1, strPasswd);
//    query.bindValue(2, strUserName);

    //    QString strSql = "INSERT INTO tUser(user_name, passwd) VALUES('" +
    //            strUserName + "', '" +
    //            strPasswd + "')";
    if (!query.exec())
    {
        strErr =  query.lastError().text();
        return false;
    }
    return true;
}


bool CSqlOperate::login(QString strUserName, QString strPasswd, T_UserInfo & tUserInfo, QString & strErr)
{
    QSqlQuery query;
    query.exec("select * from tUser where user_name = '" + strUserName + "'");
    if (!query.next())
    {
        strErr = "账号不存在，请注册账号";
        return false;
    }

    query.exec("select * from tUser where user_name = '" + strUserName + "' and passwd = '" + strPasswd + "'");
    if (!query.next())
    {
        strErr = "密码错误";
        return false;
    }

    //QSqlRecord rec = q.record();
    tUserInfo.uid = query.value("uid").toInt();
    //tUserInfo.strNickName = query.value("nick_name").toString();
    tUserInfo.strNickName = query.value("user_name").toString();
    return true;
}


    // 读取日记
QList<CDairy> CSqlOperate::getDairyList(int uid)
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
    }
    return lstDairy;
}

CDairy CSqlOperate::getDairy(int did, int uid, bool &bOk)
{
    CDairy dairy;
    QSqlQuery query;
    query.exec("select * from tDairy where uid = '"
               + QString::number(uid)
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

QList<CDairy> CSqlOperate::getListDairyByLimit(QString strFormatDate, QString strTagName)
{
    // eg: select * from tDairy where substr(date(datetime),1,7) = '2019-09';
    //
    QList<CDairy> lstDairy;
    QSqlQuery query;
    QString strSql;
    if (!strFormatDate.isEmpty() && strTagName.isEmpty())
    {
        strSql = QString("select * from tDairy where substr(date(datetime),1,%1) = '%2'")
                .arg(strFormatDate.length())
                .arg(strFormatDate);
    }
    else if (strFormatDate.isEmpty() && !strTagName.isEmpty())
    {
        strSql = QString("select * from tDairy where tag = '%1'").arg(strTagName);
    }
    else if (!strFormatDate.isEmpty() && !strTagName.isEmpty())
    {
        strSql = QString("select * from tDairy where substr(date(datetime),1,%1) = '%2' and tag = '%3'")
                .arg(strFormatDate.length())
                .arg(strFormatDate)
                .arg(strTagName);
    }
    else
    {
        strSql = QString("select * from tDairy");
    }
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

bool CSqlOperate::saveDairy(const CDairy & dairyModify, CDairy & dairySaved)
{
    QSqlQuery query;
    dairySaved = dairyModify;
    if (dairyModify.isNewDairy())
    {
        bool ok = query.prepare("INSERT INTO tDairy(uid, title,datetime,tag,weather,content) "
                                "VALUES (?, ?, ?, ?, ?, ?)");
        query.bindValue(0, dairyModify.getUid());
        query.bindValue(1, dairyModify.getTitle());
        query.bindValue(2, dairyModify.getDateTime());
        query.bindValue(3, dairyModify.getTag());
        query.bindValue(4, dairyModify.getWeather());
        query.bindValue(5, dairyModify.getContent());
        ok = query.exec();
        if (!ok)
        {
            qDebug() << query.lastError();
            return false;
        }

        // 重新获取今天的日记did
        //select max(did) from tDairy
        //select * from tDairy WHERE did = (select max(did) from tDairy)
        //select top 1 * From tDairy Order by did Desc #sqlite没有top函数
        //getDairyList(CUser::getInstance()->getUid());
        ok = query.exec("select max(did) from tDairy");
        if (!ok)
        {
            qDebug() << query.lastError();
            return false;
        }
        if (query.next())
        {
            dairySaved.setDid(query.value(0).toInt());
        }
    }
    else
    {
        QString strSql = QString("update tDairy set title='%1', tag='%2', weather='%3', content='%4' where did='%5'")
                         .arg(dairyModify.getTitle())
                         .arg(dairyModify.getTag())
                         .arg(dairyModify.getWeather())
                         .arg(dairyModify.getContent())
                         .arg(dairyModify.getDid());
        bool ok = query.exec(strSql);

        if (!ok)
        {
            qDebug() << query.lastError();
            return false;
        }
    }
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
//    QSqlQuery query;
//    query.exec("select max(did) from tDairy");
//    while (query.next())
//    {
//        qDebug() << "maxid = " << query.value(0).toInt();
//    }

}
