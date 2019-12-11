#include "JokeEditor.h"
#include "ui_JokeEditor.h"
#include "JokeModel.h"
#include <QDateTime>
#include "User.h"

CJokeEditor::CJokeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CJokeEditor)
{
    ui->setupUi(this);
}

CJokeEditor::~CJokeEditor()
{
    delete ui;
}

void CJokeEditor::on_btnSave_clicked()
{
    T_Joke tJoke;
    tJoke.strTitle = ui->leTitle->text();
    tJoke.strDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    tJoke.bOriginal = (ui->combSource->currentIndex() == 1);
    tJoke.strContent = ui->plainTextEdit->document()->toPlainText();
    tJoke.upUid = CUser::getInstance()->getUid();
    tJoke.strNickname = CUser::getInstance()->getUserName();

}

void CJokeEditor::on_btnUpload_clicked()
{

}

void CJokeEditor::on_btnCancel_clicked()
{
    close();
}
