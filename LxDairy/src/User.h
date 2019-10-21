#ifndef CUSER_H
#define CUSER_H

#include <QObject>
#include <QString>
#include <QList>
#include "patterns/Singleton.h"
#include "def/func.h"
#include "Dairy.h"

///
/// \brief The CUser class 用户数据,用于把数据库的数据加载到内存，方便管理
///
class CUser : public QObject, public CSingleton<CUser>
{
    Q_OBJECT
public:
    CUser();

    SETGET(int, nUid, Uid)
    SETGET(QString, strUserName, UserName)
    SETGET(QList<CDairy>, m_lstDairy, LstDairy)
    // 当前活动的日记
    SETGET(CDairy, ActiveDairy, ActiveDairy)
    SETGET(QStringList, m_lstDairyTag, LstDairyTag)

    void appendDairy(CDairy dairy);


    void loadDairyList(const QList<CDairy> & lstDairy);

signals:
    void dairyListChanged(const QList<CDairy> & lstDairy);

private:

};

#endif // CUSER_H
