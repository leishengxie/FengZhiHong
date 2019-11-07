#include "LHttpWorker.h"
#include <QCoreApplication>
#include <QTcpSocket>
#include "LHttpConnection.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpConfig.h"
#include "utils/LAsyncLogger.h"



Worker::Worker()
{

}

Worker::~Worker()
{
}


bool Worker::event(QEvent *e)
{
    QEvent::Type t = e->type();
    if(t == TaskEvent::evType())
    {
        TaskEvent * taskEvent = (TaskEvent*)e;
        return socketAcceptEvent(taskEvent);
    }
    return QObject::event(e);
}

bool Worker::socketAcceptEvent(TaskEvent* taskEvent)
{

    if(!taskEvent->m_socket)
    {
        processQueuedConnections();
    }
    else
    {
        processConnection(taskEvent->m_socket);
    }
    return true;
}



void Worker::onSocketError(QAbstractSocket::SocketError socketError)
{
    //delete HttpConnection
    QCoreApplication::postEvent(QThread::currentThread(), new TaskEvent(0));
}

///
/// \brief 向所属线程发送事件完毕
///
void Worker::onDone()
{
    QCoreApplication::postEvent(QThread::currentThread(), new TaskEvent(0));
}

void Worker::processQueuedConnections()
{
    int count = m_sockets.size();
    if(count > 0)
    {
        for(int i = 0; i < count; i++)
        {
            processConnection(m_sockets.at(i));
        }
        m_sockets.clear();
    }
}

///
/// \brief 产生新的连接处理消息
/// \param sock
///
void Worker::processConnection(qintptr sock)
{
    if(sock < 0)
    {
        return;
    }

    CLHttpConnection *conn = new CLHttpConnection(this);
    conn->setSocketDescriptor(sock);
//    connect(conn, SIGNAL(newRequest(CLHttpRequest*, CLHttpResponse*))
//            , this, SLOT(onNewRequest(CLHttpRequest*, CLHttpResponse*)));
    connect(conn, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}





///
/// \brief 工作者线程
/// \param id
/// \param parent
///
CLWorkerThread::CLWorkerThread(int id, QObject *parent)
    : QThread(parent)
    , m_id(id)
    , m_nTaskCount(0)
    , m_nMaxConnections(200)
{
    loadConfig();
}

CLWorkerThread::~CLWorkerThread()
{
}

// 此函数属于父线程，向子线程发送事件
void CLWorkerThread::postSocket(qintptr sock)
{
    m_nTaskCount++;
    aDebug() << "worker " << m_id << " postSocket task count " << m_nTaskCount << endl;
    if(m_pWorker)
    {
        QCoreApplication::postEvent(m_pWorker, new TaskEvent(sock));
    }
    else
    {
        m_sockets.append(sock);
    }
}

///
/// \brief 得到工作者发出的处理完成信号事件
/// \param e
/// \return
///
bool CLWorkerThread::event(QEvent *e)
{
    if(e->type() == TaskEvent::evType())
    {
        m_nTaskCount--;
        aDebug() << "worker " << m_id << " taskDone task count " << m_nTaskCount << endl;
        return true;
    }
    QThread::event(e);
}

void CLWorkerThread::loadConfig()
{
    CLHttpServerConfig & config = CLHttpServerConfig::instance();
    m_nMaxConnections = config.m_nMaxConnections;

}

void CLWorkerThread::run()
{
    // 在工作线程中创建工作者
    Worker *worker = new Worker();
    m_pWorker = worker;
    if(m_sockets.size() > 0)
    {
        worker->m_sockets = m_sockets;
        m_sockets.clear();
        QCoreApplication::postEvent(worker, new TaskEvent(0));
    }
    exec();
}
