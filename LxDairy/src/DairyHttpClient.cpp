#include "DairyHttpClient.h"

CDairyHttpClient::CDairyHttpClient(QObject *parent) : QObject(parent)
{

}

void CDairyHttpClient::asyncGet(const QUrl &urlRequest, int nTag, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    m_request.setUrl(urlRequest);
//     m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-protobuf");
//    m_request.setRawHeader("Connection", "keep-alive");
    T_DairyUserData *pData = new T_DairyUserData(nTag, true);
    QNetworkReply* pNetworkReply = m_netAccessManager->get(m_request);
    pNetworkReply->setUserData(Qt::UserRole + 1, pData);
    connect(pNetworkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(pNetworkReply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(pNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(pNetworkReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));

}

void CDairyHttpClient::syncGet(const QUrl &urlRequest, int nTag, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    T_TaskInfo tTaskInfo;
    tTaskInfo.nTag = nTag;
    tTaskInfo.urlRequest = urlRequest;
    tTaskInfo.eRequsetType = ER_Get;
    startSyncRequest();

}

void CDairyHttpClient::asyncPost(const QUrl &urlRequest, int nTag, const void *pData, int nDataLen, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    m_request.setUrl(urlRequest);
    T_DairyUserData *pUserData = new T_DairyUserData(nTag, true);
    QNetworkReply* pNetworkReply  = m_netAccessManager->post(m_request, , QByteArray((const char*)pData, nDataLen);
    pNetworkReply->setUserData(Qt::UserRole + 1, pUserData);
    connect(pNetworkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(pNetworkReply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(pNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(pNetworkReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
}

void CDairyHttpClient::syncPost(const QUrl &urlRequest, int nTag, const void *pData, int nDataLen, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    T_TaskInfo tTaskInfo;
    tTaskInfo.nTag = nTag;
    tTaskInfo.urlRequest = urlRequest;
    tTaskInfo.eRequsetType = ER_Post;
    tTaskInfo.byteArray.append(pData,nDataLen);
    startSyncRequest();
}

void CDairyHttpClient::onReadyRead()
{
    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
    T_DairyUserData* pUserData = (T_DairyUserData *)(pNetworkReply->userData(Qt::UserRole + 1));
    if (pUserData->bAsync)
    {
        m_mapDataBuffer[pUserData->nTag].push_back(m_netReply->readAll());
    }
    else
    {
        m_httpDataBuffer.push_back(m_netReply->readAll());
    }
}

void CDairyHttpClient::onFinished()
{
    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
    T_DairyUserData* pUserData = (T_DairyUserData *)(pNetworkReply->userData(Qt::UserRole + 1));
    if (pUserData->bAsync)
    {
        emit finished(pUserData->nTag, m_mapDataBuffer.value(pUserData->nTag));
        m_mapDataBuffer.remove(pUserData->nTag);
        pNetworkReply->deleteLater();
        pNetworkReply = NULL;
    }
    else
    {
        emit finished(pUserData->nTag, m_httpDataBuffer);
        m_lstTaskTag.pop_front();
        m_httpDataBuffer.clear();   // 注意清除
        m_netReply->deleteLater();
        m_netReply = NULL;
        startSyncRequest();
    }
}

void CDairyHttpClient::startSyncRequest()
{
    if (m_lstTaskTag.isEmpty())
    {
        return;
    }

    // 正在下载
    if (m_netReply)
    {
        return;
    }

    // 指向下个任务
    T_TaskInfo tTaskInfo = m_lstTaskTag.first();
    switch (tTaskInfo.eRequsetType) {
    case ER_Get:
        get(tTaskInfo.urlRequest);
        break;
    case ER_Post:
        post(tTaskInfo.urlRequest, tTaskInfo.byteArray, tTaskInfo.byteArray.length());
        break;
    default:
        break;
    }
    if (m_netReply)
    {
        T_DairyUserData *pUserData = new T_DairyUserData(tTaskInfo.nTag, false);
        m_netReply->setUserData(Qt::UserRole + 1, pUserData);
    }
}
