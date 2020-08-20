#include "inputagedlg.h"
#include "ui_inputagedlg.h"
# pragma execution_character_set("utf-8")
InputAgeDlg::InputAgeDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputAgeDlg)
{
    ui->setupUi(this);
    QStringList age_unit={tr("岁"),tr("月"),tr("天"),tr("小时")};
    ui->ageunitbox->addItems(age_unit);
    ui->ageedit->setValidator(new QRegExpValidator(QRegExp("[0-9.]+$")));   //只能输入数字
}
InputAgeDlg::~InputAgeDlg()
{
    delete ui;
}
QString InputAgeDlg::getage()
{
    return ui->ageedit->text();
}
QString InputAgeDlg::getage_unit()
{
    return ui->ageunitbox->currentText();
}
void InputAgeDlg::set_Age(const QString &a)
{
    ui->ageedit->setText(a);
}
void InputAgeDlg::set_age_uint(const QString &u)
{
    ui->ageunitbox->setCurrentText(u);
}
void InputAgeDlg::on_ageedit_editingFinished()
{
   age=ui->ageedit->text();
   age_uint=ui->ageunitbox->currentText();
}
void InputAgeDlg::on_ageunitbox_currentIndexChanged(const QString &arg1)
{
    age=ui->ageedit->text();
    age_uint=arg1;
}
