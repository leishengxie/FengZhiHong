#include "JokeEditor.h"
#include "ui_JokeEditor.h"

#include <QDateTime>
#include "DairyApp.h"

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


void CJokeEditor::on_btnUpload_clicked()
{
    T_Joke tJoke;
    tJoke.strTitle = ui->leTitle->text();
    tJoke.strDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    tJoke.bOriginal = (ui->combSource->currentIndex() == 1 ? true : false);
    tJoke.strContent = ui->plainTextEdit->document()->toPlainText();
    tJoke.upUid = CDairyApp::userInfoNet().uid;
    tJoke.strNickname = CDairyApp::userInfoNet().strNickName;
    emit requreUploadJoke(tJoke);
    close();
}

void CJokeEditor::on_btnCancel_clicked()
{
    close();
}
