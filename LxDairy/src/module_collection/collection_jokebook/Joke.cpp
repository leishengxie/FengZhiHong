#include "Joke.h"

#ifndef QT_NO_DATASTREAM
QDataStream & operator>>(QDataStream & in, T_Joke & data)
{
//    in >> data.jId >> data.strTitle >> data.strDate >> data.strContent >> data.bOriginal >> data.upUid \
//       >> data.strNickname >> data.llRatingNumOfPeople >> data.dRatingToatalScore >> data.dRatingAverageScore;
    in >> data.strTitle;
    return in;
}

QDataStream & operator<<(QDataStream & out, const T_Joke & data)
{
//    out << data.jId << data.strTitle << data.strDate << data.strContent << data.bOriginal << data.upUid \
//        << data.strNickname << data.llRatingNumOfPeople << data.dRatingToatalScore << data.dRatingAverageScore;
    out << (quint32)data.jId;
    out << data.strTitle;
    return out;
}
#endif
