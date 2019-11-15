#ifndef CPRIVATEMENUMODEL_H
#define CPRIVATEMENUMODEL_H

#include <QStandardItemModel>

struct T_PrivateMenuItem
{
    QString strTitle;
    QString strIconPath;

    T_PrivateMenuItem(QString strTitle, QString strIconPath)
        : strTitle(strTitle)
        , strIconPath(strIconPath)
    {

    }
};

///
/// \brief The CPrivateMenuModel class
/// QStandardItemModel是不包含数据的，需要向QStandardItemModel插入数据
///
class CPrivateMenuModel : public QStandardItemModel
{
public:
    explicit CPrivateMenuModel(QObject *parent = Q_NULLPTR);
    CPrivateMenuModel(int rows, int columns, QObject *parent = Q_NULLPTR);

private:
    void setupDefaultData();
};

#endif // CPRIVATEMENUMODEL_H
