#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString str = "很好";
    QByteArray byteArray = str.toUtf8();
    QString str2 = QString::fromUtf8(byteArray);
    qDebug() <<str2;
}

MainWindow::~MainWindow()
{
    delete ui;
}
