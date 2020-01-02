#include "QMsgModel.h"



CMsg::CMsg(QString from, QString content, unsigned int type)
	: m_strFrom(from)
	, m_strContent(content)
	, m_unType(type)
{

}



CMsgModel::CMsgModel(QObject* parent)
	: QAbstractListModel(parent)
	, m_nCurIndex(-1)
{

}

void CMsgModel::e_AddMsg(const CMsg &msg)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_lstMsg << msg;
	++m_nCurIndex;
	endInsertRows();
}

int CMsgModel::rowCount(const QModelIndex& parent) const
{
	return m_lstMsg.count();
}

QVariant CMsgModel::data(const QModelIndex& index, int role) const
{
	if (index.row() < 0 || index.row() > m_lstMsg.count())
	{
		return QVariant();
	}

	const CMsg& msg = m_lstMsg[index.row()];

	if (M_From == role)
	{
		return msg.from();
	}
	else if (M_Content == role)
	{
		return msg.content();
	}
	else if (M_Type == role)
	{
		return msg.type();
	}
	return QVariant();
}

bool CMsgModel::e_IsGetDataSuccess(E_MsgDriction eMsgDirection, T_Msg& tMsg, int role)
{
	if (M_Prev == eMsgDirection && m_nCurIndex > 0)
	{
		tMsg.strFrom = m_lstMsg[--m_nCurIndex].from();
		tMsg.strContent = m_lstMsg[m_nCurIndex].content();
		return true;
	}
	else if (M_Next == eMsgDirection  && m_nCurIndex < m_lstMsg.count() - 1)
	{
		tMsg.strFrom = m_lstMsg[++m_nCurIndex].from();
		tMsg.strContent = m_lstMsg[m_nCurIndex].content();
		return true;
	}
	return false;
}

QHash<int, QByteArray> CMsgModel::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[M_From]  = "from";
	roles[M_Content]  = "content";
	roles[M_Type] = "type";
	return roles;
}

void CMsgModel::e_ClearMsg()
{
	if (0 != m_lstMsg.count())
	{
		beginResetModel();
		m_lstMsg.clear();
		endResetModel();
	}
}

int CMsgModel::e_GetMsgSize()
{
	return m_lstMsg.size();
}
