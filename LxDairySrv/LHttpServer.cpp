#include "LHttpServer.h"
//#include "httpRequest.h"
//#include "httpResponse.h"
#include "LResponderFactory.h"
#include <QSettings>
#include <QFile>
#include <QStringList>
#include <malloc.h>
#include "utils/LLogger.h"
#include "LHttpWorker.h"
#include "LHttpConfig.h"
#include <QHash>
#include "utils/LAsyncLogger.h"
#include <QTcpSocket>
#include <QTime>

///
/// \brief HttpServer::HttpServer
/// \param parent
///
CLHttpServer::CLHttpServer(QObject* parent)
    : QTcpServer(parent)
    , m_nWorkerForNextTask(1)
{

    g_StatusCodes.insert(100, "Continue");
    g_StatusCodes.insert(101, "Switching Protocols");
    g_StatusCodes.insert(102, "Processing");                 // RFC 2518) obsoleted by RFC 4918
    g_StatusCodes.insert(200, "OK");
    g_StatusCodes.insert(201, "Created");
    g_StatusCodes.insert(202, "Accepted");
    g_StatusCodes.insert(203, "Non-Authoritative Information");
    g_StatusCodes.insert(204, "No Content");
    g_StatusCodes.insert(205, "Reset Content");
    g_StatusCodes.insert(206, "Partial Content");
    g_StatusCodes.insert(207, "Multi-Status");               // RFC 4918
    g_StatusCodes.insert(300, "Multiple Choices");
    g_StatusCodes.insert(301, "Moved Permanently");
    g_StatusCodes.insert(302, "Moved Temporarily");
    g_StatusCodes.insert(303, "See Other");
    g_StatusCodes.insert(304, "Not Modified");
    g_StatusCodes.insert(305, "Use Proxy");
    g_StatusCodes.insert(307, "Temporary Redirect");
    g_StatusCodes.insert(400, "Bad Request");
    g_StatusCodes.insert(401, "Unauthorized");
    g_StatusCodes.insert(402, "Payment Required");
    g_StatusCodes.insert(403, "Forbidden");
    g_StatusCodes.insert(404, "Not Found");
    g_StatusCodes.insert(405, "Method Not Allowed");
    g_StatusCodes.insert(406, "Not Acceptable");
    g_StatusCodes.insert(407, "Proxy Authentication Required");
    g_StatusCodes.insert(408, "Request Time-out");
    g_StatusCodes.insert(409, "Conflict");
    g_StatusCodes.insert(410, "Gone");
    g_StatusCodes.insert(411, "Length Required");
    g_StatusCodes.insert(412, "Precondition Failed");
    g_StatusCodes.insert(413, "Request Entity Too Large");
    g_StatusCodes.insert(414, "Request-URI Too Large");
    g_StatusCodes.insert(415, "Unsupported Media Type");
    g_StatusCodes.insert(416, "Requested Range Not Satisfiable");
    g_StatusCodes.insert(417, "Expectation Failed");
    g_StatusCodes.insert(418, "I\"m a teapot");              // RFC 2324
    g_StatusCodes.insert(422, "Unprocessable Entity");       // RFC 4918
    g_StatusCodes.insert(423, "Locked");                     // RFC 4918
    g_StatusCodes.insert(424, "Failed Dependency");          // RFC 4918
    g_StatusCodes.insert(425, "Unordered Collection");       // RFC 4918
    g_StatusCodes.insert(426, "Upgrade Required");           // RFC 2817
    g_StatusCodes.insert(500, "Internal Server Error");
    g_StatusCodes.insert(501, "Not Implemented");
    g_StatusCodes.insert(502, "Bad Gateway");
    g_StatusCodes.insert(503, "Service Unavailable");
    g_StatusCodes.insert(504, "Gateway Time-out");
    g_StatusCodes.insert(505, "HTTP Version not supported");
    g_StatusCodes.insert(506, "Variant Also Negotiates");    // RFC 2295
    g_StatusCodes.insert(507, "Insufficient Storage");       // RFC 4918
    g_StatusCodes.insert(509, "Bandwidth Limit Exceeded");
    g_StatusCodes.insert(510, "Not Extended");                // RFC 2774

    loadConfig();
    initThreadPool();
}

CLHttpServer::~CLHttpServer()
{
}

void CLHttpServer::loadConfig()
{
    CLHttpServerConfig & config = CLHttpServerConfig::instance();
    m_qu16MaxThreads = config.m_qu16MaxThreads;
    m_qu16Port = config.m_qu16Port;
    m_address = config.m_address;
}


void CLHttpServer::initThreadPool()
{
    CLWorkerThread* pWorkerThread;

    for(int i = 1; i <= m_qu16MaxThreads; i++)
    {
        pWorkerThread = new CLWorkerThread(i);
        m_hashWorkers.insert(i, pWorkerThread);
        pWorkerThread->start();
    }
}

void CLHttpServer::work()
{

    if( listen(m_address, m_qu16Port) )
    {
        aInfo() << "httpserver started on port " << serverPort() << endl;
    }
    else
    {
        aWarn() << "could not start httpserver: " << errorString() << endl;
    }
}



void CLHttpServer::incomingConnection(qintptr fd)
{
    aDebug() << "incomingConnection " << fd << endl;
    CLWorkerThread* pWorkerThread;
    int retryCount = 0;
    // 重试
retry:

    for(; m_nWorkerForNextTask <= m_qu16MaxThreads; ++m_nWorkerForNextTask)
    {
        pWorkerThread = m_hashWorkers.value(m_nWorkerForNextTask);

        if(!pWorkerThread->isFull())
        {
            // 工作线程处理连接
            pWorkerThread->postSocket(fd);
            break;
        }
    }

    if(m_nWorkerForNextTask > m_qu16MaxThreads)
    {
        m_nWorkerForNextTask = 1;

        if(++retryCount > 3)
        {
            aWarn() << "HttpServer, load too high, reject a connection" << endl;
            qDebug("HttpServer: Too many incoming connections");
            QTcpSocket* socket = new QTcpSocket(this);
            socket->setSocketDescriptor(fd);
            connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
            socket->write("HTTP/1.1 503 too many connections\r\nConnection: close\r\n\r\nToo many connections\r\n");
            socket->disconnectFromHost();
            return;
        }

        QThread::msleep(100);
        goto retry;
    }

    // 如果成功指定下一个Worker id
    if( ++m_nWorkerForNextTask > m_qu16MaxThreads )
    {
        m_nWorkerForNextTask = 1;
    }

    //m_statistics.oneConnectionAccepted();
}



