/******************************************************************************
**
** @file
** HttpClient.cpp
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

#include "HttpClient.h"
#include <QDebug>

using namespace xgKtv;

// 安全删除 QNetworkReply 对象
inline void DELETE_Reply(QNetworkReply* &pReply, bool bAbort = false)
{
	if (NULL != pReply)
	{
		if (bAbort)
		{
			pReply->abort();
		}
		pReply->deleteLater();
		pReply = NULL;
	}
}

// 安全删除 QTimer 对象
inline void DELETE_Timer(QTimer* &pTimer)
{
	if (NULL != pTimer)
	{
		pTimer->stop();
		pTimer->deleteLater();
		pTimer = NULL;
	}
}

// 构造/析构函数
CHttpClient::CHttpClient(QObject *parent, ULONG ulQueryTag)
	: QObject(parent)
	, m_accessManager(this)
	, m_pReply(NULL)
	, m_bAbortRequest(false)
	, m_unLastQueryTime(0)
	, m_timeout(this)
	, m_ulQueryTag(ulQueryTag)
	, m_llRangeOffset(0)
	, m_llRangeLength(0)
	, m_llTotalLength(-1)
	, m_bSelfDestroy(false)
	, m_eStatus(ES_Closed)
	, m_pTimerRead(NULL)
{
	connect(&m_timeout, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

CHttpClient::~CHttpClient()
{
	DELETE_Reply(m_pReply);
	DELETE_Timer(m_pTimerRead);
}

// 使用http GET下载数据
bool CHttpClient::e_HttpDownload(const QUrl& requestUrl, LONGLONG llOffset, LONGLONG llLength, int nTimeout)
{
	// 完全一致的URL，在超时时间内直接返回true
	UINT unTime = xgKtv::GetTickCount();
	if (requestUrl == m_requestUrl && m_unLastQueryTime > 0 && int(unTime - m_unLastQueryTime) < nTimeout)
	{
		if (m_bSelfDestroy)
		{
			deleteLater();
		}
		return false;
	}
	// qDebug() << "******" << requestUrl << endl;
	m_unLastQueryTime = unTime;

	if (NULL != m_pReply)
	{
		m_bAbortRequest = true;
		DELETE_Reply(m_pReply, true);
	}

	DELETE_Timer(m_pTimerRead);

	m_strError = "";
	m_eStatus  = ES_Downloading;
	m_requestUrl = requestUrl;

	QNetworkRequest request(requestUrl);

	#ifndef QT_NO_SSL
	if (requestUrl.toString().startsWith("https", Qt::CaseInsensitive))
	{ // 设置https访问
		QSslConfiguration sslConfig = request.sslConfiguration();
		sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
		request.setSslConfiguration(sslConfig);
	}
	#endif // QT_NO_SSL

	if (llOffset > 0 || llLength > 0)
	{ // 设置数据获取范围

#ifdef WIN32
		const static char RANGE_Format[] = "bytes=%I64d-";
		const static char RANGE_FormatEnd[] = "bytes=%I64d-%I64d";
#else
		const static char RANGE_Format[] = "bytes=%lld-";
		const static char RANGE_FormatEnd[] = "bytes=%lld-%lld";
#endif

		char szRange[64] = "";
		if (llLength > 0)
		{
			llLength += llOffset - 1; // 把长度转换为尾部位置
			snprintf(szRange, 63, RANGE_FormatEnd, llOffset, llLength);
		}
		else
		{
			snprintf(szRange, 63, RANGE_Format, llOffset);
		}

		request.setRawHeader("Range", szRange);
	}

	m_dataBuf.clear();
	m_llRangeOffset = 0;
	m_llRangeLength = 0;
	m_llTotalLength = -1;

	m_bAbortRequest = false;
	m_pReply = m_accessManager.get(request);
	connect(m_pReply, SIGNAL(finished()), this, SLOT(httpFinished()));
	connect(m_pReply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
	connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));

	if (nTimeout > 0)
	{ // 设置超时时间
		m_timeout.setInterval(nTimeout);
		m_timeout.start();
	}
	return true;
}

// 获取查询目标主机域名
String CHttpClient::e_GetRequestHost() const
{
	if (!m_requestUrl.isEmpty())
	{
		String strUrl = m_requestUrl.toString().toUtf8().data();
		return strUrl.substr(0, strUrl.find('/', 8));
	}
	else
	{
		return "";
	}
}

// 取消上一次的http request
void CHttpClient::e_Cancel()
{
	m_timeout.stop();
	m_bAbortRequest = true;
	if (NULL != m_pReply)
	{
		m_pReply->abort();
	}
	m_unLastQueryTime = 0;
}

void CHttpClient::httpFinished()
{
	m_eStatus = ES_Closed;

	if (m_bAbortRequest)
	{ // 用户中止操作，则退出
		DELETE_Reply(m_pReply);
		return;
	}

	m_timeout.stop();
	bool bRet = false;
	if (NULL != m_pReply)
	{
		if (QNetworkReply::NoError == m_pReply->error())
		{
			QVariant theRedirection = m_pReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
			if (!theRedirection.isNull())
			{ // 处理URL跳转的情况
				QUrl newUrl = m_requestUrl.resolved(theRedirection.toUrl());
				e_HttpGet(newUrl);
				return; // 需要继续查询
			}

			bRet = true;
		}

		if (m_pReply->bytesAvailable() == 0)
		{ // 已读取完下载的全部数据
			DELETE_Timer(m_pTimerRead);
			DELETE_Reply(m_pReply);
		}

		emit downloadCompleted(bRet, this);
	}

	if (m_bSelfDestroy)
	{ // 销毁自身
		deleteLater();
	}
}

// 超时时间到达
void CHttpClient::onTimeout()
{
	m_strError = "Time out.";
	e_Cancel();

	if (m_bSelfDestroy)
	{ // 销毁自身
		deleteLater();
	}
}

void CHttpClient::httpReadyRead()
{
	if (m_timeout.isActive())
	{
		m_timeout.stop();
	}

	if (m_llTotalLength < 0)
	{
#ifdef WIN32
		const static char RANGE_Format[] = "bytes %I64d-%I64d/%I64d";
#else
		const static char RANGE_Format[] = "bytes %lld-%lld/%lld";
#endif
		QByteArray headerData = m_pReply->rawHeader("Content-Range");

		if (!headerData.isEmpty())
		{ // bytes 52428800-217674483/217674484
			sscanf(headerData.data(), RANGE_Format,
				   &m_llRangeOffset, &m_llRangeLength, &m_llTotalLength);
			m_llRangeLength = m_llRangeLength - m_llRangeOffset + 1;
		}
		else
		{
			m_llTotalLength = m_pReply->rawHeader("Content-Length").toLongLong();
		}
	}

	if (m_pReply->readBufferSize() == 0)
	{
		m_pReply->setReadBufferSize(1024*1024);
	}

	onReadReplyBuf();

	emit readyRead(this);
}

// 读取reply中已下载数据
void CHttpClient::onReadReplyBuf()
{
	m_readLock.lock();

	if (m_dataBuf.e_GetLength() < 1024*1024)
	{
		if (NULL != m_pReply)
		{
			int nBytesForRead = m_pReply->bytesAvailable();
			while (nBytesForRead > 0 && m_dataBuf.e_GetLength() < 1024*1024)
			{
				const QByteArray data = m_pReply->read(256*1024);
				m_dataBuf.e_Append(data);
				nBytesForRead -= data.size();
			}

			if (m_pReply->isFinished() && 0 == m_pReply->bytesAvailable())
			{
				DELETE_Timer(m_pTimerRead);
				m_pReply->deleteLater();
				m_pReply = NULL;
			}
		}
	}
	else if (NULL == m_pTimerRead)
	{
		m_pTimerRead = new QTimer(this);
		m_pTimerRead->setInterval(200);
		connect(m_pTimerRead, SIGNAL(timeout()), this, SLOT(onReadReplyBuf()), Qt::QueuedConnection);
		m_pTimerRead->start();
	}

	m_readLock.unlock();
}

void CHttpClient::httpError(QNetworkReply::NetworkError errorCode)
{
	m_timeout.stop();
	DELETE_Timer(m_pTimerRead);

	if ("" == m_strError)
	{
		m_strError  = QString::number(errorCode) + ": ";
		m_strError += m_pReply->errorString();
	}
	DELETE_Reply(m_pReply);
	emit downloadCompleted(false, this);
}

// 使用http POST发送网页数据
bool CHttpClient::e_HttpPost(const QUrl& requestUrl, const void* pData, int nDataLen, int nTimeout)
{
	//qDebug() << "******" << requestUrl << endl;
	m_unLastQueryTime = xgKtv::GetTickCount();

	if (NULL != m_pReply)
	{
		m_bAbortRequest = true;
		DELETE_Reply(m_pReply, true);
	}
	DELETE_Timer(m_pTimerRead);

	m_eStatus = ES_Uploading;
	m_strError = "";
	m_requestUrl = requestUrl;

	QNetworkRequest request(requestUrl);
	#ifndef QT_NO_SSL
	if (requestUrl.toString().startsWith("https", Qt::CaseInsensitive))
	{ // 设置https访问
		QSslConfiguration sslConfig = request.sslConfiguration();
		sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
		request.setSslConfiguration(sslConfig);
	}
	#endif // QT_NO_SSL

	m_dataBuf.clear();
	m_llRangeOffset = 0;
	m_llRangeLength = 0;
	m_llTotalLength = -1;

	m_bAbortRequest = false;
	m_pReply = m_accessManager.post(request, QByteArray((const char*)pData, nDataLen));
	connect(m_pReply, SIGNAL(finished()), this, SLOT(httpFinished()));
	connect(m_pReply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
	connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));

	if (nTimeout > 0)
	{ // 设置超时时间
		m_timeout.setInterval(nTimeout);
		m_timeout.start();
	}
	return true;
}

// 获取查询下载到的数据
QByteArray CHttpClient::e_GetData()
{
	QByteArray data;
	m_readLock.lock();
	if (!m_dataBuf.empty())
	{
		m_dataBuf.e_ReadAll(data);
	}
	m_readLock.unlock();
	return data;
}

// 读取下载到的数据
int CHttpClient::e_GetData(void* pBuffer, int nBufSize)
{
	int nDataLen = 0;
	m_readLock.lock();
	if (!m_dataBuf.empty())
	{
		nDataLen = m_dataBuf.e_Read(pBuffer, nBufSize);
	}
	m_readLock.unlock();
	return nDataLen;
}

// 创建临时对象，查询完后，自动删除
CHttpClient* CHttpClient::e_GetTempObject(ULONG ulQueryTag)
{
	CHttpClient* pHttp = new CHttpClient(NULL, ulQueryTag);
	if (NULL != pHttp)
	{
		pHttp->m_bSelfDestroy = true;
	}
	return pHttp;
}
