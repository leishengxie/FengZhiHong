#include "GeneralToolsWidget.h"
#include "ui_GeneralToolsWidget.h"
#include "tool_rename/RenameWidget.h"
#include "tool_accpasswd_book/AccPasswdWidget.h"

CGeneralToolsWidget::CGeneralToolsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGeneralToolsWidget)
{
    ui->setupUi(this);

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
