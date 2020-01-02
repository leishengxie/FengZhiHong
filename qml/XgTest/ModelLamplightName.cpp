#include "ModelLamplightName.h"


// 构造函数
CModelLamplightName::CModelLamplightName(QObject *parent)
	: QAbstractListModel(parent)
{
	m_arrRoles[Qt::UserRole + EMF_Name]		= "tempName";
	m_arrRoles[Qt::UserRole + EMF_Readonly] = "isReadonly";

	m_arrTempName = CModuleManager::getInstance()->getModule(EM_Lamplight)->getLstTemplateName();
	connect(CModuleManager::getInstance()->getModule(EM_Lamplight), SIGNAL(refresh()), this, SLOT(refresh()));
}

void CModelLamplightName::requireDeleteTemplate(int nIndex)
{
	int nId = CModuleManager::getInstance()->getModule(EM_Lamplight)->getTemplateByIndex(nIndex).getId();
	CModuleManager::getInstance()->getModule(EM_Lamplight)->deletTemplateByIndex(nIndex);
	CModuleManager::getInstance()->getModule(EM_Lamplight)->requreDeleteById(nId);
	refresh();
}

void CModelLamplightName::refresh()
{
	beginResetModel();
	m_arrTempName = CModuleManager::getInstance()->getModule(EM_Lamplight)->getLstTemplateName();
	endResetModel();
}
// 获取模板数目
int CModelLamplightName::i_GetTempCount() const
{
	return m_arrTempName.size();
}

// 系统重载函数，获取字段值
QVariant CModelLamplightName::data(const QModelIndex &index, int role) const
{
	QVariant ret;
	if (!index.isValid())
	{
		return ret;
	}

	// 当前记录行索引
	int nIndex = index.row();

	// 按字段返回值
	switch (role - Qt::UserRole)
	{
	case EMF_Name: // 模板名称
		ret = m_arrTempName[nIndex];
		break;

	case EMF_Readonly: // 是否为只读模式
		ret = false;
		break;
	}

	return ret;
}

void CModelLamplightName::requireSet()
{
	CModuleManager::getInstance()->getModule(EM_Lamplight)->requreSet();
}

void CModelLamplightName::requireAddTemplate(QString strTemplateName)
{
	CModuleManager::getInstance()->getModule(EM_Lamplight)->requreCreat(strTemplateName);
	refresh();
}
