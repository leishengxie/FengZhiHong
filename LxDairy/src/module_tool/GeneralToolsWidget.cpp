#include "GeneralToolsWidget.h"
#include "ui_GeneralToolsWidget.h"
#include "tool_rename/RenameWidget.h"
#include "tool_accpasswd_book/AccPasswdWidget.h"

CGeneralToolsWidget::CGeneralToolsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGeneralToolsWidget)
{
    ui->setupUi(this);

    ui->listWidgetPrivate->setIconSize(QSize(64,64));
    ui->listWidgetPrivate->setGridSize(QSize(96,96));

    //ui->listWidgetPrivate->setResizeMode(QListView::Adjust); //设置QListView大小改变时，图标的调整模式，默认是固定的，但可以改成自动调整：
//    CPrivateMenuModel *pModel = new CPrivateMenuModel(this);
//    ui->listViewPrivate->setModel(pModel);
//    ui->listViewPrivate->setViewMode(QListView::IconMode);
    // 此处用listWidget替代listView

    CAccPasswdWidget* pAccPasswdWidget = new CAccPasswdWidget(ui->stackedWidgetTool);
    ui->stackedWidgetTool->addWidget(pAccPasswdWidget);
    //connect(ui->action_save, SIGNAL(toggled(bool))

    CRenameWidget* pRenameWidget = new CRenameWidget(ui->stackedWidgetTool);
    ui->stackedWidgetTool->addWidget(pRenameWidget);

    QWidget* pWidget = new QWidget(ui->stackedWidgetTool);
    ui->stackedWidgetTool->addWidget(pWidget);
}

CGeneralToolsWidget::~CGeneralToolsWidget()
{
    delete ui;
}

void CGeneralToolsWidget::on_listWidgetPrivate_clicked(const QModelIndex &index)
{
    ui->stackedWidgetTool->setCurrentIndex(index.row());
}
