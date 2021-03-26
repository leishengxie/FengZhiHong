#include "LArticleResponder.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"

#include "NetAppointments.h"
#include "LSqlOperate.h"
#include <QtDebug>


CLArticleResponder::CLArticleResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{

}

// http://127.0.0.1:8080/article
int CLArticleResponder::handle()
{

    QByteArray path = m_req->getPath();
    qDebug("handle: path=%s", path.data());
    if (path.startsWith(VIRTUAL_DIR_PATH_ARTICLE_LIST))
    {
        T_ArticleListRequest tArticleListRequest = CNetAppointments::deserialization<T_ArticleListRequest>(m_req->getBody());
        T_ArticleListResp tArticleListResp;
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->getArticleList(tArticleListRequest, tArticleListResp, tHttpStatusMsg);
        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());
        m_resp->write(CNetAppointments::serializa(tArticleListResp), true);
    }
    else if (path.startsWith(VIRTUAL_DIR_PATH_ARTICLE_UPLOAD))
    {
        T_Article tArticle = CNetAppointments::deserialization<T_Article>(m_req->getBody());
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->saveUserUploadArticle(tArticle, tHttpStatusMsg);

        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());

        qDebug() << "strDate=" << tArticle.strDate;
        qDebug() << "strTitle=" << tArticle.strTitle;

        m_resp->write("<html><body>");
        m_resp->write("  diaryDate: <input type=\"text\" name=\"");
        m_resp->write(tArticle.strDate.toUtf8());
        m_resp->write("\"><br>");
        m_resp->write("  dairyTitle: <input type=\"text\" name=\"");
        m_resp->write(tArticle.strTitle.toUtf8());
        m_resp->write("\"><br>");
        m_resp->write("</body></html>",true);

//        QByteArray resp_body;
//        m_resp->write(resp_body, true);
    }
    else if (path.startsWith(VIRTUAL_DIR_PATH_ARTICLE_RATING))
    {
        T_ArticleRating tArticleRating = CNetAppointments::deserialization<T_ArticleRating>(m_req->getBody());
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->articleRating(tArticleRating, tHttpStatusMsg);

        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());

        m_resp->write("ok", true);
    }


    return 1;
}
