#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include "PluginsManger.h"
#include "Plugin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setViewMode(QListView::IconMode);
    //删除stackedWidget所有子窗口
    for(int i = ui->stackedWidget->count(); i >= 0; i--)
    {
        QWidget* widget = ui->stackedWidget->widget(i);
        ui->stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }
    loadPlugins();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPlugins()
{
    QList<IPlugin*> lstPlugin = CPluginsManger::getInstance()->loadPlugins();
    foreach (IPlugin* pPlugin, lstPlugin)
    {
        QListWidgetItem* item = new QListWidgetItem(pPlugin->icon(), pPlugin->name());
        ui->listWidget->addItem(item);
        //QStandardItem *pItem = new QStandardItem(pPlugin->icon(), pPlugin->name());
        //ui->listWidget->model()->appendRow(pItem);
        ui->stackedWidget->addWidget(pPlugin->widget());
    }

}


void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(index.row());
}
