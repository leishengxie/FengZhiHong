#include "DairyHttpClient.h"
#include "widgets/LLoopLoading.h"
#include <QMessageBox>

CLLoopLoading* CDairyHttpClient::s_pLoopLoading = NULL;

CDairyHttpClient::CDairyHttpClient(QObject* parent, bool bAutoReleaseOnFinished)
    : LHttpClient(parent)
    , m_bAutoReleaseOnFinished(bAutoReleaseOnFinished)
{
    #ifndef ANDROID_MOBILE_PALTFORM_QML
    if (s_pLoopLoading == NULL)
    {
        s_pLoopLoading = new CLLoopLoading();
    }
#endif
//    QWidget* pWidget = qobject_cast<QWidget*>(parent);
//    if (pWidget)
//    {
//        s_pLoopLoading->setParent(pWidget);
    //    }
}

void CDairyHttpClient::get(const QUrl &urlRequest, int nTimeout)
{
    if (urlRequest.isEmpty())
    {
        return;
    }
    QNetworkRequest request(urlRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_netReply = m_netAccessManager->get(request);
    connect(m_netReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_netReply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(m_netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));

    #ifndef ANDROID_MOBILE_PALTFORM_QML
    s_pLoopLoading->start("正在加载中!");
#endif
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

void CDairyHttpClient::post(const QUrl & urlRequest, const QByteArray & data, int nTimeout)
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

#ifndef ANDROID_MOBILE_PALTFORM_QML
    // add 20200111
    // 测试证明， QWidget作为加载提示框，其窗口大小被Android最大化问题， qml界面和QWidget会界面分离. 按手机的返回键即使模态也会消失
    s_pLoopLoading->start("正在加载中!");
    // end add
#endif
}

void CDairyHttpClient::post(const QUrl & urlRequest, const void* pData, int nDataLen, int nTimeout)
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
    QVariant variant = m_netReply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
    QNetworkReply::NetworkError errorCode = m_netReply->error();
    // toUtf82次?, 因为传输过来的已经是utf8字节数组，toByteArray()默认又转为utf8一次。
    //QByteArray byteArray =  variant.toByteArray();
    //QString status_text = QString::fromUtf8(byteArray);

    QByteArray byteArray = variant.toString().toLatin1();
    QString status_text = QString::fromUtf8(byteArray);


    //QNetworkReply::NetworkError eNetworkError = m_netReply->error();
    m_netReply->deleteLater();
    m_netReply = NULL;

    #ifndef ANDROID_MOBILE_PALTFORM_QML
    s_pLoopLoading->stop();
#endif


    if (status_code == 200)
    {
        emit finished_1(m_httpDataBuffer.readAll());
    }
    else
    {
        if (errorCode == QNetworkReply::UnknownServerError)
        {
            QMessageBox::information(NULL, QString::number(status_code), status_text);
        }
    }

    m_httpDataBuffer.clear();
    if (m_bAutoReleaseOnFinished)
    {
        deleteLater();
    }
}

void CDairyHttpClient::onError(QNetworkReply::NetworkError errorCode)
{
    if (errorCode == QNetworkReply::UnknownServerError)
    {
        return;
    }
    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::information(NULL, "NetworkError:" + QString::number(errorCode) , pNetworkReply->errorString());
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
