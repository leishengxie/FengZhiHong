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
