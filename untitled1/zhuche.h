#ifndef ZHUCHE_H
#define ZHUCHE_H

#include <QDialog>

namespace Ui {
class zhuche;
}

class zhuche : public QDialog
{
    Q_OBJECT

public:
    explicit zhuche(QWidget *parent = 0);
    ~zhuche();

private slots:
    void on_pushButtontijiao_clicked();

    void on_pushButton_clicked();

private:
    Ui::zhuche *ui;
};

#endif // ZHUCHE_H
