#include "writerj.h"
#include "ui_writerj.h"
#include"mysql.h"
#include<QMessageBox>
#include<QDebug>
Writerj::Writerj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Writerj)
{
    ui->setupUi(this);
    QStringList list,list1;
    list<<"晴"<<"多云"<<"阴"<<"阵雨"<<"雷阵雨"<<"雷阵雨伴有冰雹"<<"小雨"<<"中雨"
        <<"大雨"<<"暴雨"<<"大暴雨"<<"特大暴雨"<<"小到中雨"<<"中到大雨"<<"大到暴雨"
        <<"暴雨到大暴雨"<<"大暴雨到特大暴雨"<<"雨夹雪"<<"阵雪"<<"小雪"<<"中雪"<<"大雪"
        <<"暴雪"<<"小到中雪"<<"中到大雪"<<"大到暴雪"<<"雾"<<"浓雾"<<"强浓雾"<<"霜"
        <<"冻雨"<<"沙尘暴"<<"浮尘"<<"扬沙"<<"沙尘暴"<<"强沙尘暴"<<"特强沙尘暴轻雾"
        <<"轻微霾"<<"轻度霾"<<"中度霾"<<"重度霾"<<"特强霾"<<"霰"<<"飑线";
    list1<<"喜"<<"怒"<<"哀"<<"乐";
    ui->comboBox->addItems(list);
    ui->comboBox1->addItems(list1);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeoutshow()));
    timer->start(1000);
  }
void Writerj::writeinit(QString zh, QFont f,QString pix)//初始化
{
   zhanghao=zh;
   this->setFont(f);
   pix1=pix;
   timeoutshow();
   ui->textEdit->setStyleSheet("background-color:transparent");
   ui->comboBox->setStyleSheet(QString("background-image:url(%1)").arg(pix1));
   ui->comboBox1->setStyleSheet(QString("background-image:url(%1)").arg(pix1));
   ui->textEdit->setFont(f);
   ui->comboBox->setFont(f);
   ui->comboBox1->setFont(f);
}
void Writerj::timeoutshow()
{
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(pix1).scaled(this->size())));
    this->setPalette(pal);
}
Writerj::~Writerj()
{
    delete ui;
}

void Writerj::on_pushButton_clicked()//保存
{
QString rq=ui->dateTimeEdit->text();
QString tq=ui->comboBox->currentText();
QString xq=ui->comboBox1->currentText();
QString rj=ui->textEdit->toPlainText();
if(rj.isEmpty())
{
    QMessageBox::information(this,"未填写内容","未填写日记内容！请填写！！！");
    return;
}
MySql sql;
qDebug()<<zhanghao;
bool ok=sql.WriteData(zhanghao,rq,tq,xq,rj);
if(ok)
{
  QMessageBox::information(this,"OK","保存成功！");
}
else
{
    QMessageBox::information(this,"ERROR","保存失败！请尝试再次保存");
}
}
