#include "PrivateMenuModel.h"


CPrivateMenuModel::CPrivateMenuModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setupDefaultData();
}

CPrivateMenuModel::CPrivateMenuModel(int rows, int columns, QObject *parent)
    : QStandardItemModel(rows, columns, parent)
{

}

void CPrivateMenuModel::setupDefaultData()
{
    T_PrivateMenuItem item("密码账号薄", ":/img/account_passwd.png");
    QList<T_PrivateMenuItem> lstPrivateMenuItem;
    lstPrivateMenuItem.append(item);

    for (int i = 0; i < lstPrivateMenuItem.size(); ++i)
    {
        QStandardItem *pItem = new QStandardItem(QIcon(lstPrivateMenuItem.at(i).strIconPath), lstPrivateMenuItem.at(i).strTitle);
        appendRow(pItem);
    }
}
