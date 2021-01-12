#ifndef CARTICLE_H
#define CARTICLE_H
#include <QDataStream>

#include <QRect>
#include <QString>

enum E_ArticleType
{

};

struct T_Article
{

    QRect rect;
    QRectF f;
    QString str;

    T_Article();

    int jId;
    QString strTitle;
    QString strDate;
    QString strContent;

    bool bOriginal; // 是否原创

    int upUid;        // 上传者用户id
    QString strNickname; // 上传者昵称, 目前没有使用第三方登录， 先用用户名顶替


    quint64 llRatingNumOfPeople; // 评价总人数
    qreal dRatingToatalScore ; // 评价总评分
    qreal dRatingAverageScore;  // 评价平均评分 0-5
};

#endif // CARTICLE_H
