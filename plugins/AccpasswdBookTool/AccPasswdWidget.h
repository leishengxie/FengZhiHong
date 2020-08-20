#ifndef ACCPASSWDWIDGET_H
#define ACCPASSWDWIDGET_H

///////////////////////////////////////
/***
 *
 * 应用名称：账号密码簿
 * 是否多用户：是
 * 储存位置：本地, 文件保存
 * 文件加密：是
 * 登录方式: 账号密码
 *
 *
 *
 */
#include <QWidget>

namespace Ui {
class CAccPasswdWidget;
}

class CAccPasswdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CAccPasswdWidget(QWidget *parent = 0);
    ~CAccPasswdWidget();

private slots:
    void on_btnAdd_clicked();

    void on_btnCommit_clicked();

    void on_btnDelete_clicked();

private:
    Ui::CAccPasswdWidget *ui;
};

#endif // ACCPASSWDWIDGET_H
