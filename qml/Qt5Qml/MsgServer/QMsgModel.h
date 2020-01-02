/******************************************************************************
**
** @file
** QMsgModel.h
** @brief
** 消息的Model类
** @author
** leisx
** @date
** 2017-3-21
**
******************************************************************************/
#ifndef QMSGMODEL_H
#define QMSGMODEL_H

#include <QAbstractListModel>

enum E_MsgDriction {
	M_Prev,        // 上一条消息
	M_Next         // 下一条消息
};

struct T_Msg
{
	QString strFrom;
	QString strContent;
	unsigned int type;
	T_Msg()
		: strFrom("")
		, strContent("")
		, type(1)
	{
	}
};

// 单条消息类
class CMsg
{
public:
	CMsg(QString from, QString content, unsigned int type);

	// 消息发送地址
	QString from() const
	{
		return m_strFrom;
	}
	// 消息内容
	QString content() const
	{
		return m_strContent;
	}

	// 消息类型
	unsigned int type() const
	{
		return m_unType;
	}

private:
	QString m_strFrom;
	QString m_strContent;
	unsigned int m_unType;
};


class CMsgModel : public QAbstractListModel
{

	Q_OBJECT

public:
	enum E_Msg {
		M_From,        // 消息发送地址
		M_Content,     // 消息内容
		M_Type         // 消息类型
	};

	CMsgModel(QObject* parent = 0);
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QHash<int, QByteArray> roleNames() const;

public:

	///
	/// @par 功能
	/// 添加一条消息
	/// @param[in] msg - 文件名字符串
	///
	void e_AddMsg(const CMsg& msg);

	///
	/// @par 功能
	/// 获取一条消息
	/// @param[in] eMsgDirection - 上一条或者下一条消息
	/// @param[out] tMsg - 消息内容
	/// @param[in] role - 消息字段
	/// @return 是否成功
	///
	bool e_IsGetDataSuccess(E_MsgDriction eMsgDirection, T_Msg& tMsg, int role = Qt::DisplayRole);

	///
	/// @par 功能
	/// 清空消息
	///
	void e_ClearMsg();

	///
	/// @par 功能
	/// 获取消息队列长度
	/// @return 队列长度
	///
	int e_GetMsgSize();

private:

	// 消息队列
	QList<CMsg> m_lstMsg;

	// 当前消息索引
	int m_nCurIndex;
};

#endif // QMSGMODEL_H
