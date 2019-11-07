#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QPointer>
#include <QList>
#include "LResponderFactory.h"
#include <QTcpSocket>
#include "LHttpEvent.h"


///
/// \brief 工作者线程，提供工作者运行的环境
///
class CLWorkerThread : public QThread
{
public:
    CLWorkerThread(int workerId, QObject *parent = 0);
    ~CLWorkerThread();

    void postSocket(qintptr sock);

    int taskCount()
    {
        return m_nTaskCount;
    }

    int maxConnection()
    {
        return m_nMaxConnections;
    }

    bool isFull()
    {
        return m_nTaskCount >= m_nMaxConnections;
    }

protected:
    void run();
    bool event(QEvent *event);

private:
    void loadConfig();

private:
    int m_id;            // 工作id
    int m_nTaskCount;    // 任务数
    int m_nMaxConnections;               // 每个线程工作者的最大连接数

    QPointer<QObject> m_pWorker;
    QList<qintptr> m_sockets;
};

///
/// \brief 工作者，管理多个连接,处理http请求
///
class Worker : public QObject
{
    Q_OBJECT
    friend class CLWorkerThread;
public:
    Worker();
    ~Worker();

    // 事件的分发
    bool event(QEvent *e);

    // 自定义事件处理器（event handler）
    virtual bool socketAcceptEvent(TaskEvent *taskEvent);

protected slots:
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onDone();

private:
    void processQueuedConnections();
    void processConnection(qintptr fd);

private:
    QList<qintptr> m_sockets;

};

#endif // WORKER_H
