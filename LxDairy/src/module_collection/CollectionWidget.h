#ifndef COLLECTIONWIDGET_H
#define COLLECTIONWIDGET_H

#include <QWidget>
//#include <QNetworkAccessManager>
#include "ArticleModel.h"
#include <QItemSelectionModel>

class CArticleSortFilterProxyModel;
class CArticleEditor;
class CArticleModel;

namespace Ui {
class CCollectionWidget;
}

///
/// \brief The CCollectionWidget class  集-主界面
///
class CCollectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CCollectionWidget(QWidget *parent = 0);
    ~CCollectionWidget();

public slots:
    void saveJoke(const T_Article & tJoke);
    void requestUploadJoke(const T_Article & tJoke);
    void requestJokeList(const T_ArticleListRequest &tJokeListRequest, bool bAppend = false);

    void onRespUploadJoke(const QByteArray& data);
    //void onRespUploadJokeFinished();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_btnAdd_clicked();


    void on_tableView_clicked(const QModelIndex &index);

    void onStarEidtFinished(qreal dRating);

    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    // 滚动条事件
    void onScrollBarValueChanged(int nValue);

private slots:
    void onHttpRequestFinished(const QByteArray& data);

private:
    Ui::CCollectionWidget *ui;



    CArticleModel* m_pJokeModel;
    CArticleSortFilterProxyModel* m_pProxyModel;
    CArticleEditor* m_pJokeEditor;

    //QNetworkAccessManager m_networkAccessManager;

    T_ArticleListRequest m_tJokeListRequest;
    T_ArticleListResp m_tJokeListResp;
};

#endif // COLLECTIONWIDGET_H
