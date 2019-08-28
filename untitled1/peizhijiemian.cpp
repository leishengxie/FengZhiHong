#include "peizhijiemian.h"
#include "ui_peizhijiemian.h"
#include<QFont>
#include<QFontDialog>
#include<QFileDialog>
Peizhijiemian::Peizhijiemian(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peizhijiemian)
{
    ui->setupUi(this);
    bjlist<<":/image/1.jpg"<<":/image/2.jpg"<<":/image/3.jpg"<<":/image/4.jpg"<<":/image/5.jpg"<<":/image/6.jpg";
}

Peizhijiemian::~Peizhijiemian()
{
    delete ui;
}

void Peizhijiemian::on_pushButtonxzt_clicked()
{
    bool ok=false;
    QFont font1 = QFontDialog::getFont(
                      &ok, QFont("Helvetica [Cronyx]", 10), this);
      if (ok) {
            font=font1;
            ui->lineEditziti->setText(font.toString());
  }
      else {

      }
}

void Peizhijiemian::on_pushButtonxuantu_clicked()//选择头像
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home",
                                                     tr("Images (*.png *.xpm *.jpg)"));
    if(!fileName.isEmpty())
    {
        ui->labeltuweizhi->setText(fileName);
        ui->labeltx->setPixmap(QPixmap(fileName).scaled(ui->labeltx->size()));
    }
}

void Peizhijiemian::on_pushButtonbc_clicked()//发送信号
{
     QString f=ui->lineEditziti->text(),
             tx=ui->labeltuweizhi->text(),
             wangming=ui->lineEditwm->text(),
             geqian=ui->lineEditgq->text();
     if(f.isEmpty()||tx.isEmpty()||wangming.isEmpty()||geqian.isEmpty())
     {
       //提示有空白
         return;
     }
     else
     {
         //发送信号 字体 背景 头像位置 网名 个签
     emit BaoCun(font,bj,tx,wangming,geqian);
     }
    this->close();
}
void Peizhijiemian::PeiZhiInit(QFont font1,QString beijing, QString touxiang, QString wangming, QString geqian)
{
    ui->lineEditziti->setText(font1.toString());
    font=font1;
    if(beijing==bjlist.at(0)) ui->comboBox->setCurrentIndex(0);
    if(beijing==bjlist.at(1)) ui->comboBox->setCurrentIndex(1);
    if(beijing==bjlist.at(2)) ui->comboBox->setCurrentIndex(2);
    if(beijing==bjlist.at(3)) ui->comboBox->setCurrentIndex(3);
    if(beijing==bjlist.at(4)) ui->comboBox->setCurrentIndex(4);
    if(beijing==bjlist.at(5)) ui->comboBox->setCurrentIndex(5);

    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(beijing).scaled(this->size())));
    this->setPalette(pal);
    bj=beijing;
    ui->labeltuweizhi->setText(touxiang);
    ui->labeltx->setPixmap(QPixmap(touxiang).scaled(ui->labeltx->size()));
    ui->lineEditwm->setText(wangming);
    ui->lineEditgq->setText(geqian);
}

void Peizhijiemian::on_comboBox_currentIndexChanged(int index)//背景
{
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(bjlist.at(index)).scaled(this->size())));
    this->setPalette(pal);
    bj=bjlist.at(index);
}
