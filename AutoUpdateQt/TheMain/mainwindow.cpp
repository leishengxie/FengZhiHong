#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

