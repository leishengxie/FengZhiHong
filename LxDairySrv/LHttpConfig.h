#ifndef _L_HTTP_CONFIG_H
#define _L_HTTP_CONFIG_H
#include <QHostAddress>
#include <QMap>
#include <QString>


class QSettings;
class QFileSystemWatcher;


// calloc 在动态分配完内存后，自动初始化该内存空间为零，而malloc不初始化，里边数据是随机的垃圾数据
// realloc 重新分配内存大小， 新的大小一定要大于原来的大小不然的话会导致数据丢失！, 主要实现数组内存增加


///
/// \brief 配置解析器, 存在于主线程内存空间
///
class CLHttpServerConfig : public QObject
{
    Q_OBJECT
private:
    CLHttpServerConfig(QObject *parent=Q_NULLPTR);
public:
    ~CLHttpServerConfig();

    static CLHttpServerConfig & instance();
    bool loadConfig(const char * config);

    QHostAddress m_address;                     // 服务ip地址
    quint16 m_qu16Port;                         // 端口号
    quint16 m_qu16MaxThreads;                   // 最大工作线程
    int m_nMaxConnections;                      // 每个线程工作者的最大连接数
    QString m_strDocumentRoot;                  // 文档根目录
    QStringList m_strlstForbiddenPatter;        //< foridden access path in URI
    QMap<QString, QString> m_mapAlias;          //

protected slots:
    void onConfigFileChanged(const QString &path);

private:
    void parseConfig(const QString &config, bool bPostEvent = false);
    void parseForbiddenPatters(const QString &fileName);


private:
    QFileSystemWatcher *m_fileWatcher;
};

#endif // _L_HTTP_CONFIG_H
