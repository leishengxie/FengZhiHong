#include "zhuche.h"
#include "ui_zhuche.h"
#include"mysql.h"
zhuche::zhuche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zhuche)
{
    ui->setupUi(this);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/1.jpg").scaled(this->size())));
    this->setPalette(pal);
}

zhuche::~zhuche()
{
    delete ui;
}
#include<QMessageBox>
void zhuche::on_pushButtontijiao_clicked()//提交
{
    QString touxiang=ui->labeltouxiangweizhi->text()
            ,mima=ui->lineEditmima->text(),
            qrmm=ui->lineEditquerenmima->text(),
            beizhu=ui->lineEditbeizhu->text(),
            wangming=ui->lineEditwangming->text(),
            geqian=ui->lineEditgexingqianming->text();
    if(touxiang.isEmpty()||mima.isEmpty()||qrmm.isEmpty()||beizhu.isEmpty()||wangming.isEmpty()||geqian.isEmpty())
    {
        QMessageBox::information(this,"ERROR","未填写完整！请全部填写完整");
    }
    else
    {
        if(mima!=qrmm)
        {
            QMessageBox::information(this,"ERROR","两次填写密码不一致！请检查重写！！");
        }
        else
        {
           MySql sql;
          int zhanghao=sql.zhanghao(mima,beizhu,wangming,geqian,touxiang);
          QMessageBox::information(this,"OK",QString("账号为：%1\n密码：%2\n备注为：%3\n").arg(zhanghao).arg(mima).arg(beizhu));
        }

    }

}
#include<QFileDialog>
void zhuche::on_pushButton_clicked()//头像
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home",
                                                     tr("Images (*.png *.xpm *.jpg)"));
    if(!fileName.isEmpty())
    {
        ui->labeltouxiangweizhi->setText(fileName);
        ui->labeltouxiang->setPixmap(QPixmap(fileName).scaled(ui->labeltouxiang->size()));
    }
}
