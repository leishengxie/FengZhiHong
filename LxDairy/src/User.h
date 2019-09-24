#ifndef CUSER_H
#define CUSER_H

#include <QString>
#include <QList>
#include "patterns/Singleton.h"
#include "def/func.h"
#include "Dairy.h"

///
/// \brief The CUser class 用户数据
///
class CUser : public CSingleton<CUser>
{
public:
    SETGET(int, nUid, Uid)
    SETGET(QString, strUserName, UserName)
    SETGET(QList<CDairy>, m_lstDairy, LstDairy)
    // 当前活动的日记
    SETGET(CDairy, ActiveDairy, ActiveDairy)
    SETGET(QStringList, m_lstDairyTag, LstDairyTag)

    void appendDairy(CDairy dairy);

    CUser();

private:

};

#endif // CUSER_H
