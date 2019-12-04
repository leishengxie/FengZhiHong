#include "CollectionWidget.h"
#include "ui_CollectionWidget.h"
#include "CollectionDelegate.h"
#include "CollectionModel.h"

#include <QHeaderView>

CCollectionWidget::CCollectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCollectionWidget)
{
    ui->setupUi(this);

    CCollectionDelegate* pCollectionDelegate = new CCollectionDelegate();
    CCollectionModel* pCollectionModel = new CCollectionModel(this);
    ui->listView->setModel(pCollectionModel);
    ui->listView->setItemDelegate(pCollectionDelegate);

}

CCollectionWidget::~CCollectionWidget()
{
    delete ui;
}
