#include "LDefaultResponder.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"


CLDefaultResponder::CLDefaultResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{


}

CLDefaultResponder::~CLDefaultResponder()
{

}

int CLDefaultResponder::handle()
{
    m_resp->setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    if (m_req->getParameter("action")=="show")
    {
        m_resp->write("<html><body>");
        m_resp->write("Name = ");
        m_resp->write(m_req->getParameter("name"));
        m_resp->write("<br>City = ");
        m_resp->write(m_req->getParameter("city"));
        m_resp->write("</body></html>",true);
    }
    else
    {
        m_resp->write("<html><body>");
        m_resp->write("<form method=\"post\">");
        m_resp->write("  <input type=\"hidden\" name=\"action\" value=\"show\">");
        m_resp->write("  Name: <input type=\"text\" name=\"name\"><br>");
        m_resp->write("  City: <input type=\"text\" name=\"city\"><br>");
        m_resp->write("  <input type=\"submit\">");
        m_resp->write("</form>");
        m_resp->write("</body></html>",true);
    }
    return 1;
}



int CLDefaultResponder::prepare()
{

//    const QString & method = m_req->method();

//    if(method != "HEAD" && method != "GET")
//    {
//        m_resp->writeHead(403);
//        return 0;
//    }
//    QString uriPath = m_req->path();
//    if(isForbidden(uriPath))
//    {
//        m_resp->writeHead(403);
//        return 0;
//    }

//    QString localPath = uri2path(uriPath);

//    aInfo() << "uriPath - " << uriPath << " localPath - " << localPath << endl;

//    if(uriPath == "/")
//    {
//        localPath = "index.htm";
//    }

//    QFileInfo fileInfo(localPath);

//    if(!fileInfo.exists())
//    {
//        m_resp->writeHead(404);
//        return 0;
//    }

//    if(!fileInfo.isFile() )
//    {
//        m_resp->writeHead(403);
//        return 0;
//    }

//    m_file = new QFile(localPath);
//    if(!m_file->open(QFile::ReadOnly))
//    {
//        m_resp->writeHead(500);
//        return 0;
//    }

//    int statusCode = 200;

//    // range解析 eg:  Range: bytes=2001-4932
//    qint64 r1 = 0;
//    qint64 r2 = 0;
//    QString strRequestRange = m_req->header("range");
//    QString strContentRange;
//    int rangeCount = 0;
//    if(!strRequestRange.isEmpty())
//    {
//        //qDebug("header range - %s", strRequestRange.toAscii().data());
//        strRequestRange.remove("bytes=");

//        statusCode = 206;

//        QStringList ranges = strRequestRange.split('-', QString::SkipEmptyParts);

//        //aDebug() << "ranges - " << ranges << endl;

//        rangeCount = ranges.size();
//        if(rangeCount >= 1)
//        {
//            r1 = ranges.at(0).toLongLong();
//        }
//        if(rangeCount >= 2)
//        {
//            r2 = ranges.at(1).toLongLong();
//        }
//    }

//    qint64 contentLength = (rangeCount == 2 ? r2 - r1 + 1: fileInfo.size() - r1 );
//    if(rangeCount > 0)
//    {
//        strContentRange = QString("bytes %1-%2/%3").arg(r1).arg(r1 + contentLength - 1).arg(fileInfo.size());
//        aDebug() << "Responder[common], " << strContentRange
//                 << " r1 - " << r1
//                 << " r2 - " << r2
//                 << " cl - " << contentLength << endl;
//    }

//    if(r1 != 0 && !m_file->seek(r1))
//    {
//        m_resp->writeHead(500);
//        return 0;
//    }

//    //TODO: add DATE, Last-Modified ... print header
//    m_resp->setHeader("Content-Type", _get_content_type(localPath.toLatin1().data()));
//    m_resp->setHeader("Content-Length", QString::number(contentLength));
//    m_resp->setHeader("Accept-Ranges", "bytes");
//    if(rangeCount > 0)
//    {
//        m_resp->setHeader("Content-Range", strContentRange);
//    }
//    m_resp->writeHead(statusCode);

//    if(method == "HEAD")
//    {
//        return 0;
//    }

//    m_bytesClientRequest = contentLength;

    return 1;

}




