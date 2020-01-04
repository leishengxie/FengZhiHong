#include "LDairyResponder.h"
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"

#include "NetAppointments.h"
#include "LSqlOperate.h"
#include <QtDebug>


CLDairyResponder::CLDairyResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{

}

int CLDairyResponder::handle()
{

    QByteArray path = m_req->getPath();
    qDebug("handle: path=%s", path.data());
    if (path.startsWith(VIRTUAL_DIR_PATH_DAIRY_LIST))
    {
        T_DairyListRequest tDairyListRequest = CNetAppointments::deserialization<T_DairyListRequest>(m_req->getBody());
        T_DairyListResp tDairyListResp;
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->getDairyList(tDairyListRequest, tDairyListResp, tHttpStatusMsg);
        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());
        m_resp->write(CNetAppointments::serializa(tDairyListResp), true);
    }
    else if (path.startsWith(VIRTUAL_DIR_PATH_DAIRY_UPLOAD))
    {
        T_Dairy dairy = CNetAppointments::deserialization<T_Dairy>(m_req->getBody());
        T_Dairy dairySaved;
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->saveDairy(dairy, dairySaved, tHttpStatusMsg);

        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());
        m_resp->write(CNetAppointments::serializa(dairySaved), true);
    }


    return 1;
}
