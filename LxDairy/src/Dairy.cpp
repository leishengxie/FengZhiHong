#include "Dairy.h"
#include <QDateTime>

CDairy::CDairy()
    : strTitle("")
    , strDateTime(QDateTime::currentDateTime().toString(FORMAT_DATETIME))
    , strWeather("晴")
    , strTag("普通日记")
    , strContent("")
{

}
