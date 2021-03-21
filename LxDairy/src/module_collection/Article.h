#ifndef CARTICLE_H
#define CARTICLE_H
#include <QDataStream>

#include <QRect>
#include <QString>

/// 文学
//按载体分为：口头文学、书面文学、网络文学三大类。
//按地域分为：外国文学、中国文学等。
//按读者年龄分为：儿童文学、成人文学等。
//按读者群体及内容分为：严肃文学和通俗文学或大众文学、民间文学、少数民族文学、宗教文学等。
//按内容分为：史传文学、纪实文学、奇幻文学、报道文学等。
//按表达体裁分为：小说、散文、诗歌、报告文学、新韵文、戏剧、歌剧、剧本、民间传说、寓言、笔记小说、野史、童话
    //、对联和笑话等；其他如史传、哲理、赋、骈文、小品文、文学批评、有文字剧情架构的电脑游戏与动漫等。
//按创作理念分为：浪漫主义文学、现实主义文学等。

/// 按表达体裁
enum E_ArticleGenreType
{
    EA_Joke,    //  笑话
    EA_Fiction, //  小说
    EA_Prose,   //  散文
    EA_Poetry,  //  诗歌
    EA_Drama,   //  戏剧
    EA_Fable,   //  寓言
    EA_FairyTale,// 童话
    EA_Biography,// 传记
};


///
/// \brief The T_Article struct 文章, 基本的单元
///
struct T_Article
{

//    QRect rect;
//    QRectF f;
//    QString str;

//    T_Article();

    int jId;
    QString strTitle;
    QString strDate;
    QString strContent;

    bool bOriginal; // 是否原创

    int upUid;        // 上传者用户id
    QString strNickname; // 上传者昵称, 目前没有使用第三方登录， 先用用户名顶替

    int nGenreType; // 体裁类型


    quint64 llRatingNumOfPeople; // 评价总人数
    qreal dRatingToatalScore ; // 评价总评分
    qreal dRatingAverageScore;  // 评价平均评分 0-5

    //QVector<T_Rating> vecRating;    // 评价列表

    T_Article()
        : jId(-1)
        , bOriginal(false)
        , upUid(-1)
        , llRatingNumOfPeople(0)
        , dRatingToatalScore(0)
        , dRatingAverageScore(0)
    {

    }

#ifndef QT_NO_DATASTREAM
    friend QDataStream & operator>>(QDataStream & in, T_Article & data);
    friend QDataStream & operator<<(QDataStream & out, const T_Article & data);
#endif
};


Q_DECLARE_METATYPE(T_Article)


// filter
enum E_SelectType
{
    ES_SelectByWorld,
//    ES_SelectByPenfriend,
    ES_SelectByMyUpload,
    ES_Max
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

struct T_ArticleListRequest
{
    int uId;
    int nPageIndex; // 页码
    int nPageItems; // 当前页最大条目数
    int nSelectType;
    int nSortFiled;
    int nOrderType;

    T_ArticleListRequest()
        : nPageIndex(1)
        , nPageItems(10)
        , nSelectType(ES_SelectByWorld)
        , nSortFiled(ES_ByTime)
        , nOrderType(EO_ASC)
    {

    }

    void init()
    {
        nPageIndex = 1;
        nPageItems = 10;
        nSelectType = ES_SelectByWorld;
        nSortFiled = ES_ByTime;
        nOrderType = EO_ASC;
    }

    void reset()
    {
        init();
    }

    friend QDataStream & operator>>(QDataStream & in, T_ArticleListRequest & data);
    friend QDataStream & operator<<(QDataStream & out, const T_ArticleListRequest & data);

};

struct T_ArticleListResp
{
    int nTotalItems;
    QList<T_Article> listJoke;

    T_ArticleListResp()
        : nTotalItems(0)
    {

    }

    friend QDataStream & operator>>(QDataStream & in, T_ArticleListResp & data);
    friend QDataStream & operator<<(QDataStream & out, const T_ArticleListResp & data);
};


struct T_ArticleRating
{
    int jId;        // 被评价的资源id 既是主键也是外键
    int uId;        // 评价用户id 既是主键也是外键
    qreal dRating;  // 评分

    friend QDataStream & operator>>(QDataStream & in, T_ArticleRating & data);
    friend QDataStream & operator<<(QDataStream & out, const T_ArticleRating & data);
};

#endif // CARTICLE_H
