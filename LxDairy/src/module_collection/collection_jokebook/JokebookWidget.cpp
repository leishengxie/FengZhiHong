#include "JokebookWidget.h"
#include "ui_JokebookWidget.h"
#include "JokeModel.h"
#include "JokeDelegate.h"
#include <QDateTime>

CJokebookWidget::CJokebookWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CJokebookWidget)
{
    ui->setupUi(this);

    // tableview set
    CJokeModel* pJokeModel = new CJokeModel(this);
    CJokeDelegate* pJokeDelegate = new CJokeDelegate(this);
    ui->tableView->setModel(pJokeModel);
    ui->tableView->setItemDelegate(pJokeDelegate);
    ui->tableView->setShowGrid(false);
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView->verticalHeader()->setDefaultSectionSize(ITEM_HEIGHT_LIST);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QList<T_Joke> lstJoke;
    T_Joke tJoke;
    tJoke.strTitle = "hello";
    tJoke.strDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    tJoke.strContent = "abcdefffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
    tJoke.dRatingAverageScore = 3.9;
    lstJoke.append(tJoke);
    pJokeModel->setListJoke(lstJoke);
}

CJokebookWidget::~CJokebookWidget()
{
    delete ui;
}
