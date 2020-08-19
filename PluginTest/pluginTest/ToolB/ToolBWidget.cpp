#include "ToolBWidget.h"
#include "ui_ToolBWidget.h"

CToolBWidget::CToolBWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CToolAWidget)
{
    ui->setupUi(this);
}

CToolBWidget::~CToolBWidget()
{
    delete ui;
}
