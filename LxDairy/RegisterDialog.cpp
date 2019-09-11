#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"

CRegisterDialog::CRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRegisterDialog)
{
    ui->setupUi(this);
}

CRegisterDialog::~CRegisterDialog()
{
    delete ui;
}
