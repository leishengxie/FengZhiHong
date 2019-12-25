#ifndef __L_SQL_OPERATE_H
#define __L_SQL_OPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Singleton.h"

#include "collection_jokebook/Joke.h"
#include "UserInfo.h"
#include "NetAppointments.h"

///
/// \brief The CSqlOperate class mysql数据库操作
///
class CLSqlOperate : public QObject, public CSingleton<CLSqlOperate>
{
    Q_OBJECT
public:
    explicit CLSqlOperate(QObject *parent = 0);

    // 连接数据库
    static bool connectSqlite(QString strDbName);
    static bool connectMySqDdatabase(QString strHostName, QString strDbName, QString strUserName, QString strPasswd, int port);

    // 创建表
     void createTable();

     //
     void registerAccount(QString strUserName, QString strPasswd, T_HttpStatusMsg &tHttpStatusMsg);
     void login(QString strUserName, QString strPasswd, T_UserInfo &tUserInfo, T_HttpStatusMsg &tHttpStatusMsg);


//     QList<CDairy> getDairyList(int uid);
//     CDairy getDairy(int did, bool & bOk);
//     QList<CDairy> getListDairyByLimit(QString strFormatDate
//                                              , QString strTagName = ""); //strFormatDate  eg:"'2019-09'", 2019-09-01, 2019
//     static bool saveDairy(const CDairy & dairyModify, CDairy & dairySaved);

     void saveUserUploadJoke(const T_Joke & tJoke, T_HttpStatusMsg &tHttpStatusMsg);
     void getJokeList(const T_JokeListRequest & tJokeListRequest
                      , T_JokeListResp & tJokeListResp
                      , T_HttpStatusMsg &tHttpStatusMsg);


public slots:


};

#endif // __L_SQL_OPERATE_H
