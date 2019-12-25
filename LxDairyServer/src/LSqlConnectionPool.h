#ifndef CSQLCONNECTIONPOOL_H
#define CSQLCONNECTIONPOOL_H
#include <QtSql>
#include <QQueue>
#include <QString>
#include <QMutex>
#include <QMutexLocker>
#include<QDebug>


///
/// \brief The CSqlConnectionPool class 单例-懒汉式 加入了线程安全
///
class CSqlConnectionPool
{
public:
    static CSqlConnectionPool* getInstance();

public:
    void release();                                  // 关闭所有的数据库连接
    QSqlDatabase getOpenConnection();                   // 获取数据库连接
    void closeConnection(QSqlDatabase connection);   // 释放数据库连接回连接池
    ~CSqlConnectionPool();

private:
    CSqlConnectionPool();
    void loadSetting();
//    CSqlConnectionPool(const CSqlConnectionPool & other);
//    CSqlConnectionPool & operator=(const CSqlConnectionPool & other);
    QSqlDatabase createConnection(const QString & connectionName); // 创建数据库连接

    QQueue<QString> m_queueUsedConnectionNames;   // 已使用的数据库连接名
    QQueue<QString> m_queueUnusedConnectionNames; // 未使用的数据库连接名



    bool testOnBorrow;    // 取得连接的时候验证连接是否有效
    QString testOnBorrowSql; // 测试访问数据库的 SQL

    int m_nMaxWaitTime;  // 获取连接最大等待时间
    int m_nWaitInterval; // 尝试获取连接时等待间隔时间
    int m_nMaxConnectionCount; // 最大连接数

    static QMutex s_mutex;
    static QWaitCondition s_waitConnection;
    static CSqlConnectionPool* s_sqlConnectionPool;

private:
    // 数据库信息
    QString strHostName;
    QString strDbName;
    QString strUserName;
    QString strPasswd;
    QString strDatabaseType;
};




#endif // CSQLCONNECTIONPOOL_H
