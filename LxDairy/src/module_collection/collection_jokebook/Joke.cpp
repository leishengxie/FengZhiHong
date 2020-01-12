#include "Joke.h"

#ifndef QT_NO_DATASTREAM
QDataStream & operator>>(QDataStream & in, T_Joke & data)
{
    in >> data.jId >> data.strTitle >> data.strDate >> data.strContent >> data.bOriginal >> data.upUid \
       >> data.strNickname >> data.llRatingNumOfPeople >> data.dRatingToatalScore >> data.dRatingAverageScore;
    return in;
}

QDataStream & operator<<(QDataStream & out, const T_Joke & data)
{
    out << data.jId << data.strTitle << data.strDate << data.strContent << data.bOriginal << data.upUid \
        << data.strNickname << data.llRatingNumOfPeople << data.dRatingToatalScore << data.dRatingAverageScore;
    return out;
}
#endif



QDataStream & operator>>(QDataStream &in, T_JokeListRequest &data)
{
    in >> data.uId >> data.nPageIndex >> data.nPageItems >> data.nSelectType >> data.nSortFiled >> data.nOrderType;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_JokeListRequest &data)
{
    out << data.uId << data.nPageIndex << data.nPageItems << data.nSelectType << data.nSortFiled << data.nOrderType;
    return out;
}



QDataStream & operator>>(QDataStream &in, T_JokeListResp &data)
{
    in >> data.nTotalItems >> data.listJoke;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_JokeListResp &data)
{
    out << data.nTotalItems << data.listJoke;
    return out;
}



QDataStream & operator>>(QDataStream &in, T_JokeRating &data)
{
    in >> data.jId >> data.uId >> data.dRating;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_JokeRating &data)
{
    out << data.jId << data.uId << data.dRating;
    return out;
}
