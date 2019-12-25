#include "JokeModel.h"



CJokeModel::CJokeModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    m_strlstHeader.clear();
    m_strlstHeader << "标题" << "上传者" << "上传日期" << "内容" << "平均分";
}

int CJokeModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_lstJoke.count();
}

int CJokeModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_strlstHeader.size();
}

QVariant CJokeModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() < 0 || index.row() >= m_lstJoke.count())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    T_Joke tJoke = m_lstJoke.at(index.row());
    QVariant variant;
    variant.setValue(tJoke);
    return variant;

}

QVariant CJokeModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(role == Qt::TextAlignmentRole)
    {
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if(orientation == Qt::Horizontal)
    {
        return m_strlstHeader.at(section);
    }

    return QAbstractTableModel::headerData(section,orientation,role);

//    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
//            return m_header[section];
//        return QAbstractTableModel::headerData(section,orientation,role);

}

Qt::ItemFlags CJokeModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    if (index.column() == 3)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }

    Qt::ItemFlags flag = QAbstractTableModel::flags(index);

    return  flag;
}

void CJokeModel::setListJoke(const QList<T_Joke> & lstJoke)
{
    beginResetModel();
    m_lstJoke = lstJoke;
    endResetModel();
}

void CJokeModel::appendListJoke(const QList<T_Joke> &lstJoke)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + lstJoke.count());
    m_lstJoke.append(lstJoke);
    endInsertRows();
}

void CJokeModel::clear()
{
    beginResetModel();
    m_lstJoke.clear();
    endResetModel();
}
