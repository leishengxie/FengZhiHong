#ifndef CDAIRYHTTPCLIENT_H
#define CDAIRYHTTPCLIENT_H

#include "LHttpClient.h"

struct T_DairyUserData : public QObjectUserData
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

/*注意，qt5.8后 QOb已申明jectUserDataQ_DISABLE_COPY， 故这里不要Q_DECLARE_METATYPE*/
//Q_DECLARE_METATYPE(T_DairyUserData)


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

class CLLoopLoading;

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
    void get(const QUrl& urlRequest, int nTimeout = 6000);
    // 阻塞主线程， 直到当前请求完成
    //void blockGet(const QUrl& urlRequest, int nTimeout = 6000);

    // 异步get, QNetworkReply本身是异步属性，需要提供唯一标示。 适用于同时多个http请求
    void asyncGet(const QUrl& urlRequest, int nTag, int nTimeout = 6000);

    // 通过自定义任务列表，实现同步处理请求, 适用于加入多个http请求
    void syncGet(const QUrl& urlRequest, int nTag, int nTimeout = 6000);


    /// post
    void post(const QUrl &urlRequest, const QByteArray &data, int nTimeout = 6000);
    void post(const QUrl& urlRequest, const void* pData, int nDataLen, int nTimeout = 6000);
    //void blockPost(const QUrl& urlRequest, const void* pData, int nDataLen, int nTimeout = 6000);

    void asyncPost(const QUrl& urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout = 6000);

    void syncPost(const QUrl& urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout = 6000);

signals:
    void finishedWithTag(int nTag, const QByteArray& data);
    void finishedAll();
    void finished_1(const QByteArray& data);

public slots:
    void onReadyReadAsync();
    void onReadyReadAsyn();

    virtual void onFinished();
    void onError(QNetworkReply::NetworkError errorCode);
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

    static CLLoopLoading* s_pLoopLoading;


};

#endif // CDAIRYHTTPCLIENT_H
