#ifndef CDAIRY_H
#define CDAIRY_H

#include <QString>
#include "func.h"

#define FORMAT_DATETIME                 "yyyy-MM-dd hh:mm:ss"
#define FORMAT_DATETIME_DISPLAYER       "yyyy年MM月dd日 hh:mm"
#define INVAILD_DAIRY_ID                -1
// Q_DISABLE_COPY(QObject) 不继承QObject
//QObject 中没有提供一个拷贝构造函数和赋值操作符给外界使用，其实拷贝构造和赋值的操作都是已经声明了的，但是它们被使用了Q_DISABLE_COPY() 宏放在了private区域。
//因此所有继承自QObject的类都使用这个宏声明了他们的拷贝构造函数和赋值操作符为私有。
class CDairy
{

public:

    CDairy();
    SETGETCONST(int, did, Did)
    SETGETCONST(int, uid, Uid)
    SETGETCONST(QString, strTitle, Title)
    SETGETCONST(QString, strDateTime, DateTime)
    SETGETCONST(QString, strWeather, Weather)
    SETGETCONST(QString, strTag, Tag)
    SETGETCONST(QString, strContent, Content)

    bool isEmptyContent()
    {
        return strTitle.isEmpty() && strContent.isEmpty();
    }

    bool isNewDairy() const
    {
        return did == INVAILD_DAIRY_ID;
    }

private:

};

#endif // CDAIRY_H
