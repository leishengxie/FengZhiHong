#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "SqlOperate.h"
#include "DairyHttpClient.h"
#include "NetAppointments.h"

#include <QMessageBox>
#include "crypto/LMd5.h"

CRegisterDialog::CRegisterDialog(QWidget* parent) :
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
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        QMessageBox::information(this, "OK", QString("账号为：%1\n密码：%2\n请记住你的账号和密码！\n").arg(strUserName).arg(strPasswd));
        accept();
    });


    // 使用qt自带 ok
    QByteArray byteArrayMd5 = QCryptographicHash::hash(strPasswd.toLatin1(), QCryptographicHash::Md5);
    QString strPasswdMd5 = byteArrayMd5.toHex().mid(8, 16);	//md5:mid(8, 16) 32位转16位,字符截断, 一般规定取9-25
    qDebug() << strPasswdMd5;

    // 使用std_tool ok
//            strPasswdMd5 = QString(CLMd5(strPasswd.toStdString()).toString().substr(8, 16).c_str());
//            qDebug() << strPasswdMd5;

    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out << strUserName << strPasswdMd5;
    pDairyHttpClient->post(CNetAppointments::urlRegister(), byteArray.data(), byteArray.length());


}
