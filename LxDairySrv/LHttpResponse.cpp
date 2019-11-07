#include "LHttpResponse.h"
#include "LHttpConnection.h"
#include <QHostAddress>
#include "utils/LAsyncLogger.h"


CLHttpResponse::CLHttpResponse(CLHttpConnection *connection)
    : QObject(0)
    , m_pConnection(connection)
{
    statusCode = 200;
    statusText = "OK";
    sentHeaders = false;
    sentLastPart = false;
    chunkedMode = false;
    //connect(m_pConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(end()));
}




CLHttpResponse::~CLHttpResponse()
{
}


void CLHttpResponse::setHeader(QByteArray field, QByteArray value)
{
    Q_ASSERT(sentHeaders==false);
    m_headers[field] = value;
}

QMap<QByteArray, QByteArray> &CLHttpResponse::getHeaders()
{
    return m_headers;
}




void CLHttpResponse::writeHeaders()
{
    Q_ASSERT(!sentHeaders);
    QByteArray buffer;
    buffer.append("HTTP/1.1 ");
    buffer.append(QByteArray::number(statusCode));
    buffer.append(' ');
    buffer.append(statusText);
    buffer.append("\r\n");

    foreach(QByteArray name, m_headers.keys())
    {
        buffer.append(name);
        buffer.append(": ");
        buffer.append(m_headers.value(name));
        buffer.append("\r\n");
    }

    foreach(HttpCookie cookie, cookies.values())
    {
        buffer.append("Set-Cookie: ");
        buffer.append(cookie.toByteArray());
        buffer.append("\r\n");
    }

    //WRITE_HEADER("Connection", "close");
    buffer.append("\r\n");
    writeToConnection(buffer);
    sentHeaders = true;
}

bool CLHttpResponse::writeToConnection(QByteArray bytesData)
{
    int nRemaining = bytesData.size(); // 剩余
    char* ptr = bytesData.data();

    while (m_pConnection->isOpen() && nRemaining > 0)
    {
        // If the output buffer has become large, then wait until it has been sent.
        if (m_pConnection->bytesToWrite() > 16384)
        {
            m_pConnection->waitForBytesWritten(-1);
        }

        int nWritten = m_pConnection->write(ptr, nRemaining);

        if (nWritten == -1)
        {
            return false;
        }

        ptr += nWritten;
        nRemaining -= nWritten;
    }

    return true;
}


void CLHttpResponse::write(QByteArray data, bool lastPart)
{
    Q_ASSERT(sentLastPart == false);

    // Send HTTP headers, if not already done (that happens only on the first call to write())
    if (sentHeaders == false)
    {
        // If the whole response is generated with a single call to write(), then we know the total
        // size of the response and therefore can set the Content-Length header automatically.
        if (lastPart)
        {
            // Automatically set the Content-Length header
            m_headers.insert("Content-Length", QByteArray::number(data.size()));
        }
        else
        {
            // else if we will not close the connection at the end, them we must use the chunked mode.
            QByteArray connectionValue = m_headers.value("Connection", m_headers.value("connection"));
            bool connectionClose = QString::compare(connectionValue, "close", Qt::CaseInsensitive) == 0;

            if (!connectionClose)
            {
                m_headers.insert("Transfer-Encoding", "chunked");
                chunkedMode = true;
            }
        }

        writeHeaders();
    }

    // Send data
    if (data.size() > 0)
    {
        if (chunkedMode)
        {
            if (data.size() > 0)
            {
                QByteArray size = QByteArray::number(data.size(), 16);
                writeToConnection(size);
                writeToConnection("\r\n");
                writeToConnection(data);
                writeToConnection("\r\n");
            }
        }
        else
        {
            writeToConnection(data);
        }
    }

    // Only for the last chunk, send the terminating marker and flush the buffer.
    if (lastPart)
    {
        if (chunkedMode)
        {
            writeToConnection("0\r\n\r\n");
        }

        m_pConnection->flush();
        sentLastPart = true;
    }
}



void CLHttpResponse::setCookie(const HttpCookie & cookie)
{
    Q_ASSERT(sentHeaders == false);

    if (!cookie.getName().isEmpty())
    {
        cookies.insert(cookie.getName(), cookie);
    }
}


QMap<QByteArray, HttpCookie> & CLHttpResponse::getCookies()
{
    return cookies;
}

void CLHttpResponse::setStatus(int statusCode, QByteArray description)
{
    this->statusCode=statusCode;
    statusText=description;
}


void CLHttpResponse::redirect(const QByteArray & url)
{
    setStatus(303, "See Other");
    setHeader("Location", url);
    write("Redirect", true);
}

bool CLHttpResponse::hasSentLastPart() const
{
    return sentLastPart;
}


void CLHttpResponse::end(const QString & data)
{
}


