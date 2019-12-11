#include "JokebookWidget.h"
#include "ui_JokebookWidget.h"
#include "JokeModel.h"
#include "JokeDelegate.h"
#include "JokeEditor.h"
#include <QDateTime>

#include "LHttpClient.h"

CJokebookWidget::CJokebookWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CJokebookWidget)
{
    ui->setupUi(this);

    // tableview set
    m_pJokeModel = new CJokeModel(this);
    CJokeDelegate* pJokeDelegate = new CJokeDelegate(this);
    ui->tableView->setModel(m_pJokeModel);
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
    m_pJokeModel->setListJoke(lstJoke);

    m_pJokeEditor = new CJokeEditor();
}

CJokebookWidget::~CJokebookWidget()
{
    delete ui;
}

void CJokebookWidget::saveJoke(const T_Joke & tJoke)
{

}

void CJokebookWidget::uploadJoke(const T_Joke & tJoke)
{

}

void CJokebookWidget::on_comboBox_activated(int index)
{

}

void CJokebookWidget::on_comboBox_currentIndexChanged(int index)
{

}

void CJokebookWidget::on_btnUpload_clicked()
{
    T_Joke tJoke = qvariant_cast<T_Joke>(index.data());
    uploadJoke(tJoke);
}

void CJokebookWidget::on_btnAdd_clicked()
{
    m_pJokeEditor->show();
}

void CJokebookWidget::on_tableView_clicked(const QModelIndex & index)
{

    ui->textBrowser->clear();
    T_Joke tJoke = qvariant_cast<T_Joke>(index.data());
    ui->textBrowser->append(QString("标题: %1").arg(tJoke.strTitle));
    ui->textBrowser->append(QString("日期: %1").arg(tJoke.strDate));
    ui->textBrowser->append(QString("上传作者昵称: %1").arg(tJoke.strNickname));
    ui->textBrowser->append(QString("资源类型: %1").arg(tJoke.bOriginal ? "原创" : "其他"));
    ui->textBrowser->append(QString("评价总人数: %1").arg(tJoke.llRatingNumOfPeople));
    ui->textBrowser->append(QString("评价总评分: %1").arg(tJoke.dRatingToatalScore));
    ui->textBrowser->append(QString("评价平均评分: %1\n").arg(tJoke.dRatingAverageScore));
    ui->textBrowser->append("***************************************");
    ui->textBrowser->append("   " + tJoke.strContent);
}
