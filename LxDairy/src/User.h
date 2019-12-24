#ifndef CUSER_H
#define CUSER_H

#include <QObject>
#include <QString>
#include <QList>
#include "Singleton.h"
#include "func.h"
#include "Dairy.h"
#include "UserInfo.h"

///
/// \brief The CUser class 用户数据,用于把数据库的数据加载到内存，方便管理
///
class CUser : public QObject, public CSingleton<CUser>
{
    Q_OBJECT
public:
    CUser();

    //////////////////////// 用户数据////////////////////

    // 用户id
    SETGET(int, nUid, Uid)
    // 用户昵称
    SETGET(QString, strUserName, UserName)
    // 用户日记数据
    SETGET(QList<CDairy>, m_lstDairy, LstDairy)
    // 当前活动的日记
    SETGET(CDairy, ActiveDairy, ActiveDairy)
    // 用户标签数据
    SETGET(QStringList, m_lstDairyTag, LstDairyTag)


    // 用户登录返回的用户信息
    SETGET(T_UserInfo, m_tUserInfo, UserInfo)

    void appendDairy(CDairy dairy);


    void loadDairyList(const QList<CDairy> & lstDairy);

signals:
    void dairyListChanged(const QList<CDairy> & lstDairy);


private:

};

#endif // CUSER_H
