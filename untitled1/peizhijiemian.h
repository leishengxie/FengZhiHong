#ifndef PEIZHIJIEMIAN_H
#define PEIZHIJIEMIAN_H

#include <QDialog>

namespace Ui {
class Peizhijiemian;
}

class Peizhijiemian : public QDialog
{
    Q_OBJECT
signals:
    void BaoCun(QFont,QString,QString,QString,QString);
public:
    explicit Peizhijiemian(QWidget *parent = 0);
    ~Peizhijiemian();
    void PeiZhiInit(QFont font1, QString beijing, QString touxiang, QString wangming, QString geqian);

private slots:
    void on_pushButtonxzt_clicked();

    void on_pushButtonxuantu_clicked();

    void on_pushButtonbc_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Peizhijiemian *ui;
    QFont font;
    QStringList bjlist;
    QString bj;
};

#endif // PEIZHIJIEMIAN_H
