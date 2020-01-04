#ifndef CSQLOPERATE_H
#define CSQLOPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include "Dairy.h"
#include "UserInfo.h"

///
/// \brief The CSqlOperate class 断网情况临时保存数据到本地sqlite数据库
///
class CSqlOperate : public QObject
{
    Q_OBJECT
public:
    explicit CSqlOperate(QObject *parent = 0);

    static bool connect(QString strDbName);

    static void createTable();


    static QList<T_Dairy> getDairyList(int uid);
    static bool saveDairy(const T_Dairy & dairyModify, T_Dairy & dairySaved, QString & sreError);


    static void SetXinXi(QString registerAccount, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian);
    static void test();
signals:

public slots:
};

#endif // CSQLOPERATE_H
