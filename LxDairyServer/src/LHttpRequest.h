
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <QObject>
#include <QHash>
#include <QMetaType>
#include <QTemporaryFile>
#include <QMultiMap>
#include <QUrl>

typedef QHash<QString, QString> HeaderHash;

class QTcpSocket;
class CLHttpConnection;


///
/// \brief http请求类
///
class CLHttpRequest : public QObject
{
    Q_OBJECT

public:
    CLHttpRequest(CLHttpConnection* connection, QObject* parent = 0);
    ~CLHttpRequest();

    enum E_RequestStatus
    {
        ER_WaitForRequest,
        ER_WaitForHeader,
        ER_WaitForBody,
        ER_Complete,
        ER_Abort
    };

    void read();
    void readRequestLine();
    void readHeader();
    void readBody();

    QByteArray getPath() const;

    E_RequestStatus getStatus() const
    {
        return m_eRequestStatus;
    }

    QByteArray getMethod() const;

    QMultiMap<QByteArray,QByteArray> getHeaderMap() const
    {
        return m_mapHeaders;
    }
    QList<QByteArray> getHeaders(const QByteArray& name) const;
    QByteArray getHeader(const QByteArray& name) const;

    /** Get the version of the HTPP request (e.g. "HTTP/1.1") */
    QByteArray getVersion() const;

    /**
      Decode an URL parameter.
      E.g. replace "%23" by '#' and replace '+' by ' '.
      @param source The url encoded strings
      @see QUrl::toPercentEncoding for the reverse direction
    */
    static QByteArray urlDecode(const QByteArray source);

    QMultiMap<QByteArray,QByteArray> getParameterMap() const
    {
        return m_mapParameters;
    }

    QMap<QByteArray,QByteArray>& getCookieMap()
    {
        return m_mapCookies;
    }

    QByteArray getBody() const
    {
        return bodyData;
    }

    QByteArray getParameter(const QByteArray& name) const;

signals:
    //正文数据
    void data(const QByteArray &);
    //http请求结束
    void end();

private:


    /** Parse the multipart body, that has been stored in the temp file. */
    void parseMultiPartFile();

    /** Sub-procedure of readFromSocket(), extract and decode request parameters. */
    void decodeRequestParams();

    /** Sub-procedure of readFromSocket(), extract cookies from headers */
    void extractCookies();


private:
    CLHttpConnection* m_pHttpConnection;
//URL
    //协议类型:[//[访问资源需要的凭证信息@]服务器地址[:端口号]][/资源层级UNIX文件路径]文件名[?查询][#片段ID]
//    （1）协议类型：HTTP、HTTPS、FTP、mailto等协议
//    （2）层级URL标记符号(为[//],固定不变)
//    （3）访问资源需要的凭证信息（可省略）
//    （4）服务器（域名或者IP地址）
//    （5）端口号
//    （6）路径（以“/”字符区别路径中的每一个目录名称）
//    （7）查询。（GET模式的窗体参数，以“?”字符为起点，每个参数以“&”隔开，再以“=”分开参数名称与数据，通常以UTF8的URL编码，避开字符冲突的问题）
//    （8）片段（以“#‘字符为起点）
//URI
    //

    /*请求行定义*/
    QByteArray m_strMethod;        //客户端请求的方法字段 eg GET
    QByteArray m_strUri;           //统一资源标识符uri 每个 URL 都是 URI，但不一定每个 URI 都是 URL, eg /
    QByteArray m_strPathInUri;          // uri的一部分
    QByteArray m_strQuery;         // 请求行?后的查询语句
    //QString m_strVersion;       //客户端http的版本 eg HTTP/1.1
    QByteArray m_strVersion;

    /*头域*/
    //HeaderHash m_mapHeaders;
    QMultiMap<QByteArray,QByteArray> m_mapHeaders;

    // uri里面?后面的参数，即请求行?后的查询语句
    QMultiMap<QByteArray, QByteArray> m_mapParameters;

    /** Received cookies */
    QMap<QByteArray, QByteArray> m_mapCookies;

    /** Uploaded files of the request, key is the field name. */
    QMap<QByteArray,QTemporaryFile*> uploadedFiles;

//#alias="/test,e:/temp;;/home,/usr/local"
//#alias="/test/,e:/temp"

    //QString m_strBady;
    /** Storage for raw body data */
    QByteArray bodyData;

    QString m_strRemoteAddress;
    quint16 m_strRemotePort;

    /** Name of the current header, or empty if no header is being processed */
    QByteArray currentHeader;

    /** Current size. 当前请求读到的字节数 */
    int m_nCurrentSize;

    /** Expected size of body 请求头里面content-length预期的消息实体的传输长度*/
    int m_nExpectedBodySize;

    /** Maximum size of requests in bytes. 允许读取请求的最大字节数，设置为16000字节 */
    int m_nMaxSizeToRead;

    /** Maximum allowed size of multipart forms in bytes. 允许最大的multipart/form-data字节数，设置为1000000字节*/
    int m_nMaxMultiPartSize;

    /** Boundary of multipart/form-data body. Empty if there is no such header */
    QByteArray m_bytesBoundary; //Boundary-分界

    /** Temp file, that is used to store the multipart/form-data body */
    QTemporaryFile* tempFile;

    E_RequestStatus m_eRequestStatus;



};

#endif
