#include "denglv.h"
#include "ui_denglv.h"
#include"zhuche.h"
#include"wangjimima.h"
#include"mysql.h"
#include"mainwindow.h"
#include<QMessageBox>
#include<QCoreApplication>
#include<QDir>
#include<QDebug>
denglv::denglv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::denglv)
{
    ui->setupUi(this);
    QString path=QCoreApplication::applicationDirPath()+"/file/";
    ui->lineEditzanghao->addItems(filenameInDir(path));
    //ui->lineEditmima->setEchoMode(QLineEdit::PasswordEchoOnEdit);//输入时显示数字，失去焦点时显示圆点
    ui->lineEditmima->setEchoMode(QLineEdit::Password);//输入时显示数字，失去焦点时显示圆点
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/1.jpg").scaled(this->size())));
    this->setPalette(pal);
    ui->lineEditmima->setStyleSheet("background-color:transparent;border-width:1;border:2px groove blue;border-radius:10px;padding:2px 4px;border-style:outset");
    ui->lineEditzanghao->setStyleSheet("background-color:transparent;border-width:1;border:2px groove blue;border-radius:10px;padding:2px 4px;border-style:outset");
    ui->pushButtondenglv->setStyleSheet("background-color:transparent;border-width:1;border:2px groove blue;border-radius:10px;padding:2px 4px;border-style:outset");
    //ui->lineEditzanghao->setStyleSheet("background-color:transparent");

}
QStringList denglv::filenameInDir(QString path)
{
    QStringList string_list;

    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        return string_list;
    }
    //查看路径中后缀为.png格式的文件
    QStringList filters;
    filters<<QString("*.png");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式
    //统计png格式的文件个数
    int dir_count = dir.count();
    if(dir_count <= 0)
    return string_list;
   //存储文件名称
    for(int i=0; i<dir_count; i++)
    {
        QString file_name = dir[i];  //文件名称
        QFileInfo fileinfo;
        fileinfo = QFileInfo(path+file_name);
        string_list<<fileinfo.baseName();
    }
    return string_list;
}
denglv::~denglv()
{
    delete ui;
}

void denglv::on_pushButtonzhuce_clicked()//注册账号
{
zhuche *zhuche1=new zhuche;
zhuche1->exec();
}

void denglv::on_pushButtonxiugai_clicked()//修改密码
{
wangjimima *wanji=new wangjimima;
wanji->exec();
}

void denglv::on_pushButtondenglv_clicked()//登录
{
    QString zhanghao=ui->lineEditzanghao->currentText();
    QString mima=ui->lineEditmima->text();
    MySql sql;
    if(sql.yanzheng(zhanghao,mima))
    {
       CDairyMainWindow *mainzhu=new CDairyMainWindow;
       mainzhu->SetZhanghao(ui->lineEditzanghao->currentText());
       mainzhu->show();
       this->close();/////////////////////////////////////
    }
    else
    {
        QMessageBox::information(this,"ERROR","账号或密码不正确！！");
    }
}
void denglv::on_lineEditzanghao_currentTextChanged(const QString &arg1)
{
    QString path=QCoreApplication::applicationDirPath()+"/file";
    QString tupian=path+QString("/%1.png").arg(arg1);
    ui->labeltouxiang->setPixmap(QPixmap(tupian).scaled(ui->labeltouxiang->size()));
}
