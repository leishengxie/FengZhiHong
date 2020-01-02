#ifndef QQMLMANGER_H
#define QQMLMANGER_H

#include <QObject>
#include "CGlobal.h"
#include "QMsgModel.h"

class QUdpConnect;
class CMsgModel;
class QQmlContext;

class QQmlManger: public QObject
{

Q_OBJECT

    Q_ENUMS(E_ToolBtnType)          //这个将这个枚举类型声明到qml里面可用

	Q_PROPERTY(QString content READ Content WRITE setContent NOTIFY contentChanged)
	Q_PROPERTY(QString text READ Text WRITE setText NOTIFY textChanged)

public:
//	Q_INVOKABLE void lastContent();
//	Q_INVOKABLE void nextContent();
    QQmlManger(QObject* pParent = 0);
    ~QQmlManger();


    enum E_ToolBtnType
    {
        LB_SET,
        LB_FILE
    };

CC_SETGOT(QString, m_strContent, Content)
CC_SETGOT(QString, m_strText, Text)

signals:
	void contentChanged(QString strContent);
	void textChanged(QString strText);


public:
	static QQmlContext* g_pQmlContext;

public slots:
    void onMyselfCompleted();
    void onTool(E_ToolBtnType eBtnType);
	void onSendMsg(QString strMsg, QString strFrom, unsigned int unType);
	void lastContent();
	void nextContent();

private:
	void i_displayerMsg(T_Msg tMsg);

private:
     QObject* m_pObjParent;
     QUdpConnect* m_pUdpConnect;
	 CMsgModel* m_pMsgModel;
};


#endif // QQMLMANGER_H
