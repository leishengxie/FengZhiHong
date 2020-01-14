#ifndef CDAIRY_H
#define CDAIRY_H


#include <QObject>
#include <QDataStream>

#define FORMAT_DATETIME                 "yyyy-MM-dd hh:mm:ss"
#define FORMAT_DATETIME_DISPLAYER       "yyyy年MM月dd日 hh:mm"
#define INVAILD_DAIRY_ID                -1
// Q_DISABLE_COPY(QObject) 不继承QObject
//QObject 中没有提供一个拷贝构造函数和赋值操作符给外界使用，其实拷贝构造和赋值的操作都是已经声明了的，但是它们被使用了Q_DISABLE_COPY() 宏放在了private区域。
//因此所有继承自QObject的类都使用这个宏声明了他们的拷贝构造函数和赋值操作符为私有。
struct T_Dairy
{
    T_Dairy();

    int did;
    int uid;
    QString strTitle;
    QString strDateTime;
    QString strWeather;
    QString strTag;
    QString strContent;


//    SETGETCONST(int, did, Did)
//    SETGETCONST(int, uid, Uid)
//    SETGETCONST(QString, strTitle, Title)
//    SETGETCONST(QString, strDateTime, DateTime)
//    SETGETCONST(QString, strWeather, Weather)
//    SETGETCONST(QString, strTag, Tag)
//    SETGETCONST(QString, strContent, Content)

    bool isEmptyContent()
    {
        return strTitle.isEmpty() && strContent.isEmpty();
    }

    bool isNewDairy() const
    {
        return did == INVAILD_DAIRY_ID;
    }

    //QList contains need
    bool operator == (const T_Dairy &right) const;

    friend QDataStream & operator>>(QDataStream & in, T_Dairy & data);
    friend QDataStream & operator<<(QDataStream & out, const T_Dairy & data);

};
Q_DECLARE_METATYPE(T_Dairy)


struct T_DairyListRequest
{
    int uid;
    int nPageIndex; // 页码
    int nPageItems; // 当前页最大条目数


    T_DairyListRequest()
        : uid(-1)
        , nPageIndex(1)
        , nPageItems(10)

    {

    }

    void init()
    {
        uid = -1;
        nPageIndex = 1;
        nPageItems = 10;

    }

    void reset()
    {
        init();
    }

    friend QDataStream & operator>>(QDataStream & in, T_DairyListRequest & data);
    friend QDataStream & operator<<(QDataStream & out, const T_DairyListRequest & data);
};

struct T_DairyListResp
{
    int nTotalItems;
    QList<T_Dairy> dairyList;
    T_DairyListResp()
        : nTotalItems(0)
    {

    }

    friend QDataStream & operator>>(QDataStream & in, T_DairyListResp & data);
    friend QDataStream & operator<<(QDataStream & out, const T_DairyListResp & data);
};

struct T_DairyDeleteReq
{
    QList<T_Dairy> dairyList;
    T_DairyDeleteReq()
    {

    }

    friend QDataStream & operator>>(QDataStream & in, T_DairyDeleteReq & data);
    friend QDataStream & operator<<(QDataStream & out, const T_DairyDeleteReq & data);
};

#endif // CDAIRY_H
