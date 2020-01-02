/******************************************************************************
**
** @file
** HttpClient.h
** @brief
** HTTP 网络数据下载
** @par
** 未处理C++异常
** @author
** panxf
** @date
** 2016-9-10
**
******************************************************************************/

#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QTimer>
#include <QMutex>
#include <xgutility.h>

class CHttpDataBuffer : public QList<QByteArray>
{
public:

    void e_Append(const QByteArray& data)
    {
        append(data);
    }

    int e_GetLength() const
    {
        int nLength = 0;
        QList<QByteArray>::const_iterator itor = begin();
        for ( ; end() != itor; ++itor)
        {
            nLength += (*itor).size();
        }
        return nLength;
    }

    int e_Read(void* pBuffer, int nBufLen)
    {
        int nRead = 0;
        while (nRead < nBufLen && !empty())
        {
            QByteArray& data = *begin();
            const int nDataLen = data.size();
            const int nCopyLen = std::min(nDataLen, nBufLen - nRead);
            memcpy(((char*)pBuffer) + nRead, data.data(), nCopyLen);
            if (nCopyLen == nDataLen)
            {
                pop_front();
            }
            else
            {
                data.remove(0, nCopyLen);
            }
            nRead += nCopyLen;
        }
        return nRead;
    }

    int e_ReadAll(QByteArray& data)
    {
        data.reserve(e_GetLength());
        QList<QByteArray>::iterator itor = begin();
        for ( ; end() != itor; ++itor)
        {
            data.append(*itor);
        }
        return data.size();
    }
};

// class CHttpClient
class CHttpClient : public QObject
{
    Q_OBJECT
public:

    enum E_Status
    {
        ES_Closed,
        ES_Downloading,
        ES_Uploading
    };

    // 构造/析构函数
    explicit CHttpClient(QObject *parent = NULL, ULONG ulQueryTag = 0);
    virtual ~CHttpClient();

    ///
    /// @par 功能
    /// 返回对象创建时设置的查询标记
    /// @return - 标记
    ///
    ULONG e_QueryTag() const
    {
        return m_ulQueryTag;
    }

    ///
    /// @par 功能
    /// 使用http GET获取网页数据
    /// @param[in] requestUrl - 查询URL
    /// @param[in] nTimeout - 超时时间
    /// @return - 下载是否成功
    ///
    bool e_HttpGet(const QUrl& requestUrl, int nTimeout = 6000)
    {
        return e_HttpDownload(requestUrl, 0, 0, nTimeout);
    }

    ///
    /// @par 功能
    /// 使用http GET下载数据
    /// @param[in] requestUrl - 查询URL
    /// @param[in] llOffset - 下载范围起始
    /// @param[in] llLength - 下载范围大小
    /// @param[in] nTimeout - 超时时间
    /// @return - 下载是否成功
    ///
    bool e_HttpDownload(const QUrl& requestUrl, LONGLONG llOffset, LONGLONG llLength, int nTimeout = 6000);

    ///
    /// @par 功能
    /// 使用http POST发送网页数据
    /// @param[in] requestUrl - 查询URL
    /// @param[in] pData - 要发送的数据
    /// @param[in] nDataLen - 数据大小
    /// @param[in] nTimeout - 超时时间
    /// @return - 发送是否成功
    ///
    bool e_HttpPost(const QUrl& requestUrl, const void* pData, int nDataLen, int nTimeout = 6000);

    ///
    /// @par 功能
    /// 获取查询目标主机域名
    /// @return - 主机域名
    ///
    xgKtv::String e_GetRequestHost() const;

    ///
    /// @par 功能
    /// 取消上一次的http request
    ///
    void e_Cancel();

    ///
    /// @par 功能
    /// 获取查询下载到的数据
    /// @return - 数据
    /// @note 此函数未考虑多线程读取问题，即不能用于多线程
    ///
    QByteArray e_GetData();

    ///
    /// @par 功能
    /// 获取已下载到的数据大小
    /// @return - 数据大小
    ///
    int e_GetDataSize()
    {
        int nSize = 0;
        m_readLock.lock();
        nSize = m_dataBuf.e_GetLength();
        m_readLock.unlock();
        return nSize;
    }

    ///
    /// @par 功能
    /// 读取下载到的数据
    /// @param[out] pBuffer - 获取数据缓存
    /// @param[in] nBufSize - 缓存大小
    /// @return - 数据大小
    ///
    int e_GetData(void* pBuffer, int nBufSize);

    ///
    /// @par 功能
    /// 获取下载原始文件数据大小
    /// @return - 数据大小
    ///
    LONGLONG e_GetDownloadSize() const
    {
        return m_llTotalLength <= 0 ? 0 : m_llTotalLength;
    }

    ///
    /// @par 功能
    /// 获取网络查询错误
    /// @return - 错误
    ///
    const QString& e_Error() const
    {
        return m_strError;
    }

    ///
    /// @par 功能
    /// 获取网络查询状态
    /// @return - 状态
    ///
    E_Status e_Status() const
    {
        return m_eStatus;
    }

public:

    ///
    /// @par 功能
    /// 创建临时对象，查询完后，自动删除
    /// @param[in] ulQueryTag - 查询标记
    /// @return - CHttpClient指针
    ///
    static CHttpClient* e_GetTempObject(ULONG ulQueryTag = 0);

signals:

    // http下载完成事件
    void downloadCompleted(bool bOk, CHttpClient* pHttpQuery);

    // 数据接收事件
    void readyRead(CHttpClient* pHttpQuery);


private slots:

    void httpFinished();
    void httpReadyRead();
    void httpError(QNetworkReply::NetworkError errorCode);

    // 读取reply中已下载数据
    void onReadReplyBuf();

public slots:

    // 超时时间到达
    void onTimeout();

private:

    // http 查询
    QNetworkAccessManager m_accessManager;

    // http 下载
    QNetworkReply* m_pReply;

    // http查询地址
    QUrl m_requestUrl;

    // 取消查询动作
    bool m_bAbortRequest;

    // HTTP 上次查询时间
    UINT m_unLastQueryTime;

    // 超时定时器
    QTimer m_timeout;

    // 对象创建时设置的查询标记
    const ULONG m_ulQueryTag;

    // 查询范围
    LONGLONG m_llRangeOffset;
    LONGLONG m_llRangeLength;
    LONGLONG m_llTotalLength;

    // 错误代码
    QString m_strError;

    // 自我删除标记
    bool m_bSelfDestroy;

    // Http 当前状态
    volatile E_Status m_eStatus;

    // 支持多线程读取数据
    QMutex m_readLock;

    // 内部缓存，支持多线程读取
    CHttpDataBuffer m_dataBuf;

    // 数据读取定时器
    QTimer* m_pTimerRead;
};

#endif // __HTTP_CLIENT_H__
