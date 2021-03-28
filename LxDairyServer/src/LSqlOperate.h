#ifndef __L_SQL_OPERATE_H
#define __L_SQL_OPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "patterns/Singleton.h"

#include "Article.h"
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
     // 创建存储过程
     void createProc();
     // 创建函数
     void createFunc();

     // 登录注册服务
     void registerAccount(QString strUserName, QString strPasswd, T_HttpStatusMsg &tHttpStatusMsg);
     void login(QString strUserName, QString strPasswd, T_UserInfo &tUserInfo, T_HttpStatusMsg &tHttpStatusMsg);



     // 日记服务
//     CDairy getDairy(int did, bool & bOk);
//     QList<CDairy> getListDairyByLimit(QString strFormatDate
//                                              , QString strTagName = ""); //strFormatDate  eg:"'2019-09'", 2019-09-01, 2019
//     static QList<T_Dairy> getDairyList(int uid);
     void saveDairy(const T_Dairy & dairyModify, T_Dairy & dairySaved, T_HttpStatusMsg &tHttpStatusMsg);
     void getDairyList(const T_DairyListRequest & tDairyListRequest
                      , T_DairyListResp & tDairyListResp
                      , T_HttpStatusMsg &tHttpStatusMsg);
     void deleteDairy(const T_DairyDeleteReq & tDairyDeleteReq, T_HttpStatusMsg &tHttpStatusMsg);

     // 集服务
     void saveUserUploadArticle(const T_Article & tArticle, T_HttpStatusMsg &tHttpStatusMsg);
     void getArticleList(const T_ArticleListRequest & tArticleListRequest
                      , T_ArticleListResp & tArticleListResp
                      , T_HttpStatusMsg &tHttpStatusMsg);
     void articleRating(const T_ArticleRating & tArticleRating, T_HttpStatusMsg &tHttpStatusMsg);


public slots:


};

#endif // __L_SQL_OPERATE_H
