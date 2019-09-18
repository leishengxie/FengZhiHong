#include "SkinWidget.h"
#include "ui_SkinWidget.h"

#include <QApplication>
#include <QListWidgetItem>
#include <QFile>
#include <QSettings>

#include "GlobalFunc.h"

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
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_saveCurrentSet()));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_list_clicked(QListWidgetItem*)));
    CGlobalFunc::moveToCenter(this);
}

CSkinWidget::~CSkinWidget()
{
    delete ui;
}

void CSkinWidget::loadQssStyle()
{
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    uint unIndex = conf.value("skin_index", 0).toUInt();
    setSkin(unIndex);
}

void CSkinWidget::slot_cancelCurrentSet()
{
    setSkin(m_unIndexSave);
}

void CSkinWidget::slot_saveCurrentSet()
{
    m_unIndexSave = m_unIndexCur;
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    conf.setValue("skin_index", m_unIndexSave);
    close();
}

void CSkinWidget::slot_list_clicked(QListWidgetItem* pItem)
{
    m_unIndexCur = ui->listWidget->currentRow();
    setSkin(m_unIndexCur);
}

void CSkinWidget::setSkin(uint nSkinIndex)
{
    if (nSkinIndex > 3)
    {
        return;
    }
    setQssStyle(s_aSkin[nSkinIndex]);
}

void CSkinWidget::setQssStyle(const QString &stylefilePath)
{
    QFile file(stylefilePath);
    bool bOk = file.open(QFile::ReadOnly);
    if (!bOk)
    {
        return;
    }
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
    file.close();
}

void CSkinWidget::closeEvent(QCloseEvent *event)
{
    slot_cancelCurrentSet();
    QWidget::closeEvent(event);
}
