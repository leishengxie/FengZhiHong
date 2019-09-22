#ifndef CDAIRY_H
#define CDAIRY_H

#include <QString>
#include "def/func.h"

#define FORMAT_DATETIME                 "yyyy-MM-dd hh:mm:ss"
#define FORMAT_DATETIME_DISPLAYER       "yyyy年MM月dd日 hh:mm"
#define INVAILD_DAIRY_ID                -1
// Q_DISABLE_COPY(QObject) 不继承QObject
class CDairy
{

public:

    CDairy();
    SETGETCONST(int, did, Did)
    SETGETCONST(QString, strTitle, Title)
    SETGETCONST(QString, strDateTime, DateTime)
    SETGETCONST(QString, strWeather, Weather)
    SETGETCONST(QString, strTag, Tag)
    SETGETCONST(QString, strContent, Content)

    bool isEmptyContent()
    {
        return strTitle.isEmpty() && strContent.isEmpty();
    }

    bool isNewDairy()
    {
        return did == INVAILD_DAIRY_ID;
    }

private:

};

#endif // CDAIRY_H
