#include "LHttpConnection.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QSettings>

#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LResponderFactory.h"

#ifdef Q_OS_WIN
    #include <winsock2.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
#endif
#include "utils/LAsyncLogger.h"
#include <QThread>

CLHttpConnection::CLHttpConnection(QObject* parent)
    : QTcpSocket(parent)
    , m_pRequest(0)
    //, m_pResponse(0)
{
    aDebug() << "HttpConnection__this " << endl;
    connect(this, SIGNAL(readyRead()), this, SLOT(parseRequest()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
}

CLHttpConnection::~CLHttpConnection()
{
    aDebug() << "~HttpConnection__this - " << endl;
}

///
/// \brief 处理请求, 根据情况是否是长连接决定解析当次完成后是否关闭连接
///
void CLHttpConnection::parseRequest()
{
    // The loop adds support for HTTP pipelinig
    while (bytesAvailable())
    {
        if (!m_pRequest)
        {
            m_pRequest = new CLHttpRequest(this);
        }

        // Collect data for the request object
        while (bytesAvailable()
                && m_pRequest->getStatus() != CLHttpRequest::ER_Complete
                && m_pRequest->getStatus() != CLHttpRequest::ER_Abort)
        {
            m_pRequest->read();

            if (m_pRequest->getStatus() == CLHttpRequest::ER_WaitForBody)
            {
                // Restart timer for read timeout, otherwise it would
                // expire during large file uploads.
                readTimer.start(readTimeout);
            }
        }

        if (m_pRequest->getStatus() == CLHttpRequest::ER_Abort)
        {
            write("HTTP/1.1 413 entity too large\r\nConnection: close\r\n\r\n413 Entity too large\r\n");

            while(bytesToWrite())
            {
                waitForBytesWritten();
            }

            disconnectFromHost();
            delete m_pRequest;
            m_pRequest = 0;
            return;
        }

        // 分发器
        // If the request is complete, let the request mapper dispatch it
        if (m_pRequest->getStatus() == CLHttpRequest::ER_Complete)
        {
            readTimer.stop();
            qDebug("HttpConnectionHandler (%p): received request", this);
            // Copy the Connection:close header to the response
            CLHttpResponse response(this);
//Connection: keep-alive , 开启HTTP持久连接，HTTP 1.1默认值
//Connection: close , 关闭HTTP持久连接，HTTP 1.0默认值
            bool bCloseConnection = QString::compare(m_pRequest->getHeader("Connection"), "close", Qt::CaseInsensitive) == 0;

            if (bCloseConnection)
            {
                response.setHeader("Connection", "close");
            }
            else
            {
                // In case of HTTP 1.0 protocol add the Connection:close header.
                // This ensures that the HttpResponse does not activate chunked mode, which is not spported by HTTP 1.0.
                bool http1_0 = QString::compare(m_pRequest->getVersion(), "HTTP/1.0", Qt::CaseInsensitive) == 0;

                if (http1_0)
                {
                    bCloseConnection = true;
                    response.setHeader("Connection", "close");
                }
            }

            // Call the request mapper
            try
            {
                IResponder* pResponder = CLResponderFactory::createResponder(m_pRequest, &response);
                pResponder->handle();
            }
            catch (...)
            {
                qCritical("HttpConnectionHandler (%p): An uncatched exception occured in the request handler", this);
            }

            // Finalize sending the response if not already done
            if (!response.hasSentLastPart())
            {
                response.write(QByteArray(), true);
            }

            qDebug("HttpConnectionHandler (%p): finished request", this);

            // Find out whether the connection must be closed
            if (!bCloseConnection)
            {
                // Maybe the request handler or mapper added a Connection:close header in the meantime
                bool closeResponse = QString::compare(response.getHeaders().value("Connection"), "close", Qt::CaseInsensitive) == 0;

                if (closeResponse == true)
                {
                    bCloseConnection = true;
                }
                else
                {
                    // If we have no Content-Length header and did not use chunked mode, then we have to close the
                    // connection to tell the HTTP client that the end of the response has been reached.
                    bool hasContentLength = response.getHeaders().contains("Content-Length");

                    if (!hasContentLength)
                    {
                        bool hasChunkedMode = QString::compare(response.getHeaders().value("Transfer-Encoding"), "chunked", Qt::CaseInsensitive) == 0;

                        if (!hasChunkedMode)
                        {
                            bCloseConnection = true;
                        }
                    }
                }
            }

            // Close the connection or prepare for the next request on the same connection.
            if (bCloseConnection)
            {
                while(bytesToWrite())
                {
                    waitForBytesWritten();
                }

                disconnectFromHost();
            }
            else
            {
                // Start timer for next request
                readTimer.start(readTimeout);
            }

            delete m_pRequest;
            m_pRequest = 0;

        }
    }
}



void CLHttpConnection::end()
{
//    if(m_pResponse)
//    {
//        m_pResponse = 0;
//    }

    disconnect(this);
    flush();
    disconnectFromHost();
    close();
    deleteLater();
}

void CLHttpConnection::setSocketSendBufferSize(int size)
{
//#ifdef Q_OS_WIN
//    setsockopt(socketDescriptor(), SOL_SOCKET, SO_SNDBUF, (const char*)&size, sizeof(int));
//#else
//    setsockopt(socketDescriptor(), SOL_SOCKET, SO_SNDBUF, (const void*)&size, sizeof(int));
//#endif
}

int CLHttpConnection::getSocketSendBufferSize()
{
    int size = 0;
    int len = sizeof(int);
//#ifdef Q_OS_WIN
//    getsockopt(socketDescriptor(), SOL_SOCKET, SO_SNDBUF, (char*)&size, (int*)&len);
//#else
//    getsockopt(socketDescriptor(), SOL_SOCKET, SO_SNDBUF, (void*)&size, (socklen_t*)&len);
//#endif
    return size;
}

void CLHttpConnection::loadConfig(QSettings *settings)
{
    readTimeout = settings->value("readTimeout", 10000).toInt();
}

void CLHttpConnection::onError(QAbstractSocket::SocketError errorCode)
{
//    if(!m_pResponse)
//    {
//        disconnect(this);
//        close();
//        deleteLater();
//    }
}

void CLHttpConnection::slot_disconnected()
{

}
