#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include <QTcpServer>
#include <QHostAddress>
#include <QString>
#include <QThread>

class CLWorkerThread;



//#define CONNECTION_COUNTERS  20
/////
///// \brief 连接统计类, 统计平均每一秒钟的连接数, 每20个数打印一次
/////
//class ConnectionStatistic
//{
//public:
//    ConnectionStatistic()
//        : m_nCursor(0)
//    {
//        m_time.start();
//        memset(m_aConnCounters, 0, sizeof(int)*CONNECTION_COUNTERS);
//    }

//    void oneConnectionAccepted()
//    {
//        // 时间经过了超过一秒
//        if(m_time.elapsed() >= 1000)
//        {
//            m_time.restart();
//            ++m_nCursor;
//            if(m_nCursor == CONNECTION_COUNTERS)
//            {
//                char buf[256]={0};
//                int ret = 0;
//                for(int i = 0; i < CONNECTION_COUNTERS; ++i)
//                {
//                    ret += sprintf(buf + ret, " %d", m_aConnCounters[i]);
//                    m_aConnCounters[i] = 0;
//                }
//                // 打印平均每秒的连接数
//                aInfo() << "connections: " << buf << endl;
//                m_nCursor = 0;
//            }
//        }

//        ++m_aConnCounters[m_nCursor];
//    }

//    QTime m_time; // 计时器

//    int m_aConnCounters[CONNECTION_COUNTERS];//recent seconds

//    int m_nCursor;
//};

///
/// \brief http服务，监听连接，创建工作线程，管理工作线程
///
class CLHttpServer : public QTcpServer
{
    Q_OBJECT
public:
    CLHttpServer(QObject * parent = 0);
    ~CLHttpServer();

    void initThreadPool();
    void work();


protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    //void close();
    void loadConfig();

private:

    QHash<int, CLWorkerThread*> m_hashWorkers;

    QHostAddress m_address;
    quint16 m_qu16Port;
    quint16 m_qu16MaxThreads;                  // 最大工作线程

    // 指定下一个处理接下来的任务的工作者工作号
    int m_nWorkerForNextTask;
    //ConnectionStatistic m_statistics;

    QHash<int, QString> g_StatusCodes;
};




///
/// \服务主线程模板,把http服务放入到服务主线程，避免堵塞ui主线程
///
template <class T>
class CLWorkerHostThread : public QThread
{
public:
    CLWorkerHostThread(QObject *parent = Q_NULLPTR)
        : QThread(parent)
    {

    }
    ~CLWorkerHostThread()
    {

    }

protected:
    void run()
    {
        T t;
        t.work();
        exec();
    }

};



#endif // HTTPSERVER_H
