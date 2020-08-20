#include "GeneralToolsWidget.h"
#include "ui_GeneralToolsWidget.h"
#include "PluginsManger.h"
#include "Plugin.h"

CGeneralToolsWidget::CGeneralToolsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGeneralToolsWidget)
{
    ui->setupUi(this);

    // 由于加载后列表就不会修改，所以用QListWidget + QListWidgetItem就行了
    ui->listWidget->setIconSize(QSize(64,64));
    ui->listWidget->setGridSize(QSize(96,96));
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

CGeneralToolsWidget::~CGeneralToolsWidget()
{
    delete ui;
}

void CGeneralToolsWidget::on_listWidgetPrivate_clicked(const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(index.row());
}

void CGeneralToolsWidget::loadPlugins()
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
