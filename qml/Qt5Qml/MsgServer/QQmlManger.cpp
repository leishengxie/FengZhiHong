#include "QQmlManger.h"

#include <QQuickView>
#include <QQuickItem>
#include <QDebug>
#include "QUdpConnect.h"
#include <QQmlContext>
#include <QDateTime>

QQmlContext* QQmlManger::g_pQmlContext = NULL;


QQmlManger::QQmlManger(QObject* pParent)
	: QObject(pParent)
	, m_pObjParent(NULL)
	, m_pUdpConnect(NULL)
{
	m_pUdpConnect = new QUdpConnect();
	m_pMsgModel = new CMsgModel();
	connect(m_pUdpConnect, SIGNAL(sendMsg(QString, QString, unsigned int)),
			this, SLOT(onSendMsg(QString, QString, unsigned int)));
}

QQmlManger::~QQmlManger()
{
	CC_SAFE_DELETE(m_pObjParent);
	CC_SAFE_DELETE(m_pUdpConnect);
	CC_SAFE_DELETE(m_pMsgModel);
}

void QQmlManger::onMyselfCompleted()
{
	m_pObjParent = parent();
	//g_pQmlContext->setContextProperty("msgModel", m_pMsgModel);
}

void QQmlManger::onTool(E_ToolBtnType btnType)
{
	QObject* setButton =  m_pObjParent->findChild<QObject*>("qmlManger");
	QList<QObject*> lstChild = m_pObjParent->findChildren<QObject*>();
	for (int i = 0; i < lstChild.size(); ++i)
	{
		qDebug() << lstChild[i];
	}
	if (NULL != setButton)
	{
		QObject::connect(setButton, SIGNAL(clicked()), this, SLOT(showText()));
		setButton->setProperty("width", 200);
		setButton->setProperty("text", QString("hello,world,test"));
	}
	else
	{
		qDebug()<<"get button failed";
	}

}

void QQmlManger::onSendMsg(QString strMsg, QString strFrom, unsigned int unType)
{
	//    QObject* pObjLstMsg = m_pObjParent->findChild<QObject*>("lstMsg");
	//    if (NULL != pObjLstMsg)
	//    {
	//        QVariant returnedValue;
	//        QVariant varMsg = strFrom;
	//        QMetaObject::invokeMethod(pObjLstMsg, "setMsgContent", Q_RETURN_ARG(QVariant, returnedValue),Q_ARG(QVariant, varMsg));
	//        qDebug() << returnedValue.toString();
	//    }
	//    QObject* pObjTextMsg = m_pObjParent->findChild<QObject*>("textMsg");
	//    if (NULL != pObjTextMsg)
	//    {
	//        pObjTextMsg->setProperty("text", strMsg);
	//    }

	int nIndex = m_pMsgModel->rowCount();
	QString strIndex = "(" + QString::number(nIndex) + ") ";
	QString strDataTime = QDateTime::currentDateTime().toString("dddd yyyy-MM-dd MMM hh:mm:ss");
	strFrom = strIndex + strDataTime + " : " + strFrom;
	if (2 == unType)
	{
		strMsg = "服务器已关闭";
	}
	CMsg msgNew(strFrom, strMsg, unType);
	m_pMsgModel->e_AddMsg(msgNew);
	T_Msg tMsg;
	tMsg.strFrom = strFrom;
	tMsg.strContent = strMsg;
	i_displayerMsg(tMsg);
}


void QQmlManger::i_displayerMsg(T_Msg tMsg)
{
		setText(tMsg.strFrom);
		setContent(tMsg.strContent);

		emit textChanged(tMsg.strFrom);
		emit contentChanged(tMsg.strContent);
}

void QQmlManger::lastContent()
{
	T_Msg tMsg;
	if (m_pMsgModel->e_IsGetDataSuccess(M_Prev, tMsg, 1))
	{
		i_displayerMsg(tMsg);
	}
}

void QQmlManger::nextContent()
{
	T_Msg tMsg;
	if (m_pMsgModel->e_IsGetDataSuccess(M_Next, tMsg, 1))
	{
		i_displayerMsg(tMsg);
	}
}
