#ifndef CUSER_H
#define CUSER_H

#include <QString>
#include <QList>
#include "patterns/Singleton.h"
#include "def/func.h"
#include "Dairy.h"

class CUser : public CSingleton<CUser>
{
public:
    SETGET(int, nUid, Uid)
    SETGET(QString, strUserName, UserName)
    SETGET(QList<CDairy>, m_lstDairy, LstDairy)

    void appendDairy(CDairy dairy);
private:

};

#endif // CUSER_H
