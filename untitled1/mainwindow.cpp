#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"writerj.h"
#include"mysql.h"
#include<QListWidgetItem>
#include<QFontDialog>
#include<QDebug>
#include"peizhijiemian.h"
CDairyMainWindow::CDairyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DairyMainWindow)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeroutshow()));
    timer->start(2000);
    ui->listWidget->setStyleSheet("background-color:transparent");
    ui->textBrowser->setStyleSheet("background-color:transparent");
    ui->menuBar->setStyleSheet("background-color:transparent");
}
void CDairyMainWindow::timeroutshow()
{
   on_actionshuxin_triggered();//刷新
   QPalette pal;
   pal.setBrush(QPalette::Background,QBrush(QPixmap(pix).scaled(this->size())));
   this->setPalette(pal);
   ui->labelgeqian->setToolTip("个性签名："+geqian);
   ui->labelwangming->setToolTip("网名："+wangming);
   ui->labelzhanghao->setToolTip("账号："+ui->labelzhanghao->text());
}
CDairyMainWindow::~CDairyMainWindow()
{
    delete ui;
}
void CDairyMainWindow::SetZhanghao(QString zhanghao)
{
    ui->labelzhanghao->setText(zhanghao);
    MySql sql;
    QStringList list=sql.zhumaintongbu(zhanghao);
if(list.length()==5)
{
    ui->labelwangming->setText(list.at(0));
    wangming=list.at(0);
    ui->labelgeqian->setText(list.at(1));
    geqian=list.at(1);
    ui->labeltouxiang->setPixmap(QPixmap(list.at(2)).scaled(ui->labeltouxiang->size()));
    touxiang=list.at(2);
    if(font.fromString(list.at(3)))
    this->setFont(font);
    pix=list.at(4);
    ui->menu->setStyleSheet(QString("background-image:url(%1)").arg(pix));

    ui->listWidget->setFont(font);
    ui->textBrowser->setFont(font);
    ui->menuBar->setFont(font);
    timeroutshow();
}
}
void CDairyMainWindow::on_actionxieriji_triggered()//写日记
{
  Writerj *write=new Writerj;

  write->writeinit(ui->labelzhanghao->text(),font,pix);
  write->exec();
}

void CDairyMainWindow::on_actionshuxin_triggered()//刷新
{
    ui->listWidget->clear();
    MySql sql;
    QStringList list;
    list=sql.shuaxin(ui->labelzhanghao->text());
    ui->listWidget->addItems(list);
}

void CDairyMainWindow::on_listWidget_itemClicked(QListWidgetItem *item)//点击ITEM
{
   QString riqi=item->text();
   MySql sql;
   QStringList list=sql.huoquqita(ui->labelzhanghao->text(),riqi);
   ui->labeltianqi1->setText(list.at(0));
   ui->labelxinqing1->setText(list.at(1));
   ui->textBrowser->setPlainText(list.at(2));
}
void CDairyMainWindow::on_actionpeizhi_triggered()//配置
{
    Peizhijiemian *pz=new Peizhijiemian;
    pz->PeiZhiInit(font,pix,touxiang,wangming,geqian);
    connect(pz,SIGNAL(BaoCun(QFont,QString,QString,QString,QString)),this,
            SLOT(huoqu(QFont,QString,QString,QString,QString)));
    pz->move(this->pos());
    pz->exec();
}

void CDairyMainWindow::huoqu(QFont font1,QString beijing, QString touxiang1, QString wangming1, QString geqian1)
{
   font=font1;
   pix=beijing;
   touxiang=touxiang1;
   wangming=wangming1;
   geqian=geqian1;
   ui->menu->setStyleSheet(QString("background-image:url(%1)").arg(pix));
   ui->listWidget->setFont(font);
   ui->textBrowser->setFont(font);
   ui->menuBar->setFont(font);

   ui->labelgeqian->setText(geqian);
   ui->labelwangming->setText(wangming);
   ui->labeltouxiang->setPixmap(QPixmap(touxiang).scaled(ui->labeltouxiang->size()));
   MySql sql;
   sql.SetXinXi(ui->labelzhanghao->text(),font1.toString(),beijing,touxiang,wangming,geqian);
}
#include<QMessageBox>
void CDairyMainWindow::on_actionguanyu_triggered()
{
   QMessageBox::information(this,"关于","软件名： Qt超级日记本\n"
                                       "创作人： 梦飞翔\n"
                                       "创作时间：2018.06.05\n"
                                       "版本号： V_1.1\n"
                                       "版权所有，盗版必究\n"
                                       "技术漏洞或更多要求请在下方留言\n");
}
