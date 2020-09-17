#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QRadioButton>
//#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QRadioButton radio;
//    QButtonGroup group;
}

MainWindow::~MainWindow()
{
    delete ui;
}

