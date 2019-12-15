#include "DairyHttpClient.h"

CDairyHttpClient::CDairyHttpClient(QObject* parent, bool bAutoReleaseOnFinished)
    : QObject(parent)
    , m_bAutoReleaseOnFinished(bAutoReleaseOnFinished)
{

}



void CDairyHttpClient::asyncGet(const QUrl & urlRequest, int nTag, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }

    if (m_mapDataBuffer.contains(nTag))
    {
        return;
    }

    m_request.setUrl(urlRequest);
//     m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-protobuf");
//    m_request.setRawHeader("Connection", "keep-alive");
    T_DairyUserData* pData = new T_DairyUserData(nTag, true);
    QNetworkReply* pNetworkReply = m_netAccessManager->get(m_request);
    pNetworkReply->setUserData(Qt::UserRole + 1, pData);
    connect(pNetworkReply, SIGNAL(readyRead()), this, SLOT(onReadyReadAsync()));
    connect(pNetworkReply, SIGNAL(finished()), this, SLOT(onFinishedAsync()));
    connect(pNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(pNetworkReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));

}

void CDairyHttpClient::syncGet(const QUrl & urlRequest, int nTag, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    T_TaskInfo tTaskInfo;
    tTaskInfo.nTag = nTag;
    tTaskInfo.urlRequest = urlRequest;
    tTaskInfo.eRequsetType = ER_Get;

//        if (m_lstTaskTag.contains(tTaskInfo))
//        {
//            return;
//        }

    startSyncRequest();

}

void CDairyHttpClient::asyncPost(const QUrl & urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }

    if (m_mapDataBuffer.contains(nTag))
    {
        return;
    }

    m_request.setUrl(urlRequest);
    T_DairyUserData* pUserData = new T_DairyUserData(nTag, true);
    QNetworkReply* pNetworkReply  = m_netAccessManager->post(m_request, QByteArray((const char*)pData, nDataLen));
    pNetworkReply->setUserData(Qt::UserRole + 1, pUserData);
    connect(pNetworkReply, SIGNAL(readyRead()), this, SLOT(onReadyReadAsync()));
    connect(pNetworkReply, SIGNAL(finished()), this, SLOT(onFinishedAsync()));
    connect(pNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(pNetworkReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
}

void CDairyHttpClient::syncPost(const QUrl & urlRequest, int nTag, const void* pData, int nDataLen, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    T_TaskInfo tTaskInfo;
    tTaskInfo.nTag = nTag;
    tTaskInfo.urlRequest = urlRequest;
    tTaskInfo.eRequsetType = ER_Post;
    tTaskInfo.byteArray.append(pData, nDataLen);

//    if (m_lstTaskTag.contains(tTaskInfo))
//    {
//        return;
//    }

    startSyncRequest();
}

void CDairyHttpClient::onReadyReadAsync()
{
    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
    T_DairyUserData* pUserData = (T_DairyUserData*)(pNetworkReply->userData(Qt::UserRole + 1));
    m_mapDataBuffer[pUserData->nTag].push_back(m_netReply->readAll());

}

void CDairyHttpClient::onReadyReadAsyn()
{
    return onReadyRead();

}

void CDairyHttpClient::onFinished()
{
    LHttpClient::onFinished();
    if (m_bAutoReleaseOnFinished)
    {
        deleteLater();
    }
}

void CDairyHttpClient::onFinishedAsync()
{
    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
    T_DairyUserData* pUserData = (T_DairyUserData*)(pNetworkReply->userData(Qt::UserRole + 1));
    emit finished(pUserData->nTag, m_mapDataBuffer.value(pUserData->nTag));
    m_mapDataBuffer.remove(pUserData->nTag);
    pNetworkReply->deleteLater();
    pNetworkReply = NULL;

    if (m_mapDataBuffer.isEmpty())
    {
        //emit finishedAll();
        if (m_bAutoReleaseOnFinished)
        {
            deleteLater();
        }
    }


}

void CDairyHttpClient::onFinishedAsyn()
{

    T_DairyUserData* pUserData = (T_DairyUserData*)(m_netReply->userData(Qt::UserRole + 1));
    emit finished(pUserData->nTag, m_httpDataBuffer);

    m_httpDataBuffer.clear();   // 注意清除
    m_netReply->deleteLater();
    m_netReply = NULL;

    // 删除已完成任务
    m_lstTaskTag.pop_front();

    if (m_lstTaskTag.isEmpty())
    {
        //emit finishedAll();
        if (m_bAutoReleaseOnFinished)
        {
            deleteLater();
        }
    }
    else
    {
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
    switch (tTaskInfo.eRequsetType)
    {
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
        T_DairyUserData* pUserData = new T_DairyUserData(tTaskInfo.nTag, false);
        m_netReply->setUserData(Qt::UserRole + 1, pUserData);
    }
}
