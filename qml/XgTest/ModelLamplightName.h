/******************************************************************************
**
** @file
** ModelLamplightName.h
** @brief
** 灯光效果模板名列表Model
** @par
** 未处理C++异常
** @author
** leisx
** @date
** 2017-5-4
**
******************************************************************************/
#ifndef CMODELLAMPLIGHTNAME_H
#define CMODELLAMPLIGHTNAME_H

#include <QAbstractListModel>
#include "ModuleManager.h"


class CModelLamplightName : public QAbstractListModel
{
	Q_OBJECT

	enum E_ModelField {
		EMF_Name,		// 模板名称
		EMF_Readonly	// 是否是只读的
	};

public slots:

	//响应刷新
	void refresh();

	//请求删除
	void requireDeleteTemplate(int nIndex);

	//请求设置
	void requireSet();

	//请求添加
	void requireAddTemplate(QString strTemplateName);

public:
	explicit CModelLamplightName(QObject *parent = 0);

	// 系统重载函数，返回字段名称数组
	QHash<int, QByteArray> roleNames() const override
	{
		return m_arrRoles;

	}

	// 系统重载函数，获取记录行数
	int rowCount(const QModelIndex &/*parent = QModelIndex()*/) const override
	{
		return i_GetTempCount();
	}

	// 系统重载函数，获取字段值
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

	///
	/// @par 功能
	/// 获取模板数目
	/// @return - 模板数目
	///
	int i_GetTempCount() const;

private:

	// Model字段数组
	QHash<int, QByteArray>	m_arrRoles;

	// 模板名称列表，测试用途
	QList<QString> m_arrTempName;

};

#endif // CMODELLAMPLIGHTNAME_H
