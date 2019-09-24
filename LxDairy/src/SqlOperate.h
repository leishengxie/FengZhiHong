#ifndef CSQLOPERATE_H
#define CSQLOPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include "Dairy.h"

class CSqlOperate : public QObject
{
    Q_OBJECT
public:
    explicit CSqlOperate(QObject *parent = 0);

    static bool connect(QString strDbName);
    static void createTable();
    static int registerAccount(QString strUserName, QString strPasswd);
    static bool login(QString strUserName, QString strPasswd);
    static CDairy getDairy(int did, bool & bOk);
    ///
    /// \brief getListDairyByDate
    /// \param strFormatDate format"yyyy-MM-dd" eg:"'2019-09'", 2019-09-01, 2019
    /// \return
    ///
    static QList<CDairy> getListDairyByDate(QString strFormatDate);
    static void saveDairy(CDairy dairy);


    QStringList shuaxin(QString registerAccount);
    QStringList huoquqita(QString registerAccount, QString riqi);



    QString wangjimima(QString registerAccount, QString beizhu, QString mima);

    QStringList zhumaintongbu(QString registerAccount);
    void setziti(QString registerAccount, QString ziti);
    void SetXinXi(QString registerAccount, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian);

signals:

public slots:
};

#endif // CSQLOPERATE_H
