#ifndef _L_HTTP_CONNECTION
#define _L_HTTP_CONNECTION

#include <QObject>
#include <QHash>
#include <QTcpSocket>
#include <QTimer>

class CLHttpRequest;
class CLHttpResponse;
class IResponder;
class QSettings;

///
/// \brief http连接类，包含请求和处理,连接解析请求成功则生成一个反应器处理该请求
///
class CLHttpConnection : public QTcpSocket
{
    Q_OBJECT

public:
    CLHttpConnection(QObject *parent = 0);
    virtual ~CLHttpConnection();

    void end();
    void setSocketSendBufferSize(int size);
    int getSocketSendBufferSize();

    void loadConfig(QSettings *settings);

signals:
    void newRequest(CLHttpRequest*, CLHttpResponse*);

private slots:
    void parseRequest();
    void onError(QAbstractSocket::SocketError socketError);
    void slot_disconnected();

private:
    // since there can only be one request at any time
    // even with pipelining
    CLHttpRequest *m_pRequest;
    //CLHttpResponse *m_pResponse;

    IResponder* m_pResponder;

    /** Time for read timeout detection */
    QTimer readTimer;
    int readTimeout;

};

#endif //_L_HTTP_CONNECTION
