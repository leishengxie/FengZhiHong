#include "JokebookWidget.h"
#include "ui_JokebookWidget.h"
#include "JokeModel.h"
#include "JokeDelegate.h"

CJokebookWidget::CJokebookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CJokebookWidget)
{
    ui->setupUi(this);

    CJokeModel* pJokeModel = new CJokeModel(this);
    CJokeDelegate* pJokeDelegate = new CJokeDelegate(this);
    ui->tableView->setModel(pJokeModel);
    ui->tableView->setItemDelegate(pJokeDelegate);

    QList<T_Joke> lstJoke;
    T_Joke tJoke;
    tJoke.strTitle = "hello";
    tJoke.dRating = 3.9;
    lstJoke.append(tJoke);
    pJokeModel->setListJoke(lstJoke);
}

CJokebookWidget::~CJokebookWidget()
{
    delete ui;
}
