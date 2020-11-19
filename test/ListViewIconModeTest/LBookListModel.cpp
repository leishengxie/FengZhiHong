#include "LBookListModel.h"

//QModelIndex CBookListModel::index(int row, int column, const QModelIndex &parent) const
//{

//}

CLBookListModel::CLBookListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_listBook << T_Book("语文", 40) << T_Book("数学", 42) << T_Book("英语", 48) << T_Book("科学", 35);
}

CLBookListModel::~CLBookListModel()
{

}

int CLBookListModel::rowCount(const QModelIndex &parent) const
{
    //int mod = m_listBook.size() % 3;
    //return m_listBook.size() / 3 + (mod == 0 ? 0 : 1);
    return m_listBook.size();
}

QVariant CLBookListModel::data(const QModelIndex &index, int role) const
{
    /// 虽然在QListView::IconMode列表展示看起来有多列，但是index.column()始终是1列
    int i = index.row();// * 3 + index.column();
    if(i >= m_listBook.size())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        return m_listBook.at(i).strName;
    }
    return QVariant();
}
