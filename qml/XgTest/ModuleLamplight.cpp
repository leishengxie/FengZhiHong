#include "ModuleLamplight.h"


CLamplightModule::CLamplightModule()
{
	m_tHttpHeader.strModuleName = "lighttemplate";
	QStringList lstTemp= {"灯光1", "灯光2", "灯光3", "灯光4", "灯光5"};
	m_strLstDefaultEffect = lstTemp;
}

CLamplightModule::~CLamplightModule()
{

}

//复制新模板
void CLamplightModule::requreCreat(QString strTemplateName)
{
	CTemplate aTemplate = getCurrSelectTemplate();
	aTemplate.setId(-1);
	aTemplate.setTemplateName(strTemplateName);
	addTemplate(aTemplate);
	QString strData;
	strData.append("&name=" + aTemplate.getTemplateName());
	strData.append("&style="  + aTemplate.getStyle("|"));
	strData = QString::fromUtf8(strData.toStdString().c_str());
	m_tHttpHeader.strData = strData;
	requre(HF_CREAT);
}

void CLamplightModule::requreSet()
{
	QString strData;
	for (int i = 0; i < m_lstTemplate.size(); ++i)
	{
		strData.append("&id=" + QString::number(m_lstTemplate[i].getId()));
		strData.append("&clubInfoId=10000");
		strData.append("&name=" + m_lstTemplate[i].getTemplateName());
		strData.append("&style="  + m_lstTemplate[i].getStyle("|"));
	}
	strData = QString::fromUtf8(strData.toStdString().c_str());
	m_tHttpHeader.strData = strData;
	requre(HF_SET);
}

void CLamplightModule::requreDeleteById(int nId)
{
	m_tHttpHeader.reset();
	m_tHttpHeader.nId = nId;
	requre(HF_DELETE);
}

void CLamplightModule::requreGetById(int nId)
{
	m_tHttpHeader.reset();
	m_tHttpHeader.nId = nId;
	requre(HF_GET);
}

void CLamplightModule::requreList(int nClubInfoId)
{
	m_tHttpHeader.reset();
	m_tHttpHeader.nClubInfoId = nClubInfoId;
	requre(HF_LIST);
}

void CLamplightModule::requreGetSongStyle(int nClubInfoId)
{
	m_tHttpHeader.reset();
	m_tHttpHeader.strModuleName = "songstyleinfo";
	m_tHttpHeader.nClubInfoId = nClubInfoId;
	requre(HF_GET);
	m_tHttpHeader.strModuleName = "lighttemplate";
}

void CLamplightModule::parseGet(QJsonObject objRoot)
{
	QString strTemplate = objRoot["query"].toString();
	QJsonObject obj2nd = objRoot["data"].toObject();
	int nId = obj2nd["id"].toInt();
	int nVersion = obj2nd["version"].toInt();
	int nClubInfoId = obj2nd["clubInfoId"].toInt();
	QString strName = obj2nd["name"].toString();
	QString strStyle = obj2nd["style"].toString();
	qDebug() << "strName=" << strName  << "strStyle=" << strStyle;
	if (strTemplate == "songStyleInfo")
	{
		if (!strStyle.isEmpty())
		{
			QStringList lstStyle = strStyle.split("|");
			if(lstStyle.size() < 2)
			{
				qDebug() << "error: the lstStyle size < 2";
				return;
			}
			qDebug() << "songStyleInfo refresh seccess";
			m_strLstDefaultEffect = lstStyle;
			requreList(m_tHttpHeader.nClubInfoId);
			return;
		}
	}

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

void CLamplightModule::parseList(QJsonObject objRoot)
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
				selectTextLX.setLstEffect(m_strLstDefaultEffect);
				aTemplate.addASelet(selectTextLX);
			}
			addTemplate(aTemplate);
		}
	}
	emit refresh();
}
