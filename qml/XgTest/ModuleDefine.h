/******************************************************************************
**
** @file
** LamplightDataDefine.h
** @brief
** 灯光效果模板
** @par
** 未处理C++异常
** @author
** leisx
** @date
** 2017-5-4
**
******************************************************************************/
#ifndef MODULE_DEFINE_H
#define MODULE_DEFINE_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "global.h"
#include "HttpClient.h"

class CSelectText
{
public:
	//用于下拉列表
	CSelectText(QString strSelectTextName, unsigned int nCurValue = 0);
	//用于单行
	CSelectText(QString strSelectTextName, QString strSelectTexValue, bool bReadOnly = false);

	void addEffect(QString strEffect);

	QString getStyle();

	CC_SYNTHESIZE(QString, m_strSelectTextName, SelectTextName)
	CC_SYNTHESIZE(QStringList, m_lstEffect, LstEffect)
	CC_SYNTHESIZE(bool, m_bReadOnly, ReadOnly)
	CC_SYNTHESIZE(unsigned int, m_nCurValue, CurValue)

};


class CTemplate
{
public:
	CTemplate(int nId = -1, QString strTemplateName = "默认模板",
			  QString strTemplateAttachedName = "", bool bCheck = false);


	void addASelet(CSelectText selectText);

	QString getStyle(QString str);

	void saveCurSelect(int nSelectTextIndex, int nSelectValue);

	void checked();

	CSelectText getCurSelectText();

	CC_SYNTHESIZE(int, m_nId, Id)
	CC_SYNTHESIZE(QString, m_strTemplateName, TemplateName)
	CC_SYNTHESIZE(QString, m_strTemplateAttachedName, TemplateAttachedName)
	CC_SYNTHESIZE(bool, m_bChecked, Checked)
	CC_SYNTHESIZE(QList<CSelectText>, m_lstSelect, LstSelect)
	CC_SYNTHESIZE(int, m_nCurSelectTextIndex, CurSelectTextIndex)
};


enum E_HttpFunc
{
	HF_GET,
	HF_SET,
	HF_LIST,
	HF_DELETE,
	HF_CREAT,
	HF_NothingToDo
};

enum E_HttpMethod
{
	HM_GET,
	HM_POST
};


enum E_ModuleType
{
	EM_Lamplight,
	EM_STB
};

struct T_HttpHeader
{
	QString strProtocol;
	QString strIp;
	int nPort;
	QString strModuleName;
	QString strMethod;
	int nId;
	int nClubInfoId;
	QString strData;

	QString data()
	{
		QString httpData;
		httpData += strProtocol;
		httpData += "://";
		httpData += strIp;
		httpData += ":";
		httpData += QString::number(nPort);
		httpData += "/xgcloud/";
		httpData += strModuleName;
		httpData += ".html?";
		httpData += strMethod;
		if(nId != -1)
		{
			httpData += "&id=" + QString::number(nId);
		}
		if(nClubInfoId != -1)
		{
			httpData += "&clubInfoId=" + QString::number(nClubInfoId);
		}
		httpData += strData;
		return httpData;
	}

	void reset()
	{
		nId = -1;
		nClubInfoId = -1;
		strData = "";
	}

	T_HttpHeader()
		: strProtocol("https")
		, strIp("192.168.5.59")
		, nPort(11443)
		, strModuleName("")
		, strMethod("")
		, nId(-1)
		, nClubInfoId(-1)
		, strData("")
	{

	}
};

class CModule : public QObject
{
	Q_OBJECT

public:
	CModule();

	//获取左侧模板名列表
	QStringList getLstTemplateName();

	//用户界面点击模板获得相应数据
	CTemplate getTemplateByIndex(int nIndex);

	void saveCurSelect(int nSelectTextIndex, int nSelectValue);

	//添加模板
	void addTemplate(CTemplate aTemplate);

	//清除数据
	void clear();

	//用户界面点击全选
	QList<CTemplate> checkAll(bool bChecked);

	//
	QList<CTemplate> check(int nIndex);

	//查找模板
	QList<CTemplate> seachfor(QString strKeyWord);

	//删除模板
	void deletTemplateByIndex(int nIndex);

	//
	CTemplate getCurrSelectTemplate();


signals:
	void refresh();

public slots:

	void handleDownloadCompleted(bool bOk, CHttpClient* pHttpQuery);

	void handReadyRead(CHttpClient* pHttpQuery);


public:

	void requre(E_HttpFunc eHttpFunc);

	virtual void requreCreat(QString strTemplateName) = 0;

	virtual void requreSet() = 0;

	virtual void requreDeleteById(int nId) = 0;

	virtual void requreGetById(int nId) = 0;

	virtual void requreList(int nClubInfoId) = 0;

	virtual void parseList(QJsonObject objRoot) = 0;

	virtual void parseGet(QJsonObject objRoot) = 0;

	void handleObjRoot(QJsonObject objRoot, ULONG nQueryTag);

	CC_SYNTHESIZE(QList<CTemplate>, m_lstTemplate, LstTemplate)
	CC_SYNTHESIZE(unsigned int, m_unCurTemplateIndex, CurTemplateIndex)

protected:

	T_HttpHeader m_tHttpHeader;
};


#endif // MODULE_DEFINE_H
