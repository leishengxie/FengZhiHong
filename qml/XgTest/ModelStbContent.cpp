#include "ModelStbContent.h"


CModelStbContent::CModelStbContent(QObject *parent)
	: QAbstractListModel(parent)
{
	m_arrRoles[Qt::UserRole + S_SelectName]  = "selectName";
	m_arrRoles[Qt::UserRole + S_LstEffect]  = "modelEffect";
	m_arrRoles[Qt::UserRole + S_CurEffect] = "curIndex";
	m_arrRoles[Qt::UserRole + S_ReadOnly] = "readOnly";
	m_lstSelectText = CModuleManager::getInstance()->getModule(EM_STB)->getTemplateByIndex(0).getLstSelect();
}



QVariant CModelStbContent::data(const QModelIndex &index, int role) const
{
	QVariant ret;
	if (!index.isValid())
		return ret;

	if (index.row() < 0 || index.row() > m_lstSelectText.count())
	{
		return ret;
	}

	const CSelectText& selectText = m_lstSelectText[index.row()];

	// 按字段返回值
	switch (role - Qt::UserRole)
	{
	case S_SelectName: // 模板名称
		ret = selectText.getSelectTextName();
		break;
	case S_LstEffect: //选择列表
		ret = selectText.getLstEffect();
		break;
	case S_CurEffect: //当前选择
		ret = selectText.getCurValue();
		break;
	case S_ReadOnly: //当前选择
		ret = selectText.getReadOnly();
		break;
	}
	return ret;
}

void CModelStbContent::refreshModel(int nIndex)
{
	beginResetModel();
	m_lstSelectText = CModuleManager::getInstance()->getModule(EM_STB)->getTemplateByIndex(nIndex).getLstSelect();
	endResetModel();
}

void CModelStbContent::saveCurSelect(int nSelectTextIndex, int nSelectValue)
{
	CModuleManager::getInstance()->getModule(EM_STB)->saveCurSelect(nSelectTextIndex, nSelectValue);
}

