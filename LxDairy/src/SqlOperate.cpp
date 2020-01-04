#include "SqlOperate.h"
#include<QVariant>
#include<QCoreApplication>
#include<QDir>
#include<QPixmap>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <time.h>


CSqlOperate::CSqlOperate(QObject* parent) : QObject(parent)
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
    QString strSql;
    /**
    strSql = " CREATE TABLE IF NOT EXISTS tUser( " \
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
    */

    strSql = "CREATE TABLE IF NOT EXISTS tDairy(" \
             "did INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
             "uid INTEGER NOT NULL," \
             "title TEXT," \
             "datetime  TEXT," \
             "weather TEXT," \
             "tag TEXT," \
             "content TEXT)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }
}






// 读取日记
QList<T_Dairy> CSqlOperate::getDairyList(int uid)
{
    QSqlQuery query;
    QList<T_Dairy> lstDairy;
    query.exec("select * from tDairy where uid = '" + QString::number(uid) + "'");
    while (query.next())
    {
        //为避免内存占用只需要did和datetime
        T_Dairy dairy;
        dairy.did = query.value("did").toInt();
        dairy.strTitle = query.value("title").toString();
        dairy.strDateTime = query.value("datetime").toString();
        dairy.strTag = query.value("tag").toString();
        dairy.strWeather = query.value("weather").toString();
        dairy.strContent = query.value("content").toString();
        lstDairy.append(dairy);
    }
    return lstDairy;
}





bool CSqlOperate::saveDairy(const T_Dairy & dairyModify, T_Dairy & dairySaved, QString & strError)
{
    QSqlQuery query;
    dairySaved = dairyModify;
    if (dairyModify.isNewDairy())
    {
        bool ok = query.prepare("INSERT INTO tDairy(uid, title,datetime,tag,weather,content) "
                                "VALUES (?, ?, ?, ?, ?, ?)");
        query.bindValue(0, dairyModify.uid);
        query.bindValue(1, dairyModify.strTitle);
        query.bindValue(2, dairyModify.strDateTime);
        query.bindValue(3, dairyModify.strTag);
        query.bindValue(4, dairyModify.strWeather);
        query.bindValue(5, dairyModify.strWeather);
        ok = query.exec();
        if (!ok)
        {
            strError = query.lastError().text();
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
            strError = query.lastError().text();
            return false;
        }
        if (query.next())
        {
            dairySaved.did = query.value(0).toInt();
        }
    }
    else
    {
        QString strSql = QString("update tDairy set title='%1', tag='%2', weather='%3', content='%4' where did='%5'")
                         .arg(dairyModify.strTitle)
                         .arg(dairyModify.strTag)
                         .arg(dairyModify.strWeather)
                         .arg(dairyModify.strContent)
                         .arg(dairyModify.did);
        bool ok = query.exec(strSql);

        if (!ok)
        {
            strError = query.lastError().text();
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
    QString path = QCoreApplication::applicationDirPath() + "/file";
    isDirExist(path);
    QString tupian = path + QString("/%1.png").arg(zhanghao);
    QPixmap(touxiang).save(tupian, "png");
    QSqlQuery query;
    query.exec("select * from zhanghao");
    while (query.next())
    {
        if(query.value(0).toInt() == zhanghao.toInt())
        {
            //zhanghao,mima,wangming,qianming,beizhu,touxiang,ziti，beijing
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
