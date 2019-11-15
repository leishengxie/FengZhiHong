#include "Dairy.h"
#include <QDateTime>

CDairy::CDairy()
    : did(INVAILD_DAIRY_ID)
    , strTitle("")
    , strDateTime(QDateTime::currentDateTime().toString(FORMAT_DATETIME))
    , strWeather("晴")
    , strTag("普通日记")
    , strContent("")
{

}
