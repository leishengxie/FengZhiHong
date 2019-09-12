#include "SkinWidget.h"
#include "ui_SkinWidget.h"
#include "GlobalFunc.h"

#include <QListWidgetItem>

static QString s_aSkin[] =
{
    ":/css/black.css",
    ":/css/blue.css",
    ":/css/gray.css",
    ":/css/navy.css"
};

CSkinWidget::CSkinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSkinWidget)
{
    ui->setupUi(this);
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slot_cancel()));
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_list_clicked(QListWidgetItem*)));
    CGlobalFunc::moveToCenter(this);
}

CSkinWidget::~CSkinWidget()
{
    delete ui;
}

void CSkinWidget::slot_cancel()
{

}

void CSkinWidget::slot_ok()
{

}

void CSkinWidget::slot_list_clicked(QListWidgetItem* pItem)
{
    QString text = pItem->text();
    int nCurrenRow = ui->listWidget->currentRow();
    setSkin(nCurrenRow);
}

void CSkinWidget::setSkin(int nSkinIndex)
{
    if (nSkinIndex < 0 || nSkinIndex > 3)
    {
        return;
    }
    CGlobalFunc::setQssStyle(s_aSkin[nSkinIndex]);
}
