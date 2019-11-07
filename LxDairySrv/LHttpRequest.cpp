
#include "LHttpRequest.h"
#include "LHttpConnection.h"
#include "LHttpCookie.h"
#include <assert.h>
#include <QHostAddress>

#define CR                      '\r'
#define LF                      '\n'
#define CRLF                    "\r\n"
#define CRLFCRLF                "\r\n\r\n"


CLHttpRequest::CLHttpRequest(CLHttpConnection* connection, QObject* parent)
    : QObject(parent)
    , m_pHttpConnection(connection)
    , m_strUri("http://localhost/")
    , m_eRequestStatus(ER_WaitForRequest)
{
    m_strRemoteAddress = m_pHttpConnection->peerAddress().toString();
    m_strRemotePort = m_pHttpConnection->peerPort();
    currentSize = 0;
    expectedBodySize = 0;
    maxSize = 16000;
    maxMultiPartSize = 1000000;
    tempFile = NULL;
}

CLHttpRequest::~CLHttpRequest()
{
    foreach(QByteArray key, uploadedFiles.keys())
    {
        QTemporaryFile* file = uploadedFiles.value(key);

        if (file->isOpen())
        {
            file->close();
        }

        delete file;
    }
}

///
/// \brief 解析会话请求,为了减少分析错误，采用顺序读取分析
/// \param buffer
///
void CLHttpRequest::read()
{
    Q_ASSERT(m_eRequestStatus != ER_Complete);

    if (m_eRequestStatus == ER_WaitForRequest)
    {
        readRequestLine();
    }
    else if (m_eRequestStatus == ER_WaitForHeader)
    {
        readHeader();
    }
    else if (m_eRequestStatus == ER_WaitForBody)
    {
        readBody();
    }

    if ((boundary.isEmpty() && currentSize > maxSize) || (!boundary.isEmpty() && currentSize > maxMultiPartSize))
    {
        qWarning("HttpRequest: received too many bytes");
        m_eRequestStatus = ER_Abort;
    }

    if (m_eRequestStatus == ER_Complete)
    {
        // Extract and decode request parameters from url and body
        decodeRequestParams();
        // Extract cookies from headers
        extractCookies();
    }
}

///
/// \brief 读取请求行
///
void CLHttpRequest::readRequestLine()
{
    QByteArray lineBuffer;
    int toRead = maxSize - currentSize + 1; // allow one byte more to be able to detect overflow 检查溢出
    lineBuffer.append(m_pHttpConnection->readLine(toRead)); // 读取字节
    currentSize += lineBuffer.size();

    if (!lineBuffer.contains('\r') && !lineBuffer.contains('\n'))
    {
        return;
    }

    QByteArray newData = lineBuffer.trimmed(); // 去除两端空格

    if (!newData.isEmpty())
    {
        QList<QByteArray> list = newData.split(' ');

        if (list.count() != 3 || !list.at(2).contains("HTTP"))
        {
            qWarning("HttpRequest: received broken HTTP request, invalid first line");
            m_eRequestStatus = ER_Abort;
        }
        else
        {
            m_strMethod = list.at(0).trimmed();
            m_strUri = list.at(1);
            m_strVersion = list.at(2);
            //peerAddress = socket->peerAddress();
            m_eRequestStatus = ER_WaitForHeader;
        }
    }
}

void CLHttpRequest::readHeader()
{
    int toRead = maxSize - currentSize + 1;
    QByteArray lineBuffer;
    lineBuffer.append(m_pHttpConnection->readLine(toRead));
    currentSize += lineBuffer.size();

    if (!lineBuffer.contains('\r') && !lineBuffer.contains('\n'))
    {
        qDebug("HttpRequest: collecting more parts until line break");
        return;
    }

    QByteArray newData = lineBuffer.trimmed();
    int posColon = newData.indexOf(':');

    if (posColon > 0)
    {
        currentHeader = newData.left(posColon).toLower();
        QByteArray value = newData.mid(posColon + 1).trimmed();
        m_mapHeaders.insert(currentHeader, value);
        qDebug("HttpRequest: received header %s: %s", currentHeader.data(), value.data());
    }
    else if (!newData.isEmpty())
    {
        // received another line - belongs to the previous header
        qDebug("HttpRequest: read additional line of header");

        // Received additional line of previous header
        if (m_mapHeaders.contains(currentHeader))
        {
            m_mapHeaders.insert(currentHeader, m_mapHeaders.value(currentHeader) + " " + newData);
        }
    }
    else
    {
        // received an empty line - end of headers reached
        qDebug("HttpRequest: headers completed");
        // Empty line received, that means all headers have been received
        // Check for multipart/form-data
        QByteArray contentType = m_mapHeaders.value("content-type");

        if (contentType.startsWith("multipart/form-data"))
        {
            int posi = contentType.indexOf("boundary=");

            if (posi >= 0 )
            {
                boundary = contentType.mid(posi + 9);

                if  (boundary.startsWith('"') && boundary.endsWith('"'))
                {
                    boundary = boundary.mid(1, boundary.length() - 2);
                }
            }
        }

        QByteArray contentLength = m_mapHeaders.value("content-length");

        if (!contentLength.isEmpty())
        {
            expectedBodySize = contentLength.toInt();
        }

        if (expectedBodySize == 0)
        {
            qDebug("HttpRequest: expect no body");
            m_eRequestStatus = ER_Complete;
        }
        else if (boundary.isEmpty() && expectedBodySize + currentSize > maxSize)
        {
            qWarning("HttpRequest: expected body is too large");
            m_eRequestStatus = ER_Abort;
        }
        else if (!boundary.isEmpty() && expectedBodySize > maxMultiPartSize)
        {
            qWarning("HttpRequest: expected multipart body is too large");
            m_eRequestStatus = ER_Abort;
        }
        else
        {
            qDebug("HttpRequest: expect %i bytes body", expectedBodySize);
            m_eRequestStatus = ER_WaitForBody;
        }
    }
}

void CLHttpRequest::readBody()
{
    Q_ASSERT(expectedBodySize != 0);

    if (boundary.isEmpty())
    {
        // normal body, no multipart
        qDebug("HttpRequest: receive body");
        int toRead = expectedBodySize - bodyData.size();
        QByteArray newData = m_pHttpConnection->read(toRead);
        currentSize += newData.size();
        bodyData.append(newData);

        if (bodyData.size() >= expectedBodySize)
        {
            m_eRequestStatus = ER_Complete;
        }
    }
    else
    {
        // multipart body, store into temp file
        qDebug("HttpRequest: receiving multipart body");

        // Create an object for the temporary file, if not already present
        if (tempFile == NULL)
        {
            tempFile = new QTemporaryFile;
        }

        if (!tempFile->isOpen())
        {
            tempFile->open();
        }

        // Transfer data in 64kb blocks
        int fileSize = tempFile->size();
        int toRead = expectedBodySize - fileSize;

        if (toRead > 65536)
        {
            toRead = 65536;
        }

        fileSize += tempFile->write(m_pHttpConnection->read(toRead));

        if (fileSize >= maxMultiPartSize)
        {
            qWarning("HttpRequest: received too many multipart bytes");
            m_eRequestStatus = ER_Abort;
        }
        else if (fileSize >= expectedBodySize)
        {
            qDebug("HttpRequest: received whole multipart body");
            tempFile->flush();

            if (tempFile->error())
            {
                qCritical("HttpRequest: Error writing temp file for multipart body");
            }

            parseMultiPartFile();
            tempFile->close();
            m_eRequestStatus = ER_Complete;
        }
    }
}

QByteArray CLHttpRequest::getPath() const
{
    return m_strPathInUri;
}

QByteArray CLHttpRequest::getMethod() const
{
    return m_strMethod;
}

QList<QByteArray> CLHttpRequest::getHeaders(const QByteArray & name) const
{
    return m_mapHeaders.values(name.toLower());
}

QByteArray CLHttpRequest::getHeader(const QByteArray & name) const
{
    return m_mapHeaders.value(name.toLower());
}

QByteArray CLHttpRequest::getVersion() const
{
    return m_strVersion;
}

void CLHttpRequest::parseMultiPartFile()
{
    qDebug("HttpRequest: parsing multipart temp file");
    tempFile->seek(0);
    bool finished = false;

    while (!tempFile->atEnd() && !finished && !tempFile->error())
    {
        qDebug("HttpRequest: reading multpart headers");
        QByteArray fieldName;
        QByteArray fileName;

        while (!tempFile->atEnd() && !finished && !tempFile->error())
        {
            QByteArray line = tempFile->readLine(65536).trimmed();

            if (line.startsWith("Content-Disposition:"))
            {
                if (line.contains("form-data"))
                {
                    int start = line.indexOf(" name=\"");
                    int end = line.indexOf("\"", start + 7);

                    if (start >= 0 && end >= start)
                    {
                        fieldName = line.mid(start + 7, end - start - 7);
                    }

                    start = line.indexOf(" filename=\"");
                    end = line.indexOf("\"", start + 11);

                    if (start >= 0 && end >= start)
                    {
                        fileName = line.mid(start + 11, end - start - 11);
                    }

                    qDebug("HttpRequest: multipart field=%s, filename=%s", fieldName.data(), fileName.data());
                }
                else
                {
                    qDebug("HttpRequest: ignoring unsupported content part %s", line.data());
                }
            }
            else if (line.isEmpty())
            {
                break;
            }
        }

        qDebug("HttpRequest: reading multpart data");
        QTemporaryFile* uploadedFile = 0;
        QByteArray fieldValue;

        while (!tempFile->atEnd() && !finished && !tempFile->error())
        {
            QByteArray line = tempFile->readLine(65536);

            if (line.startsWith("--" + boundary))
            {
                // Boundary found. Until now we have collected 2 bytes too much,
                // so remove them from the last result
                if (fileName.isEmpty() && !fieldName.isEmpty())
                {
                    // last field was a form field
                    fieldValue.remove(fieldValue.size() - 2, 2);
                    m_mapParameters.insert(fieldName, fieldValue);
                    qDebug("HttpRequest: set parameter %s=%s", fieldName.data(), fieldValue.data());
                }
                else if (!fileName.isEmpty() && !fieldName.isEmpty())
                {
                    // last field was a file
                    if (uploadedFile)
                    {
                        qDebug("HttpRequest: finishing writing to uploaded file");
                        uploadedFile->resize(uploadedFile->size() - 2);
                        uploadedFile->flush();
                        uploadedFile->seek(0);
                        m_mapParameters.insert(fieldName, fileName);
                        qDebug("HttpRequest: set parameter %s=%s", fieldName.data(), fileName.data());
                        uploadedFiles.insert(fieldName, uploadedFile);
                        qDebug("HttpRequest: uploaded file size is %i", (int) uploadedFile->size());
                    }
                    else
                    {
                        qWarning("HttpRequest: format error, unexpected end of file data");
                    }
                }

                if (line.contains(boundary + "--"))
                {
                    finished = true;
                }

                break;
            }
            else
            {
                if (fileName.isEmpty() && !fieldName.isEmpty())
                {
                    // this is a form field.
                    currentSize += line.size();
                    fieldValue.append(line);
                }
                else if (!fileName.isEmpty() && !fieldName.isEmpty())
                {
                    // this is a file
                    if (!uploadedFile)
                    {
                        uploadedFile = new QTemporaryFile();
                        uploadedFile->open();
                    }

                    uploadedFile->write(line);

                    if (uploadedFile->error())
                    {
                        qCritical("HttpRequest: error writing temp file, %s", qPrintable(uploadedFile->errorString()));
                    }
                }
            }
        }
    }

    if (tempFile->error())
    {
        qCritical("HttpRequest: cannot read temp file, %s", qPrintable(tempFile->errorString()));
    }

    qDebug("HttpRequest: finished parsing multipart temp file");
}


///
/// \brief Extract and decode request parameters from url and body
///
void CLHttpRequest::decodeRequestParams()
{
#ifdef SUPERVERBOSE
    qDebug("HttpRequest: extract and decode request parameters");
#endif
    // Get URL parameters
    QByteArray rawParameters;
    int questionMark = m_strUri.indexOf('?');

    if (questionMark >= 0)
    {
        rawParameters = m_strUri.mid(questionMark + 1);
        m_strPathInUri = m_strUri.left(questionMark);
    }
    else
    {
        m_strPathInUri = m_strUri;
    }

    // Get request body parameters
    QByteArray contentType = m_mapHeaders.value("content-type");

    if (!bodyData.isEmpty() && (contentType.isEmpty()
                                || contentType.startsWith("application/x-www-form-urlencoded")))
    {
        if (!rawParameters.isEmpty())
        {
            rawParameters.append('&');
            rawParameters.append(bodyData);
        }
        else
        {
            rawParameters = bodyData;
        }
    }

    // Split the parameters into pairs of value and name
    QList<QByteArray> list = rawParameters.split('&');

    foreach (QByteArray part, list)
    {
        int equalsChar = part.indexOf('=');

        if (equalsChar >= 0)
        {
            QByteArray name = part.left(equalsChar).trimmed();
            QByteArray value = part.mid(equalsChar + 1).trimmed();
            m_mapParameters.insert(urlDecode(name), urlDecode(value));
        }
        else if (!part.isEmpty())
        {
            // Name without value
            m_mapParameters.insert(urlDecode(part), "");
        }
    }
}

void CLHttpRequest::extractCookies()
{
    qDebug("HttpRequest: extract cookies");

    foreach(QByteArray cookieStr, m_mapHeaders.values("cookie"))
    {
        QList<QByteArray> list = HttpCookie::splitCSV(cookieStr);

        foreach(QByteArray part, list)
        {
            qDebug("HttpRequest: found cookie %s", part.data());
            // Split the part into name and value
            QByteArray name;
            QByteArray value;
            int posi = part.indexOf('=');

            if (posi)
            {
                name = part.left(posi).trimmed();
                value = part.mid(posi + 1).trimmed();
            }
            else
            {
                name = part.trimmed();
                value = "";
            }

            m_mapCookies.insert(name, value);
        }
    }

    m_mapHeaders.remove("cookie");
}


// url 解码
///
/// \brief 网页中的表单使用POST方法提交时，数据内容的类型是 application/x-www-form-urlencoded，这种类型会：
///1.字符"a"-"z"，"A"-"Z"，"0"-"9"，"."，"-"，"*"，和"_" 都不会被编码;
///2.将空格转换为加号 (+) ;
///3.将非文本内容转换成"%xy"的形式,xy是两位16进制的数值;
///4.在每个 name=value 对之间放置 & 符号。
/// \param source
/// \return
///
QByteArray CLHttpRequest::urlDecode(const QByteArray source)
{
    QByteArray buffer(source);
    // 把+还原成空格
    buffer.replace('+', ' ');
    // 非文本内容还原
    int nPosPercentChar = buffer.indexOf('%');

    while (nPosPercentChar >= 0)
    {
        bool ok;
        char byte = buffer.mid(nPosPercentChar + 1, 2).toInt(&ok, 16);

        if (ok)
        {
            // 不懂得话F1看例子
            buffer.replace(nPosPercentChar, 3, (char*)&byte, 1);
        }

        // 查找从位置nPosPercentChar + 1开始的'%'的位置
        nPosPercentChar = buffer.indexOf('%', nPosPercentChar + 1);
    }

    return buffer;
}

QByteArray CLHttpRequest::getParameter(const QByteArray & name) const
{
    return m_mapParameters.value(name);
}


// 标准c版本 urlDecode
unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
    unsigned char y;

    if (x >= 'A' && x <= 'Z')
    {
        y = x - 'A' + 10;
    }
    else if (x >= 'a' && x <= 'z')
    {
        y = x - 'a' + 10;
    }
    else if (x >= '0' && x <= '9')
    {
        y = x - '0';
    }
    else
    {
        assert(0);
    }

    return y;
}

std::string UrlEncode(const std::string & str)
{
    std::string strTemp = "";
    size_t length = str.length();

    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
                (str[i] == '-') ||
                (str[i] == '_') ||
                (str[i] == '.') ||
                (str[i] == '~'))
        {
            strTemp += str[i];
        }
        else if (str[i] == ' ')
        {
            strTemp += "+";
        }
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }

    return strTemp;
}

std::string UrlDecode(const std::string & str)
{
    std::string strTemp = "";
    size_t length = str.length();

    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+')
        {
            strTemp += ' ';
        }
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        }
        else
        {
            strTemp += str[i];
        }
    }

    return strTemp;
}
