#include "ToolAWidget.h"
#include "ui_ToolAWidget.h"

CToolAWidget::CToolAWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CToolAWidget)
{
    ui->setupUi(this);
}

CToolAWidget::~CToolAWidget()
{
    delete ui;
}
