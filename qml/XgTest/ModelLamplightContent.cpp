#include "ModelLamplightContent.h"

CModelLamplightContent::CModelLamplightContent(QObject *parent)
	: QAbstractListModel(parent)
	, m_nCurrIndex(0)
{
	m_arrRoles[Qt::UserRole + S_SelectName]  = "selectName";
	m_arrRoles[Qt::UserRole + S_LstLamplightEffect]  = "modelLamplight";
	m_arrRoles[Qt::UserRole + S_CurLamplightEffect] = "curIndex";
	connect(CModuleManager::getInstance()->getModule(EM_Lamplight),
			SIGNAL(refresh()),this, SLOT(refresh()));
	refreshModel(m_nCurrIndex);
}



QVariant CModelLamplightContent::data(const QModelIndex &index, int role) const
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
	case S_LstLamplightEffect: //选择灯光效果列表
		ret = selectText.getLstEffect();
		break;
	case S_CurLamplightEffect: //当前选择的灯光效果
		ret = selectText.getCurValue();
		break;
	}
	return ret;
}

void CModelLamplightContent::refreshModel(int nIndex)
{
	beginResetModel();
	m_lstSelectText = CModuleManager::getInstance()->getModule(EM_Lamplight)->getTemplateByIndex(nIndex).getLstSelect();
	endResetModel();
}

void CModelLamplightContent::refresh()
{
	refreshModel(0);
}

void CModelLamplightContent::saveCurSelect(int nSelectTextIndex, int nSelectValue)
{
	CModuleManager::getInstance()->getModule(EM_Lamplight)->saveCurSelect(nSelectTextIndex, nSelectValue);
}


