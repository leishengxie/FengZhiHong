#ifndef CDAIRYHTTPCLIENT_H
#define CDAIRYHTTPCLIENT_H

#include "LHttpClient.h"

struct T_DairyUserData : QObjectUserData
{
    int nTag;   // 唯一标示
   bool bAsync; // 是否异步

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
/// \brief The CDairyHttpClient class   添加对多个http请求的处理，禁止继承, 提供同步和异步请求
///
class CDairyHttpClient final : public LHttpClient
{
    Q_OBJECT
public:
    explicit CDairyHttpClient(QObject *parent = 0);

    // 异步get, QNetworkReply本身是异步属性，需要提供唯一标示。
    void asyncGet(const QUrl& urlRequest, int nTag, int nTimeout = 6000);

    // 通过自定义任务列表，实现同步处理请求
    void syncGet(const QUrl& urlRequest, int nTag, int nTimeout = 6000);

    void asyncPost(const QUrl& urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout = 6000);

    void syncPost(const QUrl& urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout = 6000);

signals:
    void finished(int nTag, const QByteArray& data);

public slots:
    void onReadyRead();
    virtual void onFinished();

private:
    void startSyncRequest();

private:
    // 处理异步接收的数据
    QMap<int, LHttpDataBuffer> m_mapDataBuffer;

    // 同步请求任务列表
    QList<T_TaskInfo> m_lstTaskTag;
};

#endif // CDAIRYHTTPCLIENT_H
