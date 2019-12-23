#include "DairyHttpClient.h"
#include "widgets/LLoopLoading.h"
#include <QMessageBox>

CLLoopLoading* CDairyHttpClient::s_pLoopLoading = NULL;

CDairyHttpClient::CDairyHttpClient(QObject* parent, bool bAutoReleaseOnFinished)
    : LHttpClient(parent)
    , m_bAutoReleaseOnFinished(bAutoReleaseOnFinished)
{
    if (s_pLoopLoading == NULL)
    {
        s_pLoopLoading = new CLLoopLoading();
    }
    QWidget* pWidget = qobject_cast<QWidget*>(parent);
    if (pWidget)
    {
        s_pLoopLoading->setParent(pWidget);
    }
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

void CDairyHttpClient::post(const QUrl &urlRequest, const QByteArray &data, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }

    QNetworkRequest request(urlRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_netReply = m_netAccessManager->post(request, data);
    connect(m_netReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_netReply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(m_netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));

    s_pLoopLoading->start("正在加载中!");
}

void CDairyHttpClient::post(const QUrl &urlRequest, const void *pData, int nDataLen, int nTimeout)
{
    post(urlRequest, QByteArray((const char*)pData, nDataLen), nTimeout);

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
    tTaskInfo.byteArray.append(QByteArray((const char*)pData, nDataLen));

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
    int status_code = m_netReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString status_text_1 = m_netReply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    QString status_text = QString::fromUtf8(m_netReply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray());
    //å¾\210å¥½

    QNetworkReply::NetworkError eNetworkError = m_netReply->error();
    m_netReply->deleteLater();
    m_netReply = NULL;

    s_pLoopLoading->stop();

    if(eNetworkError == QNetworkReply::NoError)
    {
        emit finished_1(m_httpDataBuffer.readAll());
        m_httpDataBuffer.clear();
        if (status_code != 200)
        {
            QMessageBox::information(NULL, QString::number(status_code), status_text);
        }
    }
    else
    {
        qDebug() << "failed" << status_code;
        QMessageBox::information(NULL, QString::number(status_code), status_text);
    }


    if (m_bAutoReleaseOnFinished)
    {
        deleteLater();
    }
}

void CDairyHttpClient::onFinishedAsync()
{
    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
    T_DairyUserData* pUserData = (T_DairyUserData*)(pNetworkReply->userData(Qt::UserRole + 1));
    LHttpDataBuffer httpDataBuffer = m_mapDataBuffer.value(pUserData->nTag);
    emit finishedWithTag(pUserData->nTag, httpDataBuffer.readAll());
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
    emit finishedWithTag(pUserData->nTag, m_httpDataBuffer.readAll());

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
