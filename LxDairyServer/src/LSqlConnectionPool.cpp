#include "LSqlConnectionPool.h"
#include <QSettings>

QMutex CSqlConnectionPool::s_mutex;
QWaitCondition CSqlConnectionPool::s_waitConnection;
CSqlConnectionPool* CSqlConnectionPool::s_sqlConnectionPool = NULL;

// 常量定义
static const char* const DATABASE_TYPE_MYSQL = "QMYSQL";
static const char* const DATABASE_TYPE_SQLITE = "QSQLITE";

static const char* const HOST_NAME = "localhost";
static const char* const DATABASE_NAME = "lxdairy";
static const char* const USER_NAME = "root";
static const char* const PASSWD = "0406";
static const int PORT = 3306;

CSqlConnectionPool::CSqlConnectionPool()
{


    testOnBorrow = true;
    testOnBorrowSql = "SELECT 1";

    m_nMaxWaitTime  = 1000;
    m_nWaitInterval = 200;
    m_nMaxConnectionCount  = 1000;

    loadSetting();
}

CSqlConnectionPool::~CSqlConnectionPool()
{
    // 销毁连接池的时候删除所有的连接
    foreach(QString connectionName, m_queueUsedConnectionNames)
    {
        QSqlDatabase::removeDatabase(connectionName);
    }

    foreach(QString connectionName, m_queueUnusedConnectionNames)
    {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

void CSqlConnectionPool::loadSetting()
{
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("sql_connection");
    strHostName = conf.value("host_name", HOST_NAME).toString();
    strDbName = conf.value("database_name", DATABASE_NAME).toString();
    strUserName = conf.value("user_name", USER_NAME).toString();
    strPasswd = conf.value("passwd", PASSWD).toString();
    strDatabaseType = conf.value("database_type", DATABASE_TYPE_MYSQL).toString();
}

CSqlConnectionPool* CSqlConnectionPool::getInstance()
{
    if (NULL == s_sqlConnectionPool)
    {
        QMutexLocker locker(&s_mutex);
        s_sqlConnectionPool = new CSqlConnectionPool();
    }

    return s_sqlConnectionPool;
}

void CSqlConnectionPool::release()
{
    QMutexLocker locker(&s_mutex);
    if (NULL != s_sqlConnectionPool)
    {
        delete s_sqlConnectionPool;
        s_sqlConnectionPool = NULL;
    }
}

QSqlDatabase CSqlConnectionPool::getOpenConnection()
{

    QString connectionName;

    QMutexLocker locker(&s_mutex);

    // 已创建连接数
    int connectionCount = m_queueUnusedConnectionNames.size() + m_queueUsedConnectionNames.size();

    // 如果连接已经用完，等待 waitInterval 毫秒看看是否有可用连接，最长等待 maxWaitTime 毫秒
    for (int i = 0; i < m_nMaxWaitTime && m_queueUnusedConnectionNames.size() == 0 && connectionCount == m_nMaxConnectionCount; i += m_nWaitInterval)
    {
        s_waitConnection.wait(&s_mutex, m_nWaitInterval);

        // 重新计算已创建连接数
        connectionCount = m_queueUnusedConnectionNames.size() + m_queueUsedConnectionNames.size();
    }

    if (m_queueUnusedConnectionNames.size() > 0)
    {
        // 有已经回收的连接，复用它们
        connectionName = m_queueUnusedConnectionNames.dequeue();
    }
    else if (connectionCount < m_nMaxConnectionCount)
    {
        // 没有已经回收的连接，但是没有达到最大连接数，则创建新的连接
        connectionName = QString("Connection-%1").arg(connectionCount + 1);
    }
    else
    {
        // 已经达到最大连接数
        qDebug() << "Cannot create more connections.";
        return QSqlDatabase();
    }

    // 创建连接
    QSqlDatabase db = createConnection(connectionName);

    // 有效的连接才放入 usedConnectionNames
    if (db.isOpen())
    {
        m_queueUsedConnectionNames.enqueue(connectionName);
    }

    return db;
}

void CSqlConnectionPool::closeConnection(QSqlDatabase connection)
{
    QString connectionName = connection.connectionName();

    // 如果是我们创建的连接，从 used 里删除，放入 unused 里
    if (m_queueUsedConnectionNames.contains(connectionName))
    {
        QMutexLocker locker(&s_mutex);
        m_queueUsedConnectionNames.removeOne(connectionName);
        m_queueUnusedConnectionNames.enqueue(connectionName);
        s_waitConnection.wakeOne();
    }
}

QSqlDatabase CSqlConnectionPool::createConnection(const QString & connectionName)
{
    // 连接已经创建过了，复用它，而不是重新创建
    if (QSqlDatabase::contains(connectionName))
    {
        QSqlDatabase db1 = QSqlDatabase::database(connectionName);

        if (testOnBorrow)
        {
            // 返回连接前访问数据库，如果连接断开，重新建立连接
            qDebug() << "Test connection on borrow, execute:" << testOnBorrowSql << ", for" << connectionName;
            QSqlQuery query(testOnBorrowSql, db1);

            if (query.lastError().type() != QSqlError::NoError && !db1.open())
            {
                qDebug() << "Open datatabase error:" << db1.lastError().text();
                return QSqlDatabase();
            }
        }

        return db1;
    }

    // 创建一个新的连接
    QSqlDatabase db = QSqlDatabase::addDatabase(strDatabaseType, connectionName);
    db.setHostName(strHostName);
    db.setDatabaseName(strDbName);
    db.setUserName(strUserName);
    db.setPassword(strPasswd);
    //db.setPort(3306);

    if (!db.open())
    {
        qDebug() << "Open datatabase error:" << db.lastError().text();
        return QSqlDatabase();
    }

    return db;
}

