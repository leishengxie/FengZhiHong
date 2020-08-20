#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "delegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        ui->tableWidget->setItemDelegate(new Delegate());
        ui->tableWidget->setHorizontalHeaderLabels(
                QStringList() << tr("Track") << tr("Duration"));
        ui->tableWidget->setRowCount(2);
        ui->tableWidget->setColumnCount(2);
        for (int row = 0; row < 2; ++row) {
                QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(row));
                ui->tableWidget->setItem(row, 0, item0);
                QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(row));
                item1->setTextAlignment(Qt::AlignRight);
                ui->tableWidget->setItem(row, 1, item1);
            }

}

MainWindow::~MainWindow()
{
    delete ui;
}
