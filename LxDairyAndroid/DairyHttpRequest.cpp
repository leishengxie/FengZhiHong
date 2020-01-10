#include "DairyHttpRequest.h"

#include "DairyHttpClient.h"
#include "NetAppointments.h"
#include "DairyAndroidApp.h"
#include "ModelManager.h"
#include "DairyListModel.h"
#include "LToast.h"

#include <QMessageBox>

#include <QtDebug>

CDairyHttpRequest::CDairyHttpRequest(QObject *parent)
    : QObject(parent)
{

}


/// c++ call back qml
//class MyObject: public QObject
//{

//Q_OBJECT

//public:
//    Q_INVOKABLE void doSomething(int x, QJSValue jsCallback)
//    {
//        x += 1;
//        qDebug() << __FUNCTION__ << x; //参数x
//        QJSValue val = jsCallback.engine()->toScriptValue(x);
//        QJSValueList paramList;
//        paramList.append(val);
//        qDebug() << jsCallback.call(paramList).toBool();  //js fucntion的返回值
//    }
//};
//MyObject
//{
//    id:myobj
//}
//Button{
//        text:qsTr("complete items")
//        onClicked: {
//            myobj.doSomething(444,function(x){
//                console.log("c++ js callback",x)
//                return true;
//            })
//        }


void CDairyHttpRequest::login(QString strUserName, QString strPasswd, QJSValue jsCallback)
{
/** 放在外面可以
    bool bSucceed = true;
    QJSEngine *jsEngine = jsCallback.engine();
    if (!jsEngine)
    {
        return;
    }
    QJSValue val = jsEngine->toScriptValue(bSucceed);
    QJSValueList paramList;
    paramList.append(val);
    qDebug() << jsCallback.call(paramList).toBool();  //js fucntion的返回值
    */

    if (strUserName.isEmpty())
    {
        QMessageBox::information(NULL, "提示", "请输入用户名！");
        return;
    }
    if (strPasswd.isEmpty())
    {
        QMessageBox::information(NULL, "提示", "请输入密码！");
        return;
    }

    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);

    // 这里使用了成员变量保存局部变量的值
    m_jsValue = jsCallback;
    // 此处为什么不能识别父类的finished???
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [=](QByteArray byteArray)
    {
        /*
        QSettings conf("conf.ini", QSettings::IniFormat);
        conf.beginGroup("user");
        if (ui->ckboxRememberUserName->isChecked())
        {
            conf.setValue("user_name", strUserName);
        }
        if (ui->ckboxRememberPasswd->isChecked())
        {
            conf.setValue("passwd", strPasswd);
        }
        */
        T_UserInfo tUserInfo = CNetAppointments::deserialization<T_UserInfo>(byteArray);
        CDairyAndroidApp::setUserInfo(tUserInfo);

        // 放在闭包里出现问题
        bool bSucceed = true;
        QJSEngine *jsEngine = m_jsValue.engine();
        if (!jsEngine)
        {
            return;
        }
        QJSValue val = jsEngine->toScriptValue(bSucceed);
        QJSValueList paramList;
        paramList.append(val);
        qDebug() << m_jsValue.call(paramList).toBool();  //js fucntion的返回值

    });

    QByteArray byteArrayMd5 = QCryptographicHash::hash(strPasswd.toLatin1(), QCryptographicHash::Md5);
    QString strPasswdMd5 = byteArrayMd5.toHex().mid(8, 16);	//md5:mid(8, 16) 32位转16位,字符截断, 一般规定取9-25

    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out << strUserName << strPasswdMd5;
    pDairyHttpClient->post(CNetAppointments::urlLogin(), byteArray.data(), byteArray.length());
}

void CDairyHttpRequest::dairyList()
{
    T_DairyListRequest tDairyListRequest;
    tDairyListRequest.uid = CDairyAndroidApp::userInfo().uid;
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        T_DairyListResp tDairyListResp = CNetAppointments::deserialization<T_DairyListResp>(byteArray);
//        if (bAppend)
//        {
//            //m_pJokeModel->appendListJoke(tDairyListResp.dairyList);
//        }
//        else
//        {

//        }
        CModelManager::getInstance()->dairyListModel()->loadDairyList(tDairyListResp.dairyList);
    });
    pDairyHttpClient->post(CNetAppointments::urlDairyList(), CNetAppointments::serializa(tDairyListRequest));
}

void CDairyHttpRequest::uploadDairy(int did, QString strTitle, QString strContent)
{

    T_Dairy dairy;
    //T_Dairy dairySaved;
    //dairy.did = did;
    dairy.uid = CDairyAndroidApp::userInfo().uid;
    dairy.did = did;
    dairy.strTitle = strTitle;
    dairy.strContent = strContent; //toPlainText 去除textEdit当中的纯文本


    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        T_Dairy dairySaved = CNetAppointments::deserialization<T_Dairy>(byteArray);
        CModelManager::getInstance()->dairyListModel()->addDairy(dairySaved);

//        if (dairy.isNewDairy())
//        {
            CLToast::showStr(NULL, "提交成功");
//            CModelManager::getInstance()->dairyListModel()->addDairy(dairySaved);

//            //emit saveDairyfinished(dairy, dairySaved);
//            //did = dairySaved.did;
//            //setWindowTitle(dairySaved.strTitle);
//            //ui->dairyEdit->document()->setModified(false);
//        }
    });
    pDairyHttpClient->post(CNetAppointments::urlDairyUpload(), CNetAppointments::serializa(dairy));
}
