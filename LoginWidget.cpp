#include "LoginWidget.h"
#include "ui_LoginWidget.h"

CLoginWidget::CLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLoginWidget)
{
    ui->setupUi(this);
}

CLoginWidget::~CLoginWidget()
{
    delete ui;
}
