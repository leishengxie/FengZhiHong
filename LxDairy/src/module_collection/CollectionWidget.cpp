#include "CollectionWidget.h"
#include "ui_CollectionWidget.h"
#include "CollectionDelegate.h"
#include "CollectionModel.h"

#include "ArticleModel.h"
#include "ArticleSortFilterProxyModel.h"
#include "ArticleDelegate.h"
#include "ArticleEditor.h"

#include <QDateTime>
#include <QNetworkReply>
#include <QMessageBox>
#include <QScrollBar>

#include "DairyHttpClient.h"
#include "NetAppointments.h"
#include "DairyApp.h"
#include "LToast.h"
#include "ArticleModel.h"

#include <QHeaderView>

CCollectionWidget::CCollectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCollectionWidget)
{
    ui->setupUi(this);

    CCollectionDelegate* pCollectionDelegate = new CCollectionDelegate();
    CCollectionModel* pCollectionModel = new CCollectionModel(this);
    ui->listView->setModel(pCollectionModel);
    ui->listView->setItemDelegate(pCollectionDelegate);

    // tableview set
    m_pJokeModel = new CArticleModel(this);
    m_pProxyModel = new CArticleSortFilterProxyModel;
    m_pProxyModel->setSourceModel(m_pJokeModel);
    CArticleDelegate* pJokeDelegate = new CArticleDelegate(this);
    ui->tableView->setModel(m_pProxyModel);
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
    QItemSelectionModel* pItemSelectionModel = ui->tableView->selectionModel();
    connect(pItemSelectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this, SLOT(onSelectionChanged(QItemSelection, QItemSelection)));

    m_pJokeEditor = new CArticleEditor(this, Qt::Window);
    connect(m_pJokeEditor, SIGNAL(requreUploadJoke(T_Article)), this, SLOT(requestUploadJoke(T_Article)));
    connect(ui->starEditor, SIGNAL(editingFinished(qreal)), this, SLOT(onStarEidtFinished(qreal)));
}

CCollectionWidget::~CCollectionWidget()
{
    delete ui;
}




void CCollectionWidget::saveJoke(const T_Article & tJoke)
{

}

void CCollectionWidget::requestUploadJoke(const T_Article & tJoke)
{

//    qDebug() << "uploadJoke:" << tJoke.strDate << tJoke.strTitle;
//    QNetworkRequest request(CNetAppointments::urlUploadJoke());
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    QNetworkReply* pNetworkReply = m_networkAccessManager.post(request, CNetAppointments::serializa(tJoke));
//    connect(pNetworkReply, SIGNAL(finished()), this, SLOT(onRespUploadJokeFinished()));
    // 20191225 使用自己封装的http
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        qDebug() << "onRespUploadJokeFinished:" << byteArray;
        m_tJokeListRequest.nPageIndex = 1;
        requestJokeList(m_tJokeListRequest);
    });
    pDairyHttpClient->post(CNetAppointments::urlArticleUpload(), CNetAppointments::serializa(tJoke));

}

///
/// \brief CCollectionWidget::requestJokeList
/// \param tJokeListRequest
/// \param bAppend  是否追加到现有列表，否则清除现有列表
///
void CCollectionWidget::requestJokeList(const T_ArticleListRequest & tJokeListRequest, bool bAppend)
{
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        m_tJokeListResp = CNetAppointments::deserialization<T_ArticleListResp>(byteArray);
        if (bAppend)
        {
            m_pJokeModel->appendListJoke(m_tJokeListResp.listArticle);
        }
        else
        {
            // beginResetModel()  -- When a model is reset it means that any previous data reported from the model is now invalid
            //and has to be queried for again. This also means that the current item and any selected items will become invalid.
            // 根据官方介绍所有视图selected items 无效
            ui->tableView->selectionModel()->clearSelection();
            m_pJokeModel->setListJoke(m_tJokeListResp.listArticle);
        }
    });
    pDairyHttpClient->post(CNetAppointments::urlArticleList(), CNetAppointments::serializa(tJokeListRequest));
}

void CCollectionWidget::onRespUploadJoke(const QByteArray & data)
{

}

//void CCollectionWidget::onRespUploadJokeFinished()
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

void CCollectionWidget::showEvent(QShowEvent* event)
{
    Q_UNUSED(event)
    m_tJokeListRequest.reset();
    requestJokeList(m_tJokeListRequest);
}

void CCollectionWidget::hideEvent(QHideEvent* event)
{
    Q_UNUSED(event)
    //ui->tableView->model()->cl
    m_pJokeModel->clear();
    ui->textBrowser->clear();
}


void CCollectionWidget::on_comboBox_currentIndexChanged(int index)
{
    Q_ASSERT(index < ES_Max);

    // 后台整理
    m_tJokeListRequest.uId = CDairyApp::userInfo().uid;
    m_tJokeListRequest.nSelectType = index;
    m_tJokeListRequest.nPageIndex = 1;
    requestJokeList(m_tJokeListRequest);

    // ok, 本地整理 -- 利：减轻后台压力， 弊:因为是分页请求导致未请求的没有加载上
//    switch (E_SelectType(index))
//    {
//    case ES_SelectByWorld:
//        m_pProxyModel->setSortFilterUid(-1);
//        break;
//    case ES_SelectByMyUpload:
//        m_pProxyModel->setSortFilterUid(CDairyApp::userInfo().uid);
//        break;
//    default:
//        break;
//    }

}


void CCollectionWidget::on_btnAdd_clicked()
{
    m_pJokeEditor->show();
}

void CCollectionWidget::on_tableView_clicked(const QModelIndex & index)
{

    ui->textBrowser->clear();
    T_Article tJoke = qvariant_cast<T_Article>(index.data());
    ui->textBrowser->append(QString("标题: %1").arg(tJoke.strTitle));
    ui->textBrowser->append(QString("日期: %1").arg(tJoke.strDate));
    ui->textBrowser->append(QString("上传作者昵称: %1").arg(tJoke.strNickname));
    ui->textBrowser->append(QString("资源类型: %1").arg(tJoke.bOriginal ? "原创" : "其他"));
    ui->textBrowser->append(QString("评价总人数: %1").arg(tJoke.llRatingNumOfPeople));
    ui->textBrowser->append(QString("评价总评分: %1").arg(tJoke.dRatingToatalScore));
    ui->textBrowser->append(QString("评价平均评分: %1\n").arg(tJoke.dRatingAverageScore));
    ui->textBrowser->append("***************************************");
    ui->textBrowser->append("   " + tJoke.strContent);
    ui->starEditor->setRating(tJoke.dRatingAverageScore);
}

void CCollectionWidget::onStarEidtFinished(qreal dRating)
{
    QItemSelectionModel* pItemSelectionModel = ui->tableView->selectionModel();
    QModelIndexList IndexList = pItemSelectionModel->selectedIndexes();
    if (IndexList.isEmpty())
    {
        ui->starEditor->setRating(0);
        CLToast::showStr(this, "请先选择一则笑话！");
        return;
    }
    T_Article tJoke = qvariant_cast<T_Article>(IndexList.at(0).data());
    T_ArticleRating tJokeRating;
    tJokeRating.jId = tJoke.jId;
    tJokeRating.uId = CDairyApp::userInfo().uid;
    tJokeRating.dRating = dRating;
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        qDebug() << "joke rating finished:" << byteArray;
        m_tJokeListRequest.nPageIndex = 1;
        requestJokeList(m_tJokeListRequest);
    });
    pDairyHttpClient->post(CNetAppointments::urlArticleRating(), CNetAppointments::serializa(tJokeRating));
}

void CCollectionWidget::onSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{

    QItemSelectionModel* pItemSelectionModel = ui->tableView->selectionModel();
    QModelIndexList IndexList = pItemSelectionModel->selectedIndexes();
    qDebug() << "onSelectionChanged" << IndexList.size();
    if (IndexList.isEmpty())
    {
        ui->starEditor->setRating(0);
        ui->textBrowser->clear();
        return;
    }

    QModelIndexList realList;
    foreach (QModelIndex index, IndexList)
    {
        if (index.column() != 0)
        {
            continue;
        }
        realList.append(index);
    }
    if (realList.size() > 1)
    {
        ui->starEditor->setRating(0);
        ui->textBrowser->clear();
        return;
    }
    QModelIndex index = realList.at(0);
    on_tableView_clicked(index);
}

void CCollectionWidget::onScrollBarValueChanged(int nValue)
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

void CCollectionWidget::onHttpRequestFinished(const QByteArray & data)
{

}
