#ifndef CDAIRY_H
#define CDAIRY_H

#include <QString>
#include "def/func.h"

#define FORMAT_DATETIME    "yyyy-MM-dd hh:mm:ss"
// Q_DISABLE_COPY(QObject) 不继承QObject
class CDairy
{

public:

    CDairy();
    SETGET(int, did, Did)
    SETGET(QString, strTitle, Title)
    SETGET(QString, strDateTime, DateTime)
    SETGET(QString, strWeather, Weather)
    SETGET(QString, strTag, Tag)
    SETGET(QString, strContent, Content)


private:

};

#endif // CDAIRY_H
