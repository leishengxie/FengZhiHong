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

CSkinWidget::CSkinWidget(QWidget *parent)
    : QWidget(parent)
  , ui(new Ui::CSkinWidget)
  , m_unIndexSave(0)
  , m_unIndexCur(0)
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
    setSkin(m_unIndexSave);
    close();
}

void CSkinWidget::slot_ok()
{
    setSkin(m_unIndexCur, true);
    close();
}

void CSkinWidget::slot_list_clicked(QListWidgetItem* pItem)
{
    int nCurrenRow = ui->listWidget->currentRow();
    setSkin(nCurrenRow);
}

void CSkinWidget::setSkin(int nSkinIndex, bool bSave)
{
    if (nSkinIndex < 0 || nSkinIndex > 3)
    {
        return;
    }
    m_unIndexCur = nSkinIndex;
    if (bSave)
    {
        m_unIndexSave = m_unIndexCur;
    }
    CGlobalFunc::setQssStyle(s_aSkin[nSkinIndex]);
}
