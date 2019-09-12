#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "RegisterDialog.h"
#include "SqlOperate.h"
#include "DairyMainWindow.h"

#include <QSettings>

CLoginWidget::CLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLoginWidget)
{
    ui->setupUi(this);

    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    QString strUserName = conf.value("user_name", "").toString();
    ui->leUserName->setText(strUserName);
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    setPalette(pal);
}

CLoginWidget::~CLoginWidget()
{
    delete ui;
}

void CLoginWidget::on_btnRegister_clicked()
{
  //CRegisterDialog* pRegisterDialog = new CRegisterDialog();
  //pRegisterDialog->exec();
    CRegisterDialog registerDialog;
    if (registerDialog.exec() == QDialog::Accepted)
    {

    }
}

void CLoginWidget::on_btnLogin_clicked()
{
    QString strUserName = ui->leUserName->text();
    QString strPasswd = ui->lePasswd->text();
    if (strUserName.isEmpty())
    {
        QMessageBox::information(this, "提示" ,"请输入用户名！");
        return;
    }
    if (strPasswd.isEmpty())
    {
        QMessageBox::information(this, "提示" ,"请输入密码！");
        return;
    }
    if(CSqlOperate::login(strUserName, strPasswd))
    {
        QSettings conf("conf.ini", QSettings::IniFormat);
        conf.beginGroup("user");
        conf.setValue("user_name", strUserName);

       CDairyMainWindow *pDairyMainWindow = new CDairyMainWindow;
       pDairyMainWindow->setLoginWidget(this);
       //pDairyMainWindow->SetZhanghao(ui->lineEditzanghao->currentText());
       pDairyMainWindow->show();
       close();
    }
    else
    {
        QMessageBox::information(this, "ERROR" ,"账号或密码不正确！！");
    }
}
