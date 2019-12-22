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
    createTable();

}

bool CSqlOperate::connectSqlite(QString strDbName)
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

bool CSqlOperate::connectMySqDdatabase(QString strHostName, QString strDbName, QString strUserName, QString strPasswd, int port)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //mysql -u root -p0406 -h 39.106.17.62
    //db.setHostName("localhost");
    //db.setHostName("192.168.0.143");
    db.setHostName(strHostName);
    //db.setHostName("39.106.17.62");
    db.setDatabaseName(strDbName);
    db.setUserName(strUserName);
    db.setPassword(strPasswd);

    if(db.open())
    {
        //qDebug()<<"database is established!";
    }
    else
    {
        qDebug() << "db open error!";
        return false;
    }
}

void CSqlOperate::createTable()
{

/// tUser 主要mysql的主键没有默认值
    QString strSql = "create table if not exists tUser(" \
                     "uid int not null primary key auto_increment, " \
                     "user_name varchar(32) not null, " \
                     "passwd varchar(16) not null)";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    /// tDairy
    strSql = "create table if not exists tDairy(" \
             "did int not null primary key auto_increment, " \
             "uid int NOT NULL, " \
             "title varchar(32), " \
             "wirte_datetime datetime null, " \
             "weather varchar(32), " \
             "tag varchar(32), " \
             "content TEXT, " \
             "CONSTRAINT `fk_tDairy_uid` FOREIGN KEY (`uid`) REFERENCES `lxdairy`.`tUser` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE" \
             ")";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    /// tAPasswd
    strSql = "create table if not exists tAPasswd(" \
             "aid int not null primary key auto_increment, " \
             "uid int NOT NULL, " \
             "item varchar(32), " \
             "account varchar(32), " \
             "passwd varchar(16), " \
             "CONSTRAINT fk_tAPasswd_uid FOREIGN KEY (uid) REFERENCES tUser(uid) ON DELETE CASCADE ON UPDATE CASCADE )";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    /// tJoke 此表服务端即使上传者账号注销，其上传的作品不删除， 所以其外键删除时NO ACTION
    strSql = "create table if not exists tJoke(" \
             "jid int not null primary key auto_increment," \
             "title varchar(32) NOT NULL," \
             "create_datetime datetime," \
             "content TEXT," \
             "original tinyint NOT NULL," \
             "up_uid int NOT NULL," \
             "nickname varchar(32), " \
             "total_rating_people int DEFAULT 0, " \
             "total_rating_score double DEFAULT 0, " \
             "average_rating_score double DEFAULT 0, " \
             "CONSTRAINT fk_tJoke_up_uid FOREIGN KEY (up_uid) REFERENCES tUser(uid) ON DELETE NO ACTION ON UPDATE CASCADE" \
             ")";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    /// tJoke 外键不能重名 统一用fk_表名_字段名
    strSql = "create table if not exists tJokeRating(" \
             "jid int not null, " \
             "uid int not null, " \
             "rating int NOT NULL, " \
             "PRIMARY KEY (jid, uid), " \
             "CONSTRAINT fk_tJokeRating_jid FOREIGN KEY (jid) REFERENCES tJoke(jid) ON DELETE CASCADE ON UPDATE CASCADE," \
             "CONSTRAINT fk_tJokeRating_uid FOREIGN KEY (uid) REFERENCES tUser(uid) ON DELETE CASCADE ON UPDATE CASCADE" \
             ")";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

}

bool CSqlOperate::saveUserUploadJoke(const T_Joke &tJoke)
{
    // 有外键约束会检测uid在tuser的存在
    query.prepare("INSERT INTO tJoke(title, create_datetime, content, original, up_uid, nickname) VALUES(?, ?, ?, ?, ?, ?)");
    query.bindValue(0, tJoke.strTitle);
    query.bindValue(1, tJoke.strDate);
    query.bindValue(2, tJoke.strContent);
    query.bindValue(3, tJoke.bOriginal);
    query.bindValue(4, tJoke.upUid);
    query.bindValue(5, tJoke.strNickname);

    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}


