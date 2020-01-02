/******************************************************************************
**
** @file
** ModelStbName.cpp
** @brief
** 机顶盒选择列表Model，源文件
** @par
** 未处理C++异常
** @author
** panxf
** @date
** 2017-5-10
**
******************************************************************************/

#include "ModelStbName.h"


// 构造函数
CModelStbName::CModelStbName(QObject *parent)
	: QAbstractListModel(parent)
{
	m_arrRoles[Qt::UserRole + EMF_Name]	= "name";
	m_arrRoles[Qt::UserRole + EMF_Readonly] = "isReadonly";
	m_arrRoles[Qt::UserRole + EMF_AttachedName]	= "attachedName";
	m_arrRoles[Qt::UserRole + EMF_IsChecked] = "isTempateChecked";

	m_lstTempate = CModuleManager::getInstance()->getModule(EM_STB)->getLstTemplate();
}

// 获取模板数目
int CModelStbName::i_GetTempCount() const
{
	return m_lstTempate.size();
}

// 系统重载函数，获取字段值
QVariant CModelStbName::data(const QModelIndex &index, int role) const
{
	QVariant ret;
	if (!index.isValid())
	{
		return ret;
	}

	if (index.row() < 0 || index.row() > m_lstTempate.count())
	{
		return ret;
	}

	CTemplate aTemplate = m_lstTempate[index.row()];

	// 按字段返回值
	switch (role - Qt::UserRole)
	{
	case EMF_Name: // 模板名称
		ret = aTemplate.getTemplateName();
		break;
	case EMF_Readonly: // 是否为只读模式
		ret = false;
		break;
	case EMF_AttachedName: // 附加
		ret = aTemplate.getTemplateAttachedName();
		break;
	case EMF_IsChecked: // 是否选择
		ret = aTemplate.getChecked();
		break;
	}

	return ret;
}

void CModelStbName::check(int nIndex)
{
	beginResetModel();
	m_lstTempate = CModuleManager::getInstance()->getModule(EM_STB)->check(nIndex);
	endResetModel();
}

void CModelStbName::checkAll(bool bChecked)
{
	beginResetModel();
	m_lstTempate = CModuleManager::getInstance()->getModule(EM_STB)->checkAll(bChecked);
	endResetModel();
}

void CModelStbName::seachfor(QString strKeyWord)
{

}

