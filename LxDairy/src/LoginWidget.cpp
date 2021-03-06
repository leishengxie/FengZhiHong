#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "RegisterDialog.h"
#include "SqlOperate.h"
#include "DairyMainWindow.h"
#include <QMessageBox>
#include <QSettings>
#include <QResizeEvent>
#include <QPainter>
#include "SkinWidget.h"
#include "DairyHttpClient.h"
#include "NetAppointments.h"

#include "DairyApp.h"

CLoginWidget::CLoginWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CLoginWidget)
{
    ui->setupUi(this);
    setWindowTitle("登录");
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    bool bRememberUserName = conf.value("remember_user_name", false).toBool();
    bool bRememberPasswd = conf.value("remember_passwd", false).toBool();
    ui->ckboxRememberUserName->setChecked(bRememberUserName);
    ui->ckboxRememberPasswd->setChecked(bRememberPasswd);
    if (ui->ckboxRememberUserName->isChecked())
    {
        QString strUserName = conf.value("user_name", "").toString();
        ui->leUserName->setText(strUserName);
    }
    if (ui->ckboxRememberPasswd->isChecked())
    {
        QString strPasswd = conf.value("passwd", "").toString();
        ui->lePasswd->setText(strPasswd);
    }

    m_pixBg = CSkinWidget::currentBackgroundPixmap();
    // 谨慎使用，20191201 会应用到子对象， 从而导致子对象每次show时都会使用，导致界面刷新卡顿
//    QPalette pal;
//    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
//    setPalette(pal);
}

CLoginWidget::~CLoginWidget()
{
    delete ui;
}

void CLoginWidget::onBgPixmapChanged(const QPixmap & pixmap)
{
    m_pixBg = pixmap;
}

void CLoginWidget::on_btnRegister_clicked()
{
    //CRegisterDialog* pRegisterDialog = new CRegisterDialog();
    //pRegisterDialog->exec();
    CRegisterDialog registerDialog(this);
    if (!m_pixBg.isNull())
    {
        QPalette pal;
        pal.setBrush(QPalette::Background, QBrush(m_pixBg.scaled(registerDialog.size())));
        registerDialog.setPalette(pal);
    }
    if (registerDialog.exec() == QDialog::Accepted)
    {

    }
}



void CLoginWidget::on_ckboxRememberUserName_clicked(bool checked)
{
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    conf.setValue("remember_user_name", checked);
}

void CLoginWidget::on_ckboxRememberPasswd_clicked(bool checked)
{
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    conf.setValue("remember_passwd", checked);
}

void CLoginWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    if (m_pixBg.isNull())
    {
        return;
    }
    QPainter painter(this);
    painter.drawPixmap(rect(), m_pixBg);

    //
//        QPixmap *pm_back_buffer = new QPixmap("images/main.png");
//        QBitmap *pm_mask = new QBitmap("images/main_mask.png");
//        // 设置檬板图片；
//        setMask(*pm_mask);


}

void CLoginWidget::resizeEvent(QResizeEvent* event)
{
    // 大图片谨慎使用，20191201 会应用到子对象， 从而导致子对象每次show时都会使用，导致界面刷新卡顿
//    QPalette pal;
//    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    //    setPalette(pal);
}

void CLoginWidget::testUrlDump()
{
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    // 此处为什么不能识别父类的finished???
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [=](QByteArray byteArray)
    {
        qDebug() << byteArray;
    });

    qDebug() <<CNetAppointments::urlTest();
    pDairyHttpClient->get(CNetAppointments::urlTest());
}

void CLoginWidget::on_btnLoginServer_clicked()
{
    // test
//    testUrlDump();
//    return;

    //
    QString strUserName = ui->leUserName->text();
    QString strPasswd = ui->lePasswd->text();
    if (strUserName.isEmpty())
    {
        QMessageBox::information(this, "提示", "请输入用户名！");
        return;
    }
    if (strPasswd.isEmpty())
    {
        QMessageBox::information(this, "提示", "请输入密码！");
        return;
    }

    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    // 此处为什么不能识别父类的finished???
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [=](QByteArray byteArray)
    {
        QSettings conf("conf.ini", QSettings::IniFormat);
        conf.beginGroup("user");
        if (ui->ckboxRememberUserName->isChecked())
        {
            conf.setValue("user_name", strUserName);
        }
        if (ui->ckboxRememberPasswd->isChecked())
        {
            conf.setValue("passwd", strPasswd);
        }
        T_UserInfo tUserInfo = CNetAppointments::deserialization<T_UserInfo>(byteArray);
        CDairyApp::setUserInfo(tUserInfo);

        CDairyMainWindow* pDairyMainWindow = new CDairyMainWindow;
        pDairyMainWindow->setLoginWidget(this);
        pDairyMainWindow->show();
        close();
    });

    QByteArray byteArrayMd5 = QCryptographicHash::hash(strPasswd.toLatin1(), QCryptographicHash::Md5);
    QString strPasswdMd5 = byteArrayMd5.toHex().mid(8, 16);	//md5:mid(8, 16) 32位转16位,字符截断, 一般规定取9-25

    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out << strUserName << strPasswdMd5;
    pDairyHttpClient->post(CNetAppointments::urlLogin(), byteArray.data(), byteArray.length());




}
