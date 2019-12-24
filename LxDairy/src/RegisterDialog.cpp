#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "SqlOperate.h"
#include "DairyHttpClient.h"
#include "NetAppointments.h"

#include <QMessageBox>

CRegisterDialog::CRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRegisterDialog)
{
    ui->setupUi(this);
    setWindowTitle("注册");

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
        return;
    }
    else
    {
        if(strPasswd != strPasswdSure)
        {
            QMessageBox::information(this, "ERROR", "两次填写密码不一致！请检查重写！！");
            return;
        }
        else
        {
          int nResult = CSqlOperate::registerAccount(strUserName, strPasswd);
          if (nResult == 1)
          {
              QMessageBox::information(this, "ERROR", "该用户名已经被注册！！");
              return;
          }
          if (nResult == 2)
          {
              QMessageBox::information(this, "ERROR", "sql语句错误！！");
              return;
          }
          QMessageBox::information(this, "OK", QString("账号为：%1\n密码：%2\n请记住你的账号和密码！\n").arg(strUserName).arg(strPasswd));
          accept();
        }
    }
}

void CRegisterDialog::on_btnRegister_clicked()
{
    QString strUserName = ui->leUserName->text();
    QString strPasswd = ui->lePasswd->text();
    QString strPasswdSure = ui->lePasswdSure->text();
    if(strUserName.isEmpty() || strPasswd.isEmpty())
    {
        QMessageBox::information(this, "ERROR", "未填写完整！请全部填写完整");
        return;
    }
    else
    {
        if(strPasswd != strPasswdSure)
        {
            QMessageBox::information(this, "ERROR", "两次填写密码不一致！请检查重写！！");
            return;
        }
    }

    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [=]()
    {
        QMessageBox::information(this, "OK", QString("账号为：%1\n密码：%2\n请记住你的账号和密码！\n").arg(strUserName).arg(strPasswd));
        accept();
    });
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out << strUserName << strPasswd;
    pDairyHttpClient->post(CNetAppointments::urlRegister(), byteArray.data(), byteArray.length());


}
