/******************************************************************************
**
** @file
** ModelStbContent.h
** @brief
** 机顶盒模板选择列表Model
** @par
** 未处理C++异常
** @author
** leisx
** @date
** 2017-5-10
**
******************************************************************************/

#ifndef CMODELSTBCONTENT_H
#define CMODELSTBCONTENT_H


#include <QAbstractListModel>
#include <QtDebug>
#include "ModuleManager.h"

class CModelStbContent : public QAbstractListModel
{
	Q_OBJECT

	enum E_SelectText {
		S_SelectName,   // 名称
		S_LstEffect,    // 效果列表
		S_CurEffect,     // 当前效果
		S_ReadOnly      //是否为仅可读
	};


public:
	explicit CModelStbContent(QObject *parent = 0);

	// 系统重载函数，获取记录行数
	int rowCount(const QModelIndex &parent = QModelIndex()) const override
	{
//		if (!parent.isValid()) //bug 如果继承QAbstractListModel而不是QAbstractItemModel此处直接返回
//		{
//			return 0;
//		}
		return m_lstSelectText.count();
	}

	// 系统重载函数，返回字段名称数组
	QHash<int, QByteArray> roleNames() const override
	{
		return m_arrRoles;

	}

	// 系统重载函数，获取字段值
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
	// 刷新模板
	void refreshModel(int nIndex);

	// 保存选择的值
	void saveCurSelect(int nSelectTextIndex, int nSelectValue);

private:
	// 模板内容列表
	QList<CSelectText> m_lstSelectText;

	// Model字段数组
	QHash<int, QByteArray>	m_arrRoles;

};

#endif // CMODELSTBCONTENT_H
