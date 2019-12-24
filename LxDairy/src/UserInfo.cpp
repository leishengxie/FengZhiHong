#include "UserInfo.h"



QDataStream & operator>>(QDataStream &in, T_UserInfo &data)
{
    in >> data.uid >> data.strNickName;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_UserInfo &data)
{
    out << data.uid << data.strNickName;
    return out;
}
