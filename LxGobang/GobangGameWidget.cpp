#include "GobangGameWidget.h"
#include "ui_GobangGameWidget.h"

CGobangGameWidget::CGobangGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CGobangGameWidget)
{
    ui->setupUi(this);
}

CGobangGameWidget::~CGobangGameWidget()
{
    delete ui;
}

