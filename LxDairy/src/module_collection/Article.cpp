#include "Article.h"



#ifndef QT_NO_DATASTREAM
QDataStream & operator>>(QDataStream & in, T_Article & data)
{
    in >> data.jId >> data.strTitle >> data.strDate >> data.strContent >> data.bOriginal \
            >> data.upUid >> data.nGenreType >> data.strNickname \
            >> data.llRatingNumOfPeople >> data.dRatingToatalScore >> data.dRatingAverageScore;
    return in;
}

QDataStream & operator<<(QDataStream & out, const T_Article & data)
{
    out << data.jId << data.strTitle << data.strDate << data.strContent << data.bOriginal \
        << data.upUid << data.nGenreType << data.strNickname \
        << data.llRatingNumOfPeople << data.dRatingToatalScore << data.dRatingAverageScore;
    return out;
}
#endif



QDataStream & operator>>(QDataStream &in, T_ArticleListRequest &data)
{
    in >> data.uId >> data.nPageIndex >> data.nPageItems >> data.nSelectType >> data.nSortFiled >> data.nOrderType;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_ArticleListRequest &data)
{
    out << data.uId << data.nPageIndex << data.nPageItems << data.nSelectType << data.nSortFiled << data.nOrderType;
    return out;
}



QDataStream & operator>>(QDataStream &in, T_ArticleListResp &data)
{
    in >> data.nTotalItems >> data.listJoke;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_ArticleListResp &data)
{
    out << data.nTotalItems << data.listJoke;
    return out;
}



QDataStream & operator>>(QDataStream &in, T_ArticleRating &data)
{
    in >> data.jId >> data.uId >> data.dRating;
    return in;
}

QDataStream & operator<<(QDataStream &out, const T_ArticleRating &data)
{
    out << data.jId << data.uId << data.dRating;
    return out;
}
