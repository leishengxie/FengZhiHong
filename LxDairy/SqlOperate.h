#ifndef CSQLOPERATE_H
#define CSQLOPERATE_H

#include <QObject>

class CSqlOperate : public QObject
{
    Q_OBJECT
public:
    explicit CSqlOperate(QObject *parent = 0);

    bool WriteData(QString zhanghao, QString time, QString wather, QString xinqing, QString neirong);
    QStringList shuaxin(QString zhanghao);
    QStringList huoquqita(QString zhanghao, QString riqi);
    int zhanghao(QString mima,QString beizhu,QString wangming,QString qianming,QString touxiang);
    QString wangjimima(QString zhanghao,QString beizhu,QString mima);
    bool yanzheng(QString zhanghao,QString mima);
    QStringList zhumaintongbu(QString zhanghao);
    void setziti(QString zhanghao,QString ziti);
    void SetXinXi(QString zhanghao, QString ziti, QString beijing, QString touxiang, QString wangming, QString geqian);

signals:

public slots:
};

#endif // CSQLOPERATE_H
