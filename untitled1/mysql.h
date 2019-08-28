#ifndef MYSQL_H
#define MYSQL_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>

class MySql
{
public:
    MySql();
    bool WriteData(QString zhanghao, QString time, QString wather, QString xinqing, QString neirong);
    QStringList shuaxin(QString zhanghao);
    QStringList huoquqita(QString zhanghao, QString riqi);
    int zhanghao(QString mima,QString beizhu,QString wangming,QString qianming,QString touxiang);
    QString wangjimima(QString zhanghao,QString beizhu,QString mima);
    bool yanzheng(QString zhanghao,QString mima);
    QStringList zhumaintongbu(QString zhanghao);
    void setziti(QString zhanghao,QString ziti);
    void SetXinXi(QString zhanghao, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian);


};

#endif // MYSQL_H
