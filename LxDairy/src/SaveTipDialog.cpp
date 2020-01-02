#include "SaveTipDialog.h"
#include "ui_SaveTipDialog.h"

CSaveTipDialog::CSaveTipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSaveTipDialog)
{
    ui->setupUi(this);
}

CSaveTipDialog::~CSaveTipDialog()
{
    delete ui;
}
