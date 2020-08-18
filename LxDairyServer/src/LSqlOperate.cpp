#include "LSqlOperate.h"
#include<QVariant>
#include<QCoreApplication>
#include<QDir>
#include<QPixmap>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <time.h>
#include "LSqlConnectionPool.h"



CLSqlOperate::CLSqlOperate(QObject* parent) : QObject(parent)
{
    createTable();

}

bool CLSqlOperate::connectSqlite(QString strDbName)
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

bool CLSqlOperate::connectMySqDdatabase(QString strHostName, QString strDbName, QString strUserName, QString strPasswd, int port)
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

void CLSqlOperate::createTable()
{

    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);

    /// tUser 主要mysql的主键没有默认值
    QString strSql = "create table if not exists tUser(" \
                     "uid int not null primary key auto_increment, " \
                     "user_name varchar(32) not null, " \
                     "passwd varchar(16) not null, " \
                     "nick_name varchar(32), " \
                     "phone_no varchar(16))";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    // 用户授权信息表 - 暂时不使用第三方登录
    //    QString strSql = "create table if not exists tUserAuths(" \
    //                     "id int not null primary key auto_increment, " \
    //                     "uid int not null, " \
    //                     "identity_type varchar(32) not null, " \
    //                     "identifier varchar(32) not null, " \
    //                     "credential varchar(128) not null)";
    //    if (!query.exec(strSql))
    //    {
    //        qDebug() << query.lastError();
    //    }

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
             "rating double NOT NULL, " \
             "PRIMARY KEY (jid, uid), " \
             "CONSTRAINT fk_tJokeRating_jid FOREIGN KEY (jid) REFERENCES tJoke(jid) ON DELETE CASCADE ON UPDATE CASCADE," \
             "CONSTRAINT fk_tJokeRating_uid FOREIGN KEY (uid) REFERENCES tUser(uid) ON DELETE CASCADE ON UPDATE CASCADE" \
             ")";
    if (!query.exec(strSql))
    {
        qDebug() << query.lastError();
    }

    CSqlConnectionPool::getInstance()->closeConnection(db);

}

void CLSqlOperate::createProc()
{
//    DROP PROCEDURE IF EXISTS `proc_joke_rating`;
//    delimiter ;;
//    CREATE PROCEDURE `proc_joke_rating`(IN `i_jid` int,IN `i_uid` int,IN `i_rating` double)
//    BEGIN
//        #Routine body goes here...
//    DECLARE bExist TINYINT default 0;
//    DECLARE var_total_rating_people int default 0;
//    DECLARE var_total_rating_score double default 0;
//    DECLARE var_average_rating_score double default 0;

//    DECLARE t_error int DEFAULT 0;
//    DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET t_error=1;

//        select count(1) into bExist from tjokerating where jid=i_jid and uid=i_uid;
//    # 开始事务
//    START TRANSACTION;
//        if bExist
//        then
//        update tJokeRating set rating=i_rating where jid=i_jid and uid=i_uid;
//    else
//    INSERT INTO tJokeRating(jid, uid, rating) VALUES(i_jid, i_uid, i_rating);

//    end if;

//    # select COUNT(1) into var_total_rating_people from tjokerating where jid=i_jid;
//    #	set @var_total_rating_score = (select SUM(rating) from tjokerating where jid=i_jid);
//    #	set @var_average_rating_score = var_total_rating_people / var_total_rating_score;
//    update tJoke, (select COUNT(1) as r_count from tjokerating where jid=i_jid) as t1, (select SUM(rating) as r_rating from tjokerating where jid=i_jid) as t2 set total_rating_people=t1.r_count, total_rating_score=t2.r_rating, average_rating_score = r_rating / r_count WHERE jid=i_jid;

//    IF t_error = 1 THEN
//                ROLLBACK;
//            ELSE
//                COMMIT;
//            END IF;

//    END
//    ;;
//    delimiter ;
}

void CLSqlOperate::createFunc()
{

}


void CLSqlOperate::registerAccount(QString strUserName, QString strPasswd, T_HttpStatusMsg & tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);

    // 检查账号是否已经存在
    query.exec("select * from tUser where user_name = '" + strUserName + "'");
    if (query.next())
    {
        tHttpStatusMsg.nStatusCode = EH_Ex_AccountAlreadyExists;  // user name already existes
        tHttpStatusMsg.strMsg = "账号已经存在";
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }

    // test2
    query.prepare("INSERT INTO tUser(user_name, passwd, nick_name) VALUES(?, ?, ?)");
    query.bindValue(0, strUserName);
    query.bindValue(1, strPasswd);
    query.bindValue(2, strUserName);

    if (!query.exec())
    {
        qDebug() << query.lastError();
        tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
        tHttpStatusMsg.strMsg = query.lastError().text();
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }

    CSqlConnectionPool::getInstance()->closeConnection(db);

}

void CLSqlOperate::login(QString strUserName, QString strPasswd, T_UserInfo & tUserInfo, T_HttpStatusMsg & tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);
    query.exec("select * from tUser where user_name = '" + strUserName + "'");
    if (!query.next())
    {
        tHttpStatusMsg.nStatusCode = EH_Ex_AccountNotExists;
        tHttpStatusMsg.strMsg = "账号不存在，请注册账号";
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;

    }

    query.exec("select * from tUser where user_name = '" + strUserName + "' and passwd = '" + strPasswd + "'");
    if (query.next())
    {
        //QSqlRecord rec = q.record();
        tUserInfo.uid = query.value("uid").toInt();
        tUserInfo.strNickName = query.value("nick_name").toString();
    }
    else
    {
        tHttpStatusMsg.nStatusCode = EH_Ex_PasswdError;
        tHttpStatusMsg.strMsg = "密码错误";
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }

    CSqlConnectionPool::getInstance()->closeConnection(db);
}

void CLSqlOperate::saveDairy(const T_Dairy &dairyModify, T_Dairy &dairySaved, T_HttpStatusMsg &tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);
    dairySaved = dairyModify;
    if (dairyModify.isNewDairy())
    {
        bool ok = query.prepare("INSERT INTO tDairy(uid, title,wirte_datetime,tag,weather,content) "
                                "VALUES (?, ?, ?, ?, ?, ?)");
        query.bindValue(0, dairyModify.uid);
        query.bindValue(1, dairyModify.strTitle);
        query.bindValue(2, dairyModify.strDateTime);
        query.bindValue(3, dairyModify.strTag);
        query.bindValue(4, dairyModify.strWeather);
        query.bindValue(5, dairyModify.strContent);
        ok = query.exec();
        if (!ok)
        {
            qDebug() << query.lastError();
            tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
            tHttpStatusMsg.strMsg = query.lastError().text();
            CSqlConnectionPool::getInstance()->closeConnection(db);
            return;
        }

        // 重新获取今天的日记did
        //select max(did) from tDairy
        //select * from tDairy WHERE did = (select max(did) from tDairy)
        //select top 1 * From tDairy Order by did Desc #sqlite没有top函数
        //getDairyList(CUser::getInstance()->getUid());
        query.exec("select max(did) from tDairy");
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
            qDebug() << query.lastError();
            tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
            tHttpStatusMsg.strMsg = query.lastError().text();
            CSqlConnectionPool::getInstance()->closeConnection(db);
            return;
        }
    }
    CSqlConnectionPool::getInstance()->closeConnection(db);
}


void CLSqlOperate::getDairyList(const T_DairyListRequest &tDairyListRequest
                                , T_DairyListResp &tDairyListResp
                                , T_HttpStatusMsg &tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);

    QList<T_Dairy> lstDairy;
    query.exec("select * from tDairy where uid = '" + QString::number(tDairyListRequest.uid) + "'");
    while (query.next())
    {
        //为避免内存占用只需要did和datetime
        T_Dairy dairy;
        dairy.did = query.value("did").toInt();
        dairy.strTitle = query.value("title").toString();
        dairy.strDateTime = query.value("wirte_datetime").toString();
        dairy.strTag = query.value("tag").toString();
        dairy.strWeather = query.value("weather").toString();
        dairy.strContent = query.value("content").toString();
        lstDairy.append(dairy);
    }
    tDairyListResp.nTotalItems = lstDairy.size();
    tDairyListResp.dairyList = lstDairy;
    CSqlConnectionPool::getInstance()->closeConnection(db);

}


///
/// \brief CLSqlOperate::deleteDairy 根据需求，用户的日记数据不是特别重要，直接使用物理删除，不必用逻辑删除
/// \param tDairyDeleteReq 批量删除
/// \param tHttpStatusMsg
///
void CLSqlOperate::deleteDairy(const T_DairyDeleteReq &tDairyDeleteReq, T_HttpStatusMsg &tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);

    db.transaction();
    QVariantList varlist_id;
    foreach (int id, tDairyDeleteReq.dairyList)
    {
        varlist_id << id;
    }

    query.prepare("delete from tDairy where did=?");
    query.addBindValue(varlist_id);	//绑定数据
    bool ok = query.execBatch();		//进行批处理操作
    if (!ok)
    {
        tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
        tHttpStatusMsg.strMsg = query.lastError().text();
        db.rollback();
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }
    db.commit();		//提交事务，此时打开数据库文件执行SQL语句

    CSqlConnectionPool::getInstance()->closeConnection(db);
}



void CLSqlOperate::saveUserUploadJoke(const T_Joke & tJoke, T_HttpStatusMsg & tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);
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
        tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
        tHttpStatusMsg.strMsg = query.lastError().text();
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }

    CSqlConnectionPool::getInstance()->closeConnection(db);
}


//QList<T_Dairy> CSqlOperate::getListDairyByLimit(QString strFormatDate, QString strTagName)
//{
//    // eg: select * from tDairy where substr(date(datetime),1,7) = '2019-09';
//    //
//    QList<T_Dairy> lstDairy;
//    QSqlQuery query;
//    QString strSql;
//    if (!strFormatDate.isEmpty() && strTagName.isEmpty())
//    {
//        strSql = QString("select * from tDairy where substr(date(datetime),1,%1) = '%2'")
//                 .arg(strFormatDate.length())
//                 .arg(strFormatDate);
//    }
//    else if (strFormatDate.isEmpty() && !strTagName.isEmpty())
//    {
//        strSql = QString("select * from tDairy where tag = '%1'").arg(strTagName);
//    }
//    else if (!strFormatDate.isEmpty() && !strTagName.isEmpty())
//    {
//        strSql = QString("select * from tDairy where substr(date(datetime),1,%1) = '%2' and tag = '%3'")
//                 .arg(strFormatDate.length())
//                 .arg(strFormatDate)
//                 .arg(strTagName);
//    }
//    else
//    {
//        strSql = QString("select * from tDairy");
//    }
//    bool ok = query.exec(strSql);

//    if (!ok)
//    {
//        qDebug() << query.lastError();
//        return lstDairy;
//    }
//    while (query.next())
//    {
//        T_Dairy dairy;
//        dairy.setDid(query.value("did").toInt());
//        dairy.setTitle(query.value("title").toString());
//        dairy.setDateTime(query.value("datetime").toString());
//        dairy.setTag(query.value("tag").toString());
//        dairy.setWeather(query.value("weather").toString());
//        dairy.setContent(query.value("content").toString());
//        lstDairy.append(dairy);
//    }
//    return lstDairy;
//}

//T_Dairy CSqlOperate::getDairy(int did, int uid, bool & bOk)
//{
//    T_Dairy dairy;
//    QSqlQuery query;
//    query.exec("select * from tDairy where uid = '"
//               + QString::number(uid)
//               + "' and did = '" + QString::number(did) + "'");
//    if (query.next())
//    {
//        bOk = true;
//        dairy.setDid(query.value("did").toInt());
//        dairy.setTitle(query.value("title").toString());
//        dairy.setDateTime(query.value("datetime").toString());
//        dairy.setTag(query.value("tag").toString());
//        dairy.setWeather(query.value("weather").toString());
//        dairy.setContent(query.value("content").toString());
//    }
//    else
//    {
//        bOk = false;
//    }
//    return dairy;
//}


void CLSqlOperate::getJokeList(const T_JokeListRequest & tJokeListRequest
                               , T_JokeListResp & tJokeListResp
                               , T_HttpStatusMsg & tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);
    //    int nPageIndex; // 页码
    //    int nPageItems; // 当前页最大条目数
    //    int nSelectType;
    //    int nSortFiled;
    //    int nOrderType;


    QString strUserLimit = "";
    if (tJokeListRequest.nSelectType == ES_SelectByMyUpload)
    {
        strUserLimit = QString(" where up_uid = %1").arg(tJokeListRequest.uId);
    }
    QString strQuery = "select count(1) from tJoke" + strUserLimit;
    qDebug() << strQuery;
    query.exec(strQuery);
    if(query.next())
    {
        tJokeListResp.nTotalItems = query.value(0).toInt();
    }

    //select * from table_name limit 0,10
    int nPos = (tJokeListRequest.nPageIndex - 1) * tJokeListRequest.nPageItems;
    strQuery = QString("select * from tJoke" + strUserLimit + " limit %1, %2").arg(nPos).arg(tJokeListRequest.nPageItems);
    qDebug() << strQuery;
    if (!query.exec(strQuery))
    {
        qDebug() << query.lastError();
        tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
        tHttpStatusMsg.strMsg = query.lastError().text();
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }
    while (query.next())
    {
        T_Joke tJoke;
        tJoke.jId = query.value("jid").toInt();
        tJoke.strTitle = query.value("title").toString();
        tJoke.strDate = query.value("create_datetime").toString();
        tJoke.strContent = query.value("content").toString();
        tJoke.bOriginal = query.value("original").toBool();
        tJoke.upUid = query.value("up_uid").toInt();
        tJoke.strNickname = query.value("nickname").toString();
        tJoke.llRatingNumOfPeople = query.value("total_rating_people").toInt();
        tJoke.dRatingToatalScore = query.value("total_rating_score").toDouble();
        tJoke.dRatingAverageScore = query.value("average_rating_score").toDouble();
        tJokeListResp.listJoke.append(tJoke);
    }
    CSqlConnectionPool::getInstance()->closeConnection(db);
}

void CLSqlOperate::jokeRating(const T_JokeRating & tJokeRating, T_HttpStatusMsg & tHttpStatusMsg)
{
    QSqlDatabase db = CSqlConnectionPool::getInstance()->getOpenConnection();
    QSqlQuery query(db);
    /**
        // 查询是否已经有评价

        QString strQuery = QString("select count(1) from tJoke where jid=%1 and uid=%2").arg(tJokeRating.jId).arg(tJokeRating.uId);
        query.exec(strQuery);
        if(query.next())
        {
            strQuery = QString("update tJokeRating set rating=%1 where jid=%2 and uid=%3")
                    .arg(tJokeRating.dRating)
                    .arg(tJokeRating.jId)
                    .arg(tJokeRating.uId);
        }
        else
        {
            strQuery = QString("INSERT INTO tJokeRating(jid, uid, rating) VALUES(%1, %2, %3)")
                    .arg(tJokeRating.jId)
                    .arg(tJokeRating.uId)
                    .arg(tJokeRating.dRating);
        }
        query.exec(strQuery);
        //strQuery = "update tJoke set total_rating_people= total_rating_score= average_rating_score=";
        */

    //    以下是访问oracle存储过程的示例，多个输入、输出都可以。
    //    QSqlQuery query(db);
    //    if (!query.prepare("call test_out2(:p1,:p2,:out1,:out2)"))
    //    {
    //    return false;
    //    }
    //    query.bindValue(":p1", "abcd", QSql::In);
    //    query.bindValue(":p2", "edfg", QSql::In);
    //    QString t1(128,'\0'),t2(128,'\0');
    //    query.bindValue(":out1", t1, QSql::Out);
    //    query.bindValue(":out2", t2, QSql::Out);
    //    if (!query.exec())
    //    {
    //    return false;
    //    }
    //    QString str1 = query.boundValue(":out1").toInt();
    //    QString str2 = query.boundValue(":out2").toInt();

    // 使用存储过程
    qDebug() << "使用存储过程" << tJokeRating.jId << tJokeRating.uId << tJokeRating.dRating;
    if (!query.prepare("call proc_joke_rating(:p1,:p2,:p3)"))
    {
        qDebug() << query.lastError();
        tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
        tHttpStatusMsg.strMsg = query.lastError().text();
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }
    query.bindValue(":p1", tJokeRating.jId, QSql::In);
    query.bindValue(":p2", tJokeRating.uId, QSql::In);
    query.bindValue(":p3", tJokeRating.dRating, QSql::In);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        tHttpStatusMsg.nStatusCode = EH_Ex_SqlError;
        tHttpStatusMsg.strMsg = query.lastError().text();
        CSqlConnectionPool::getInstance()->closeConnection(db);
        return;
    }
    CSqlConnectionPool::getInstance()->closeConnection(db);
}


