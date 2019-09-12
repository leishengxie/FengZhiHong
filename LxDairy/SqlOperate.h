#ifndef CSQLOPERATE_H
#define CSQLOPERATE_H

#include <QObject>
#include <QSqlDatabase>

class CSqlOperate : public QObject
{
    Q_OBJECT
public:
    explicit CSqlOperate(QObject *parent = 0);

    static bool connect(QString strDbName);
    static void createTable();

    bool WriteData(QString registerAccount, QString time, QString wather, QString xinqing, QString neirong);
    QStringList shuaxin(QString registerAccount);
    QStringList huoquqita(QString registerAccount, QString riqi);

    static int registerAccount(QString strUserName, QString strPasswd);

    QString wangjimima(QString registerAccount, QString beizhu, QString mima);
    static bool login(QString strUserName, QString strPasswd);
    QStringList zhumaintongbu(QString registerAccount);
    void setziti(QString registerAccount, QString ziti);
    void SetXinXi(QString registerAccount, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian);

signals:

public slots:
};

#endif // CSQLOPERATE_H
