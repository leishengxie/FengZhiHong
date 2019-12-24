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

        m_resp->write("hello", true);
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
        T_UserInfo tUserInfo;
        CLSqlOperate::getInstance()->login(strUserName, strPasswd, tUserInfo, tHttpStatusMsg);

        m_resp->setStatus(tHttpStatusMsg.nStatusCode, tHttpStatusMsg.strMsg.toUtf8());

        // 返回用户信息
        m_resp->write(CNetAppointments::serializa(tUserInfo), true);

        //能用QString就尽量不要用QByteArray
    }



    return 1;
}
