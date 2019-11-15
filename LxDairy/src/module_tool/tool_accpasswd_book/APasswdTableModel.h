#ifndef CAPASSWDTABLEMODEL_H
#define CAPASSWDTABLEMODEL_H

#include <QAbstractTableModel>

struct T_ApasswdItem
{
    QString strItemName;
    QString strAccount;
    QString strPasswd;
};

class CAPasswdTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CAPasswdTableModel(QObject *parent = 0);

private:
    QList<T_ApasswdItem> m_lstApasswdItem;
};

#endif // CAPASSWDTABLEMODEL_H
