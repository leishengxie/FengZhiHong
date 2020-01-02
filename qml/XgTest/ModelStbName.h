/******************************************************************************
**
** @file
** ModelStbName.h
** @brief
** 机顶盒模板名列表Model
** @par
** 未处理C++异常
** @author
** leisx
** @date
** 2017-5-10
**
******************************************************************************/

#ifndef CMODELSTBNAME_H
#define CMODELSTBNAME_H

#include <QAbstractListModel>
#include <QtDebug>
#include "ModuleManager.h"


class CModelStbName : public QAbstractListModel
{
	Q_OBJECT

	enum E_ModelField {
		EMF_Name,		// 模板名称
		EMF_Readonly,	// 是否是只读的
		EMF_AttachedName,
		EMF_IsChecked
	};


public:
	explicit CModelStbName(QObject *parent = 0);

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

public slots:
	void check(int nIndex);

	void checkAll(bool bChecked);

	void seachfor(QString strKeyWord);

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
	QList<CTemplate> m_lstTempate;

};

#endif // CMODELSTBNAME_H
