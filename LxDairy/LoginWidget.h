#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class CLoginWidget;
}

class CLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CLoginWidget(QWidget *parent = 0);
    ~CLoginWidget();

private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

    void on_ckboxRememberUserName_clicked(bool checked);

    void on_ckboxRememberPasswd_clicked(bool checked);

private:
    Ui::CLoginWidget *ui;
};

#endif // LOGINWIDGET_H
