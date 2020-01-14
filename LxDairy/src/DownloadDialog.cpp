#include "DownloadDialog.h"
#include "ui_DownloadDialog.h"

CDownloadDialog::CDownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDownloadDialog)
{
    ui->setupUi(this);
}

CDownloadDialog::~CDownloadDialog()
{
    delete ui;
}
