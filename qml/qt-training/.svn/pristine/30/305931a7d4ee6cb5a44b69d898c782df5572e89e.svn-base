/******************************************************************************
**
** @file
** drinksmodel.h
** @brief
** 酒水的Model类
** @author
** leisx
** @date
** 2017-3-28
**
******************************************************************************/
#ifndef CDRINKSMODEL_H
#define CDRINKSMODEL_H


#include <QAbstractListModel>
#include "global.h"


// 单个饮品信息
class CDrinksGoods
{
public:

	CDrinksGoods();
	CDrinksGoods(unsigned int unId, QString strName, float fUnitPrice, QString strRemark = "");
	~CDrinksGoods();

	CC_SETGETCONST(unsigned int, m_unId, Id)
	CC_SETGETCONST(QString, m_strName, Name)
	CC_SETGETCONST(unsigned int, m_unNum, Num)
	CC_SETGETCONST(float, m_fUnitPrice, UnitPrice)
	CC_SETGETCONST(float, m_fTotalPrice, TotalPrice)
	CC_SETGETCONST(QString, m_strRemark, Remark)

};


// 饮品类别
class CDrinksClass
{
public:

	 //向该类商品注册添加一个新商品
	void e_AddNewGoods(CDrinksGoods newGoods);

	CDrinksClass(QString strCName, unsigned int unCId = 0, CDrinksGoods drinksGoods = CDrinksGoods());

	QList<CDrinksGoods> getLstGoods()
	{
		return m_lstGoods;
	}


CC_SETGOT(QString, m_strCName, StrCName)

private:
	unsigned int m_unCId;

	// 单类饮品队列
	QList<CDrinksGoods> m_lstGoods;

};



class CDrinksModel : public QAbstractListModel
{

	Q_OBJECT

public:
	enum E_DrinksGoods {
		D_Id,              // id号
		D_Name,            // 饮品名称
		D_Num,             // 饮品数量
		D_UnitPrice,       // 单价
		D_TotalPrice,      // 总金额
		D_Remark           // 备注
	};

	CDrinksModel(QObject* parent = 0);
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QHash<int, QByteArray> roleNames() const;

public:

	///
	/// @par 功能
	/// 添加饮品类别
	/// @param[in] msg - 文件名字符串
	///
	void e_AddDrinksC(const CDrinksClass& msg);

	///
	/// @par 功能
	/// 清空所有饮品类
	///
	void e_ClearDrinksC();

	///
	/// @par 功能
	/// 获取所有饮品队列长度
	/// @return 队列长度
	///
	int e_GetDrinksCSize();

	///
	/// @par 功能
	/// 获取所有饮品类名
	/// @return 饮品类别名
	///
	QStringList e_GetLstDrinksCName();

	///
	/// @par 功能
	/// 显示model
	/// @param[in] nIndex - 类索引
	///
	void showModel(int nIndex);

	///
	/// @par 功能
	/// 饮品列表上一页
	///
	void prevGoodsPage();

	///
	/// @par 功能
	/// 饮品列表下一页
	///
	void nextGoodsPage();

private:

	// 用于model的单类饮品队列
	QList<CDrinksGoods> m_lstGoods;

	// 饮品类队列
	QList<CDrinksClass> m_lstDrinksClass;

	// 当前饮品索引页
	int m_nCurGoodsPageIndex;
};

#endif // CDRINKSMODEL_H
