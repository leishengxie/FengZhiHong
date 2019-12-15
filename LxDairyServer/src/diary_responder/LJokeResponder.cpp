#include "LJokeResponder.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"


CLJokeResponder::CLJokeResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{

}

// http://127.0.0.1:8080/joke
int CLJokeResponder::handle()
{
    m_resp->setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    m_resp->setCookie(HttpCookie("firstCookie", "hello", 600, QByteArray(), QByteArray(), QByteArray(), false, true));
    m_resp->setCookie(HttpCookie("secondCookie", "world", 600));

    m_req->getBody();

    QByteArray body();

    m_resp->write(body, true);

    return 1;
}
