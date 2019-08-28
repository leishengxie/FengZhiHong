#ifndef WANGJIMIMA_H
#define WANGJIMIMA_H

#include <QDialog>

namespace Ui {
class wangjimima;
}

class wangjimima : public QDialog
{
    Q_OBJECT

public:
    explicit wangjimima(QWidget *parent = 0);
    ~wangjimima();

private slots:
    void on_pushButtontijiao_clicked();

private:
    Ui::wangjimima *ui;
};

#endif // WANGJIMIMA_H
