#include "LJokeResponder.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"

#include "NetAppointments.h"


CLJokeResponder::CLJokeResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{

}

// http://127.0.0.1:8080/joke
int CLJokeResponder::handle()
{
    QByteArray path = m_req->getPath();
    qDebug("RequestMapper: path=%s", path.data());
    if (path.startsWith("/joke/upload"))
    {
        T_Joke tJoke = CNetAppointments::deserialization(m_req->getBody());

    }

    m_resp->setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    m_resp->setCookie(HttpCookie("firstCookie", "hello", 600, QByteArray(), QByteArray(), QByteArray(), false, true));
    m_resp->setCookie(HttpCookie("secondCookie", "world", 600));
    QByteArray resp_body();
    m_resp->write(resp_body, true);

    return 1;
}
