#ifndef _I_RESPONDER_H_
#define _I_RESPONDER_H_
#include <QObject>
#include <QMap>

class CLHttpRequest;
class CLHttpResponse;

#define RESPONDER_BUFFER_SIZE 1024*16

///
/// \brief 响应器接口类
///
class IResponder : public QObject
{
    Q_OBJECT
public:
    IResponder(CLHttpRequest* req, CLHttpResponse* resp);

    virtual ~IResponder() {}

    virtual int handle() = 0;

    // 是否禁用該uri路径
    bool isForbidden(const QString & uriPath);


signals:
    void finished();


protected:
    QStringList m_strlstForbiddenPatter;     //< foridden access path in URI
    QMap<QString, QString> m_mapAlias;
    QString m_strDocumentRoot;
    CLHttpRequest* m_req;
    CLHttpResponse* m_resp;

private:

};







#endif // _I_RESPONDER_H_
