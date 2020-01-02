#include "ModuleStb.h"

CStbModule::CStbModule()
{
	m_tHttpHeader.strModuleName = "userinfoex";
}

CStbModule::~CStbModule()
{

}


void CStbModule::requreCreat(QString strTemplateName)
{
	CTemplate aTemplate = getCurrSelectTemplate();
	aTemplate.setId(-1);
	aTemplate.setTemplateName(strTemplateName);
	addTemplate(aTemplate);
	QString strData;
	strData.append("&name=" + aTemplate.getTemplateName());
	strData.append("&attachedName" + aTemplate.getTemplateAttachedName());
	strData.append("&style="  + aTemplate.getStyle("|"));
	strData = QString::fromUtf8(strData.toStdString().c_str());
	m_tHttpHeader.strData = strData;
	requre(HF_CREAT);
}

void CStbModule::requreSet()
{
	QString strData;
	for (int i = 0; i < m_lstTemplate.size(); ++i)
	{
		strData.append("&id=" + QString::number(m_lstTemplate[i].getId()));
		strData.append("&clubInfoId=10000");
		strData.append("&name=" + m_lstTemplate[i].getTemplateName());
		strData.append("&attachedName" + m_lstTemplate[i].getTemplateAttachedName());
		strData.append("&style="  + m_lstTemplate[i].getStyle("|"));
	}
	strData = QString::fromUtf8(strData.toStdString().c_str());
	m_tHttpHeader.strData = strData;
	requre(HF_SET);

}

void CStbModule::requreDeleteById(int nId)
{
	m_tHttpHeader.reset();
	m_tHttpHeader.nId = nId;
	requre(HF_DELETE);
}


void CStbModule::requreGetById(int nId)
{
	m_tHttpHeader.reset();
	m_tHttpHeader.nId = nId;
	requre(HF_GET);
}


void CStbModule::requreList(int nClubInfoId)
{
	m_tHttpHeader.reset();
	m_tHttpHeader.nClubInfoId = nClubInfoId;
	requre(HF_LIST);
}

void CStbModule::parseGet(QJsonObject objRoot)
{
	//QString strTemplate = getJsonValueQString(objRoot, "query"); //模板
	QJsonObject obj2nd = objRoot["data"].toObject();
	int nId = obj2nd["id"].toInt();
	int nVersion = obj2nd["version"].toInt();
	int nClubInfoId = obj2nd["clubInfoId"].toInt();
	QString strName = obj2nd["name"].toString();
	QString strStyle = obj2nd["style"].toString();
	qDebug() << "strName=" << strName  << "strStyle=" << strStyle;
	if (!strStyle.isEmpty())
	{
		QStringList lstStyle = strStyle.split("|");
		CTemplate aTemplate(nId, strName);
		for (int i = 0; i < lstStyle.size(); ++i)
		{
			QStringList strLstSelectText = lstStyle[i].split("=");
			if(strLstSelectText.size() < 2)
			{
				qDebug() << "error: the strLstSelectText size < 2";
				return;
			}
			CSelectText selectTextLX(strLstSelectText.at(0), strLstSelectText.at(1).toInt());
			aTemplate.addASelet(selectTextLX);
		}
		addTemplate(aTemplate);
	}

}

void CStbModule::parseList(QJsonObject objRoot)
{
	QString strTemplate = objRoot["query"].toString(); //模板
	clear();
	QJsonArray arrData = objRoot["data"].toArray();
	for (int i = 0; i < arrData.size(); ++i)
	{
		QJsonObject obj2nd = arrData.at(i).toObject();
		int nId = obj2nd["id"].toInt();
		QString strName = obj2nd["name"].toString();
		QString strStyle = obj2nd["style"].toString();
		qDebug() <<"id=" <<nId << "strName=" << strName  << "strStyle=" << strStyle;
		if (!strStyle.isEmpty())
		{
			QStringList lstStyle = strStyle.split("|");
			CTemplate aTemplate(nId, strName);
			for (int j = 0; j < lstStyle.size(); ++j)
			{
				QStringList strLstSelectText = lstStyle[j].split("=");
				if(strLstSelectText.size() < 2)
				{
					qDebug() << "error: the strLstSelectText size < 2";
					return;
				}
				CSelectText selectTextLX(strLstSelectText.at(0), strLstSelectText.at(1).toInt());
				aTemplate.addASelet(selectTextLX);
			}
			addTemplate(aTemplate);
		}
	}
	emit refresh();
}







