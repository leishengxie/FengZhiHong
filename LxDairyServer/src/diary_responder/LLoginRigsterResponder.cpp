#include "LLoginRigsterResponder.h"

#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "LHttpCookie.h"

#include "NetAppointments.h"
#include "LSqlOperate.h"
#include <QtDebug>


CLLoginRigsterResponder::CLLoginRigsterResponder(CLHttpRequest *req, CLHttpResponse *resp)
    : IResponder(req, resp)
{

}


int CLLoginRigsterResponder::handle()
{

    QByteArray path = m_req->getPath();
    qDebug("handle: path=%s", path.data());
    if (path.startsWith(VIRTUAL_DIR_PATH_REGISTER))
    {
        QByteArray byteArrayTemp = m_req->getBody();
        QString strUserName;
        QString strPasswd;
        QDataStream in(&byteArrayTemp, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_6);
        in >> strUserName >> strPasswd;
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->registerAccount(strUserName, strPasswd, tHttpStatusMsg);

        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());

        QByteArray resp_body;
        m_resp->write(resp_body, true);
    }
    else if(path.startsWith(VIRTUAL_DIR_PATH_LOGIN))
    {
        QByteArray byteArrayTemp = m_req->getBody();
        QString strUserName;
        QString strPasswd;
        QDataStream in(&byteArrayTemp, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_6);
        in >> strUserName >> strPasswd;
        T_HttpStatusMsg tHttpStatusMsg;
        CLSqlOperate::getInstance()->login(strUserName, strPasswd, tHttpStatusMsg);

        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());

        // 返回用户信息
        QByteArray resp_body;
        m_resp->write(resp_body, true);
    }



    return 1;
}
