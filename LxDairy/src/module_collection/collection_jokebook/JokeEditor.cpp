#include "JokeEditor.h"
#include "ui_JokeEditor.h"

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
