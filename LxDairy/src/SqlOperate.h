#ifndef CSQLOPERATE_H
#define CSQLOPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include "Dairy.h"
#include "UserInfo.h"

///
/// \brief The CSqlOperate class 本地sqlite数据库操作
///
class CSqlOperate : public QObject
{
    Q_OBJECT
public:
    explicit CSqlOperate(QObject *parent = 0);

    static bool connect(QString strDbName);

    static void createTable();

    static bool registerAccount(QString strUserName, QString strPasswd, QString & strErr);

    static bool login(QString strUserName, QString strPasswd, T_UserInfo & tUserInfo, QString & strErr);

    static QList<CDairy> getDairyList(int uid);
    static CDairy getDairy(int did, int uid, bool & bOk);
    static QList<CDairy> getListDairyByLimit(QString strFormatDate
                                             , QString strTagName = ""); //strFormatDate  eg:"'2019-09'", 2019-09-01, 2019
    static bool saveDairy(const CDairy & dairyModify, CDairy & dairySaved);


    static void SetXinXi(QString registerAccount, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian);
    static void test();
signals:

public slots:
};

#endif // CSQLOPERATE_H
