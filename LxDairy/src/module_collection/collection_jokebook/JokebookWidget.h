#ifndef JOKEBOOKWIDGET_H
#define JOKEBOOKWIDGET_H

#include <QWidget>
//#include <QNetworkAccessManager>
#include "JokeModel.h"

namespace Ui {
class CJokebookWidget;
}

class CJokeEditor;

class CJokebookWidget : public QWidget
{
    Q_OBJECT

public:


    explicit CJokebookWidget(QWidget *parent = 0);
    ~CJokebookWidget();


public slots:
    void saveJoke(const T_Joke & tJoke);
    void requestUploadJoke(const T_Joke & tJoke);
    void requestJokeList(const T_JokeListRequest &tJokeListRequest, bool bAppend = false);

    void onRespUploadJoke(const QByteArray& data);
    //void onRespUploadJokeFinished();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_btnAdd_clicked();


    void on_tableView_clicked(const QModelIndex &index);

    // 滚动条事件
    void onScrollBarValueChanged(int nValue);

private slots:
    void onHttpRequestFinished(const QByteArray& data);

private:
    Ui::CJokebookWidget *ui;

    CJokeModel* m_pJokeModel;
    CJokeEditor* m_pJokeEditor;

    //QNetworkAccessManager m_networkAccessManager;

    T_JokeListRequest m_tJokeListRequest;
    T_JokeListResp m_tJokeListResp;
};

#endif // JOKEBOOKWIDGET_H
