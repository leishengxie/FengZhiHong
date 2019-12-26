#include "JokebookWidget.h"
#include "ui_JokebookWidget.h"
#include "JokeModel.h"
#include "JokeDelegate.h"
#include "JokeEditor.h"

#include <QDateTime>
#include <QNetworkReply>
#include <QMessageBox>
#include <QScrollBar>

#include "DairyHttpClient.h"
#include "NetAppointments.h"
#include "User.h"


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
    //ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView->verticalHeader()->setDefaultSectionSize(ITEM_HEIGHT_LIST);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->tableView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));


    m_pJokeEditor = new CJokeEditor();
    connect(m_pJokeEditor, SIGNAL(requreUploadJoke(T_Joke)), this, SLOT(requestUploadJoke(T_Joke)));
    connect(ui->starEditor, SIGNAL(editingFinished(qreal)), this, SLOT(onStarEidtFinished(qreal)));

}

CJokebookWidget::~CJokebookWidget()
{
    delete ui;
}

void CJokebookWidget::saveJoke(const T_Joke & tJoke)
{

}

void CJokebookWidget::requestUploadJoke(const T_Joke & tJoke)
{

//    qDebug() << "uploadJoke:" << tJoke.strDate << tJoke.strTitle;
//    QNetworkRequest request(CNetAppointments::urlUploadJoke());
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    QNetworkReply* pNetworkReply = m_networkAccessManager.post(request, CNetAppointments::serializa(tJoke));
//    connect(pNetworkReply, SIGNAL(finished()), this, SLOT(onRespUploadJokeFinished()));
    // 20191225 使用自己封装的http
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [=](QByteArray byteArray)
    {
        qDebug() << "onRespUploadJokeFinished:" << byteArray;
        requestJokeList(m_tJokeListRequest);
    });
    pDairyHttpClient->post(CNetAppointments::urlUploadJoke(), CNetAppointments::serializa(tJoke));

}

///
/// \brief CJokebookWidget::requestJokeList
/// \param tJokeListRequest
/// \param bAppend  是否追加到现有列表，否则清除现有列表
///
void CJokebookWidget::requestJokeList(const T_JokeListRequest & tJokeListRequest, bool bAppend)
{
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [=](QByteArray byteArray)
    {
        m_tJokeListResp = CNetAppointments::deserialization<T_JokeListResp>(byteArray);
        if (bAppend)
        {
            m_pJokeModel->appendListJoke(m_tJokeListResp.listJoke);
        }
        else
        {
            m_pJokeModel->setListJoke(m_tJokeListResp.listJoke);
        }
    });
    pDairyHttpClient->post(CNetAppointments::urlJokeList(), CNetAppointments::serializa(tJokeListRequest));
}

void CJokebookWidget::onRespUploadJoke(const QByteArray & data)
{

}

//void CJokebookWidget::onRespUploadJokeFinished()
//{
//    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
//    QByteArray data = pNetworkReply->readAll();

//    int status_code = pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//    QVariant variant = pNetworkReply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
//    QByteArray byteArray = variant.toString().toLatin1();
//    QString status_text = QString::fromUtf8(byteArray);


//    if (status_code == 200)
//    {
//       qDebug() << "onRespUploadJokeFinished:" << data;
//    }
//    else
//    {
//        QMessageBox::information(this, QString::number(status_code), status_text);
//    }

//    pNetworkReply->deleteLater();
//    pNetworkReply = NULL;

//}

void CJokebookWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    m_tJokeListRequest.reset();
    requestJokeList(m_tJokeListRequest);
}

void CJokebookWidget::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
    //ui->tableView->model()->cl
    m_pJokeModel->clear();
    ui->textBrowser->clear();
}


void CJokebookWidget::on_comboBox_currentIndexChanged(int index)
{
    Q_ASSERT(index < 3);
    m_tJokeListRequest.nSelectType = index;
    requestJokeList(m_tJokeListRequest);
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

void CJokebookWidget::onStarEidtFinished(qreal dRating)
{
    QModelIndex index = ui->tableView->currentIndex();
    T_Joke tJoke = qvariant_cast<T_Joke>(index.data());
    T_JokeRating tJokeRating;
    tJokeRating.jId = tJoke.jId;
    tJokeRating.uId = CUser::getInstance()->getUserInfo().uid;
    tJokeRating.dRating = dRating;
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [=](QByteArray byteArray)
    {

    });
    pDairyHttpClient->post(CNetAppointments::urlJokeRating(), CNetAppointments::serializa(tJokeRating));
}

void CJokebookWidget::onScrollBarValueChanged(int nValue)
{
    if (nValue == ui->tableView->verticalScrollBar()->maximum())
    {
        int nListCount = ui->tableView->model()->rowCount();

        if (nListCount >= m_tJokeListResp.nTotalItems)
        {
            return;
        }
        ++m_tJokeListRequest.nPageIndex;
        requestJokeList(m_tJokeListRequest, true);
    }
}

void CJokebookWidget::onHttpRequestFinished(const QByteArray & data)
{

}
