#include "wangjimima.h"
#include "ui_wangjimima.h"
#include"mysql.h"
#include<QMessageBox>
wangjimima::wangjimima(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wangjimima)
{
    ui->setupUi(this);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/1.jpg").scaled(this->size())));
    this->setPalette(pal);
}
wangjimima::~wangjimima()
{
    delete ui;
}

void wangjimima::on_pushButtontijiao_clicked()
{
    QString zhanghao=ui->lineEditzhanghao->text();
    QString beizhu=ui->lineEditbeizhu->text();
    QString mima=ui->lineEditmima->text();
    if(zhanghao.isEmpty()||mima.isEmpty()||beizhu.isEmpty())
    {
       QMessageBox::information(this,"ERROR","未填写完整！请全部填写完整");
    }
    else
    {
    MySql sql;
    QMessageBox::information(this,"结果",sql.wangj imima(zhanghao,beizhu,mima));
    }
}
