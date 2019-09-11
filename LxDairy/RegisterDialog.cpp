#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "SqlOperate.h"

#include <QMessageBox>

CRegisterDialog::CRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRegisterDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

CRegisterDialog::~CRegisterDialog()
{
    delete ui;
}

void CRegisterDialog::on_btnOK_clicked()
{
    QString strUserName = ui->leUserName->text();
    QString strPasswd = ui->lePasswd->text();
    QString strPasswdSure = ui->lePasswdSure->text();
    if(strUserName.isEmpty() || strPasswd.isEmpty())
    {
        QMessageBox::information(this, "ERROR", "未填写完整！请全部填写完整");
    }
    else
    {
        if(strPasswd != strPasswdSure)
        {
            QMessageBox::information(this,"ERROR","两次填写密码不一致！请检查重写！！");
        }
        else
        {
          int nResult = CSqlOperate::registerAccount(strUserName, strPasswd);
          QMessageBox::information(this, "OK", QString("账号为：%1\n密码：%2\n").arg(strUserName).arg(strPasswd));
        }
    }
}
