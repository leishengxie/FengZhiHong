#ifndef __JOKE_H
#define __JOKE_H
#include <QObject>
#include <QDataStream>

struct T_JokeRating
{
    int jId;        // 被评价的资源id 既是主键也是外键
    int uId;        // 评价用户id 既是主键也是外键
    qreal dRating;  // 评分

};


struct T_Joke
{
    int jId;
    QString strTitle;
    QString strDate;
    QString strContent;

    bool bOriginal; // 是否原创

    int upUid;        // 上传者用户id
    QString strNickname; // 上传者昵称


    quint64 llRatingNumOfPeople; // 评价总人数
    qreal dRatingToatalScore ; // 评价总评分
    qreal dRatingAverageScore;  // 评价平均评分 0-5

    //QVector<T_Rating> vecRating;    // 评价列表

    T_Joke()
        : jId(-1)
        , bOriginal(false)
        , upUid(-1)
        , llRatingNumOfPeople(0)
        , dRatingToatalScore(0)
        , dRatingAverageScore(0)
    {

    }

#ifndef QT_NO_DATASTREAM
    friend QDataStream & operator>>(QDataStream & in, T_Joke & data);
    friend QDataStream & operator<<(QDataStream & out, const T_Joke & data);
#endif

};
Q_DECLARE_METATYPE(T_Joke)


// filter
enum E_SelectType
{
    ES_SelectByWorld,
    ES_SelectByPenfriend,
    ES_SelectByMyUpload,
    ES_SelectByMyLocal
};

enum E_SortFiled
{
    ES_ByTime,
    ES_BySize,
    ES_ByName,
};

enum E_OrderType
{
    EO_ASC,
    EO_DESC,
};

struct T_JokeListRequest
{
    int nPageIndex; // 页码
    int nPageItems; // 当前页最大条目数
    int nSelectType;
    int nSortFiled;
    int nOrderType;

};

struct T_JokeListResp
{
\
    int nTotalItems;
    QList<T_Joke> listJoke;

};

#endif // __JOKE_H