#include "Dairy.h"
#include <QDateTime>

T_Dairy::T_Dairy()
    : did(INVAILD_DAIRY_ID)
    , strTitle("")
    , strDateTime(QDateTime::currentDateTime().toString(FORMAT_DATETIME))
    , strWeather("晴")
    , strTag("普通日记")
    , strContent("")
{

}

int T_Dairy::year() const
{
    //QMultiMap
    //"2010-07-02 17:35:00";
//    strYear = strDateTime.mid(0, 4);
//    strMonth = strDateTime.mid(5, 2);
//    strDay = strDateTime.mid(8, 2);

    QDateTime dataTime = QDateTime::fromString(strDateTime, FORMAT_DATETIME);
    return dataTime.date().year();
}

int T_Dairy::month() const
{
    QDateTime dataTime = QDateTime::fromString(strDateTime, FORMAT_DATETIME);
    return dataTime.date().month();
}

int T_Dairy::day() const
{
    QDateTime dataTime = QDateTime::fromString(strDateTime, FORMAT_DATETIME);
    return dataTime.date().day();
}

bool T_Dairy::operator ==(const T_Dairy &right) const
{
    return did == right.did;
}



QDataStream &operator>>(QDataStream &in, T_Dairy &data)
{
    in >> data.did >> data.uid >> data.strTitle >> data.strDateTime >> data.strWeather >> data.strTag >> data.strContent;
    return in;
}

QDataStream &operator<<(QDataStream &out, const T_Dairy &data)
{
    out << data.did << data.uid << data.strTitle << data.strDateTime << data.strWeather << data.strTag \
        << data.strContent;
    return out;
}


QDataStream &operator>>(QDataStream &in, T_DairyListRequest &data)
{
    in >> data.uid >> data.nPageIndex >> data.nPageItems;
    return in;
}

QDataStream &operator<<(QDataStream &out, const T_DairyListRequest &data)
{
    out << data.uid << data.nPageIndex << data.nPageItems;
    return out;
}



QDataStream &operator>>(QDataStream &in, T_DairyListResp &data)
{
    in >> data.nTotalItems >> data.dairyList;
    return in;
}

QDataStream &operator<<(QDataStream &out, const T_DairyListResp &data)
{
    out << data.nTotalItems << data.dairyList;
    return out;
}


QDataStream &operator>>(QDataStream &in, T_DairyDeleteReq &data)
{
    in >> data.dairyList;
    return in;
}

QDataStream &operator<<(QDataStream &out, const T_DairyDeleteReq &data)
{
    out << data.dairyList;
    return out;
}
