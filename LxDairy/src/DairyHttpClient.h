#ifndef CDAIRYHTTPCLIENT_H
#define CDAIRYHTTPCLIENT_H

#include "LHttpClient.h"

struct T_DairyUserData : QObjectUserData
{
    int nTag;   // 唯一标示
   bool bAsync; // 是否异步

   T_DairyUserData()
       : nTag(-1)
       , bAsync(false)
   {

   }

   T_DairyUserData(int nTag, bool bAsync = false)
       : nTag(nTag)
       , bAsync(bAsync)
   {

   }
};
Q_DECLARE_METATYPE(T_DairyUserData)


enum E_RequsetType
{
    ER_Get,
    ER_Post
};

// 同步的任务
struct T_TaskInfo
{
    int nTag;   // 唯一标示
    E_RequsetType eRequsetType;
    QUrl urlRequest;
    QByteArray byteArray;
};

///
/// \brief The CDairyHttpClient class   不知道原来的get请求会不会把前一次get的请求终止掉。所以新加了几个自定义的请求方式
/// asyncGet 添加对多个http请求的处理，禁止继承, 提供同步和异步请求
/// ，其实大可不必封装，直接使用qt给的，只是一些通用性的东西需要统一一下。
///
class CDairyHttpClient final : public LHttpClient
{
    Q_OBJECT
public:
    // bAutoReleaseOnFinished== false适用于同时多个请求， true适用于单个请求
    explicit CDairyHttpClient(QObject *parent = 0, bool bAutoReleaseOnFinished = false);


    /// get
    // 阻塞主线程， 直到当前请求完成
    //void blockGet(const QUrl& urlRequest, int nTimeout = 6000);

    // 异步get, QNetworkReply本身是异步属性，需要提供唯一标示。 适用于同时多个http请求
    void asyncGet(const QUrl& urlRequest, int nTag, int nTimeout = 6000);

    // 通过自定义任务列表，实现同步处理请求, 适用于加入多个http请求
    void syncGet(const QUrl& urlRequest, int nTag, int nTimeout = 6000);


    /// post
    void asyncPost(const QUrl& urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout = 6000);

    void syncPost(const QUrl& urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout = 6000);

signals:
    void finished(int nTag, const QByteArray& data);
    void finishedAll();

public slots:
    void onReadyReadAsync();
    void onReadyReadAsyn();

    virtual void onFinished();
    void onFinishedAsync();
    void onFinishedAsyn();

private:
    void startSyncRequest();

private:
    // 处理异步接收的数据
    QMap<int, LHttpDataBuffer> m_mapDataBuffer;

    // 同步请求任务列表
    QList<T_TaskInfo> m_lstTaskTag;

    //
    bool m_bAutoReleaseOnFinished;
};

#endif // CDAIRYHTTPCLIENT_H
