#include "DairyEditWidget.h"
#include "ui_DairyEditWidget.h"

CDairyEditWidget::CDairyEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDairyEditWidget)
{
    ui->setupUi(this);
}

CDairyEditWidget::CDairyEditWidget(CDairy dairy, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDairyEditWidget)
{

    QString strDateTime = dairy.getDateTime();
    QDateTime datetime = QDateTime::fromString(strDateTime, FORMAT_DATETIME);
    QString strDateTimeDisplay = datetime.toString(FORMAT_DATETIME_DISPLAYER);
    did = dairy.getDid();
    ui->comboBoxWeather->setCurrentText(dairy.getWeather());
    ui->comboBoxTag->setCurrentText(dairy.getTag());
    ui->labelDateTime->setText(strDateTimeDisplay);
    ui->leTitle->setText(dairy.getTitle());
    ui->dairyEdit->setPlainText(dairy.getContent());
}

CDairyEditWidget::~CDairyEditWidget()
{
    delete ui;
}
