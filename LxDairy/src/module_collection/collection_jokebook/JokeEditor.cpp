#include "JokeEditor.h"
#include "ui_JokeEditor.h"

#include <QDateTime>
#include "DairyApp.h"

CJokeEditor::CJokeEditor(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
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
    tJoke.upUid = CDairyApp::userInfo().uid;
    tJoke.strNickname = CDairyApp::userInfo().strNickName;
    emit requreUploadJoke(tJoke);
    close();
}

void CJokeEditor::on_btnCancel_clicked()
{
    close();
}
