#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LBookListModel.h"

#include <QStandardItemModel>
#include <QListWidget>
#include <QStyle>

#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CLBookListModel* pBookListModel = new CLBookListModel();
    ui->listView->setViewMode(QListView::IconMode);

    //ui->listView->setLayoutMode(QListView::Batched);
    //ui->listView->setBatchSize(3);


    ui->listView->setModel(pBookListModel);

    //QStandardItemModel m;
    //QStandardItem item;

    //QListWidget
    //QStyle style;

    //QCheckBox chbox;

    ///Qt技巧
    //设置控件隐藏时占位
    QSizePolicy policy = ui->listView->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    ui->listView->setSizePolicy(policy);

    //setFcous最好放在showEvent()函数里才生效

}

MainWindow::~MainWindow()
{
    delete ui;
}


