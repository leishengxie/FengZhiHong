#include "drinksmodel.h"

CDrinksGoods::CDrinksGoods()
	: m_unId(0)
	, m_strName("")
	, m_fUnitPrice(0.0f)
	, m_strRemark("")
	, m_unNum(0)
	, m_fTotalPrice(0.0f)
{

}

CDrinksGoods::CDrinksGoods(unsigned int unId, QString strName, float fUnitPrice, QString strRemark)
	: m_unId(unId)
	, m_strName(strName)
	, m_fUnitPrice(fUnitPrice)
	, m_strRemark(strRemark)
	, m_unNum(1)
	, m_fTotalPrice(fUnitPrice)
{

}

CDrinksGoods::~CDrinksGoods()
{

}

void CDrinksClass::e_AddNewGoods(CDrinksGoods newGoods)
{
	m_lstGoods.append(newGoods);
}

CDrinksClass::CDrinksClass(QString strCName, unsigned int unCId, CDrinksGoods drinksGoods)
	: m_strCName(strCName)
	, m_unCId(unCId)
{

}




CDrinksModel::CDrinksModel(QObject* parent)
	: QAbstractListModel(parent)
	, m_nCurGoodsPageIndex(-1)
{
	CDrinksClass drinksC("啤酒");
	drinksC.e_AddNewGoods(CDrinksGoods(0, "百威啤酒", 8, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(1, "啤酒A", 5, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(2, "啤酒B", 5, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(3, "啤酒C", 8, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(4, "啤酒D", 7, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(5, "啤酒E", 10, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(6, "啤酒F", 8, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(7, "啤酒G", 5, "加冰"));
	drinksC.e_AddNewGoods(CDrinksGoods(8, "啤酒H", 6, "加冰"));
	m_lstDrinksClass.append(drinksC);
	CDrinksClass drinksCH("红酒");
	drinksCH.e_AddNewGoods(CDrinksGoods(0, "红葡萄酒", 125, ""));
	m_lstDrinksClass.append(drinksCH);
	m_lstDrinksClass.append(CDrinksClass("洋酒"));
	m_lstDrinksClass.append(CDrinksClass("饮料"));
	m_lstDrinksClass.append(CDrinksClass("小吃"));
	m_lstDrinksClass.append(CDrinksClass("A"));
	m_lstDrinksClass.append(CDrinksClass("B"));
	m_lstDrinksClass.append(CDrinksClass("C"));
	m_lstDrinksClass.append(CDrinksClass("D"));
	showModel(0);

}

void CDrinksModel::e_AddDrinksC(const CDrinksClass &msg)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_lstDrinksClass << msg;
	++m_nCurGoodsPageIndex;
	endInsertRows();
}

int CDrinksModel::rowCount(const QModelIndex& parent) const
{
	return m_lstGoods.count();
}

QVariant CDrinksModel::data(const QModelIndex& index, int role) const
{
	if (index.row() < 0 || index.row() > m_lstGoods.count())
	{
		return QVariant();
	}

	const CDrinksGoods& msg = m_lstGoods[index.row()];

	if (D_Id == role)
	{
		return msg.Id();
	}
	else if (D_Name == role)
	{
		return msg.Name();
	}
	else if (D_Num == role)
	{
		return msg.Num();
	}
	else if (D_UnitPrice == role)
	{
		return msg.UnitPrice();
	}
	else if (D_TotalPrice == role)
	{
		return msg.TotalPrice();
	}
	else if (D_Remark == role)
	{
		return msg.Remark();
	}
	return QVariant();
}


QHash<int, QByteArray> CDrinksModel::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[D_Id]  = "index";
	roles[D_Name]  = "goldName";
	roles[D_Num] = "num";
	roles[D_UnitPrice]  = "unitPrice";
	roles[D_TotalPrice]  = "figure";
	roles[D_Remark] = "remark";
	return roles;
}

void CDrinksModel::e_ClearDrinksC()
{
	if (0 != m_lstGoods.count())
	{
		beginResetModel();
		m_lstDrinksClass.clear();
		endResetModel();
	}
}

int CDrinksModel::e_GetDrinksCSize()
{
	return m_lstDrinksClass.size();
}

QStringList CDrinksModel::e_GetLstDrinksCName()
{
	QStringList lstDrinksCName;
	for (int i = 0; i < m_lstDrinksClass.size(); ++i)
	{
		lstDrinksCName.append(m_lstDrinksClass[i].StrCName());
	}
	return lstDrinksCName;
}

void CDrinksModel::showModel(int nIndex)
{
	beginResetModel();
	m_lstGoods.clear();
	m_lstGoods = m_lstDrinksClass[nIndex].getLstGoods();
	endResetModel();
}

void CDrinksModel::prevGoodsPage()
{
	//	//QList<CDrinksGoods>::iterator iter;
	//	unsigned int unTotalPage = m_lstGoods.count() / 7;
	//	if (m_nCurGoodsPageIndex > 0)
	//	{
	//		--m_nCurGoodsPageIndex;
	//		for (int i = m_nCurGoodsPageIndex * 7; i < 7; ++i)
	//	}

}


