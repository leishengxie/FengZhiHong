#include "LDumpResponder.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"


CLDumpResponder::CLDumpResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{

}

int CLDumpResponder::handle()
{
    m_resp->setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    m_resp->setCookie(HttpCookie("firstCookie", "hello", 600, QByteArray(), QByteArray(), QByteArray(), false, true));
    m_resp->setCookie(HttpCookie("secondCookie", "world", 600));
    QByteArray body("<html><body>");
    body.append("<b>Request:</b>");
    body.append("<br>Method: ");
    body.append(m_req->getMethod());
    body.append("<br>Path: ");
    body.append(m_req->getPath());
    body.append("<br>Version: ");
    body.append(m_req->getVersion());
    body.append("<p><b>Headers:</b>");
    QMapIterator<QByteArray, QByteArray> iter(m_req->getHeaderMap());

    while (iter.hasNext())
    {
        iter.next();
        body.append("<br>");
        body.append(iter.key());
        body.append("=");
        body.append(iter.value());
    }

    body.append("<p><b>Parameters:</b>");
    iter = QMapIterator<QByteArray, QByteArray>(m_req->getParameterMap());

    while (iter.hasNext())
    {
        iter.next();
        body.append("<br>");
        body.append(iter.key());
        body.append("=");
        body.append(iter.value());
    }

    body.append("<p><b>Cookies:</b>");
    iter = QMapIterator<QByteArray, QByteArray>(m_req->getCookieMap());

    while (iter.hasNext())
    {
        iter.next();
        body.append("<br>");
        body.append(iter.key());
        body.append("=");
        body.append(iter.value());
    }

    body.append("<p><b>Body:</b><br>");
    body.append(m_req->getBody());
    body.append("</body></html>");
    m_resp->write(body, true);

    return 1;
}
