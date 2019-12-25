#include "LJokeResponder.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"

#include "NetAppointments.h"
#include "LSqlOperate.h"
#include <QtDebug>


CLJokeResponder::CLJokeResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{

}

// http://127.0.0.1:8080/joke
int CLJokeResponder::handle()
{

    QByteArray path = m_req->getPath();
    qDebug("handle: path=%s", path.data());
    if (path.startsWith(VIRTUAL_DIR_PATH_JOKE_LIST))
    {
        T_JokeListRequest tJokeListRequest = CNetAppointments::deserialization<T_JokeListRequest>(m_req->getBody());
        T_JokeListResp tJokeListResp;
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->getJokeList(tJokeListRequest, tJokeListResp, tHttpStatusMsg);
        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());
        m_resp->write(CNetAppointments::serializa(tJokeListResp), true);
    }
    else if (path.startsWith(VIRTUAL_DIR_PATH_JOKE_UPLOAD))
    {
        T_Joke tJoke = CNetAppointments::deserialization<T_Joke>(m_req->getBody());
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->saveUserUploadJoke(tJoke, tHttpStatusMsg);

        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());

        qDebug() << "strDate=" << tJoke.strDate;
        qDebug() << "strTitle=" << tJoke.strTitle;

        m_resp->write("<html><body>");
        m_resp->write("  diaryDate: <input type=\"text\" name=\"");
        m_resp->write(tJoke.strDate.toUtf8());
        m_resp->write("\"><br>");
        m_resp->write("  dairyTitle: <input type=\"text\" name=\"");
        m_resp->write(tJoke.strTitle.toUtf8());
        m_resp->write("\"><br>");
        m_resp->write("</body></html>",true);

//        QByteArray resp_body;
//        m_resp->write(resp_body, true);
    }



    return 1;
}
