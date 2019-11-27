#include "CollectionWidget.h"
#include "ui_CollectionWidget.h"

CCollectionWidget::CCollectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCollectionWidget)
{
    ui->setupUi(this);
}

CCollectionWidget::~CCollectionWidget()
{
    delete ui;
}
