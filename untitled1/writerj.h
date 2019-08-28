#ifndef WRITERJ_H
#define WRITERJ_H

#include <QDialog>
#include<QTimer>
namespace Ui {
class Writerj;
}

class Writerj : public QDialog
{
    Q_OBJECT

public:
    explicit Writerj(QWidget *parent = 0);
    ~Writerj();
    void writeinit(QString zh, QFont f, QString pix);//初始化
    QString zhanghao;
private slots:
    void on_pushButton_clicked();
    void timeoutshow();
private:
    Ui::Writerj *ui;
    QTimer *timer;
    QString pix1;
};

#endif // WRITERJ_H
