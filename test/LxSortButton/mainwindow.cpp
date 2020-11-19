#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "LSortButton.h"
//#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QVBoxLayout* vLay = new QVBoxLayout;
//    CLSortButton* btn = new CLSortButton(QPixmap(":/img/ascending.jpg"), QPixmap(":/img/descending.jpg"), this);
//    vLay->addWidget(btn);
//    centralWidget()->setLayout(vLay);
    ui->widget->setPixmap(QPixmap(":/img/ascending.jpg"), QPixmap(":/img/descending.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

