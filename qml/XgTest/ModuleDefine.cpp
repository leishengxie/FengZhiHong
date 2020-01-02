#include "ModuleDefine.h"

static const char* fields[] = 
{
	"query",
	"data",
	"id",
	"version",
	"clubInfoId",
	"name",
	"style"
};

static const char* arrModuleName[] =
{
	"lighttemplate",
	"userinfoex", //stbtemplate
};

static const char* arrHttpMethod[] =
{
	"method=get",
	"method=set",
	"method=list",
	"method=delete",
	"method=create",
};

CSelectText::CSelectText(QString strSelectTextName, unsigned int nCurValue)
	: m_strSelectTextName(strSelectTextName)
	, m_nCurValue(nCurValue)
	, m_bReadOnly(false)
{

}

CSelectText::CSelectText(QString strSelectTextName, QString strSelectTexValue, bool bReadOnly)
	: m_strSelectTextName(strSelectTextName)
	, m_bReadOnly(bReadOnly)
	, m_nCurValue(0)
{
	m_lstEffect.append(strSelectTexValue);
}

void CSelectText::addEffect(QString strEffect)
{
	m_lstEffect.append(strEffect);
}

QString CSelectText::getStyle()
{
	return m_strSelectTextName + "=" + QString::number(m_nCurValue);
}

CTemplate::CTemplate(int nId, QString strTemplateName, QString strTemplateAttachedName, bool bCheck)
	: m_strTemplateName(strTemplateName)
	, m_strTemplateAttachedName(strTemplateAttachedName)
	, m_bChecked(bCheck)
	, m_nId(nId)
{

}

void CTemplate::addASelet(CSelectText selectText)
{
	m_lstSelect.append(selectText);
}

QString CTemplate::getStyle(QString str)
{
	QString strStyle;
	for (int i = 0; i < m_lstSelect.size(); ++i)
	{
		strStyle.push_back(m_lstSelect[i].getStyle());
		strStyle.push_back(str);
	}
	strStyle.chop(str.length());
	return strStyle;
}

void CTemplate::saveCurSelect(int nSelectTextIndex, int nSelectValue)
{
	m_nCurSelectTextIndex = nSelectTextIndex;
	m_lstSelect[m_nCurSelectTextIndex].setCurValue(nSelectValue);

}

void CTemplate::checked()
{
	m_bChecked = !m_bChecked;
}

CSelectText CTemplate::getCurSelectText()
{
	return m_lstSelect[m_nCurSelectTextIndex];
}


CModule::CModule()
	: m_unCurTemplateIndex(0)
{

}

QStringList CModule::getLstTemplateName()
{
	QStringList lstTempName;
	for (int i = 0; i < m_lstTemplate.size(); ++i)
	{
		lstTempName.append(m_lstTemplate[i].getTemplateName());
	}
	return lstTempName;
}

CTemplate CModule::getTemplateByIndex(int nIndex)
{
	CTemplate aTemplate;
	m_unCurTemplateIndex = nIndex;
	if (nIndex < m_lstTemplate.size())
	{
		return m_lstTemplate[nIndex];
	}
	else
	{
		return aTemplate;
	}
}

void CModule::saveCurSelect(int nSelectTextIndex, int nSelectValue)
{
	m_lstTemplate[m_unCurTemplateIndex].saveCurSelect(nSelectTextIndex, nSelectValue);
}

void CModule::addTemplate(CTemplate aTemplate)
{
	m_lstTemplate.append(aTemplate);
}

void CModule::clear()
{
	m_lstTemplate.clear();
	m_unCurTemplateIndex = 0;
}

QList<CTemplate> CModule::checkAll(bool bChecked)
{
	for (int i = 0; i < m_lstTemplate.size(); ++i)
	{
		m_lstTemplate[i].setChecked(bChecked);
	}
	return m_lstTemplate;
}

QList<CTemplate> CModule::check(int nIndex)
{
	m_lstTemplate[nIndex].checked();
	return m_lstTemplate;
}

QList<CTemplate> CModule::seachfor(QString strKeyWord)
{
	for (int i = 0; i < m_lstTemplate.size(); ++i)
	{
		m_lstTemplate[i].getTemplateName();
	}
	return m_lstTemplate;
}

void CModule::deletTemplateByIndex(int nIndex)
{
	if (m_lstTemplate.size() > nIndex)
	{
		m_lstTemplate.removeAt(nIndex);
	}
}

CTemplate CModule::getCurrSelectTemplate()
{
	return m_lstTemplate[m_unCurTemplateIndex];
}

void CModule::handleDownloadCompleted(bool bOk, CHttpClient* pHttpQuery)
{
	if (!bOk)
	{
		return;
	}
	ULONG nQueryTag = pHttpQuery->e_QueryTag();
	QByteArray byteData = pHttpQuery->e_GetData();
	qDebug() << byteData << "\n";
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(byteData, &json_error);
	if (json_error.error == QJsonParseError::NoError)
	{
		QJsonObject objRoot;
		if (parse_doucment.isObject())
		{
			objRoot = parse_doucment.object();
		}
		handleObjRoot(objRoot, nQueryTag);
	}
}

void CModule::handReadyRead(CHttpClient* pHttpQuery)
{

}


void CModule::requre(E_HttpFunc eHttpFunc)
{
	m_tHttpHeader.strMethod = arrHttpMethod[eHttpFunc];
	CHttpClient *pTempHttpClient = CHttpClient::e_GetTempObject(eHttpFunc);
	connect(pTempHttpClient, SIGNAL(readyRead(CHttpClient*)),this, SLOT(handReadyRead(CHttpClient*)));
	connect(pTempHttpClient, SIGNAL(downloadCompleted(bool,CHttpClient*)),
			this, SLOT(handleDownloadCompleted(bool,CHttpClient*)));
	QString strData = m_tHttpHeader.data();
	pTempHttpClient->e_HttpGet(QUrl(strData));
}

void CModule::handleObjRoot(QJsonObject objRoot, ULONG nQueryTag)
{
	switch (nQueryTag)
	{
	case HF_GET:
	{
		parseGet(objRoot);
		break;
	}
	case HF_DELETE:
	{
		break;
	}
	case HF_LIST:
	{
		parseList(objRoot);
		break;
	}
	case HF_SET:
	{
		break;
	}
	case HF_CREAT:
	{
		break;
	}
	default:
		break;
	}
}


