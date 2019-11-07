#ifndef Q_HTTP_RESPONSE
#define Q_HTTP_RESPONSE

#include <QObject>
#include <QHash>
#include <QMap>
#include <QByteArray>
#include "LHttpCookie.h"

//
class QTcpSocket;
class CLHttpConnection;


///
/// \brief 响应类-数据发送
///
class CLHttpResponse : public QObject
{
    Q_OBJECT
public:
    CLHttpResponse(CLHttpConnection *connection);
    virtual ~CLHttpResponse();

    void setHeader(QByteArray field, QByteArray value);

    /** Get the map of HTTP response headers */
    QMap<QByteArray,QByteArray>& getHeaders();

    void writeHead(int status);


    bool writeToConnection(QByteArray bytesData);

    /**
      Write body data to the socket.
      <p>
      The HTTP status line, headers and cookies are sent automatically before the body.
      <p>
      If the response contains only a single chunk (indicated by lastPart=true),
      then a Content-Length header is automatically set.
      <p>
      Chunked mode is automatically selected if there is no Content-Length header
      and also no Connection:close header.
      @param data Data bytes of the body
      @param lastPart Indicates that this is the last chunk of data and flushes the output buffer.
    */
    void write(QByteArray data, bool lastPart=false);



    /** Get the map of cookies */
    QMap<QByteArray,HttpCookie>& getCookies();


    /**
      Set status code and description. The default is 200,OK.
      You must call this method before the first write().
    */
    void setStatus(int statusCode, QByteArray description=QByteArray());

    void setCookie(const HttpCookie& cookie);

    /**
      Send a redirect response to the browser.
      Cannot be combined with write().
      @param url Destination URL
    */
    void redirect(const QByteArray& url);


    bool hasSentLastPart() const;

private slots:
    void end(const QString &data);

signals:
    void done();


private:
    void writeHeaders();

private:
    CLHttpConnection *m_pConnection;

    //bool m_headerWritten;

    QMap<QByteArray,QByteArray> m_headers;

    QMap<QByteArray,HttpCookie> cookies;

    /** HTTP status code*/
    int statusCode;

    /** HTTP status code description */
    QByteArray statusText;

    /** Indicator whether headers have been sent */
    bool sentHeaders;

    /** Indicator whether the body has been sent completely */
    bool sentLastPart;

    /** Whether the response is sent in chunked mode */
    bool chunkedMode;

};

#endif
