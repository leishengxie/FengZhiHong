#ifndef JOKEBOOKWIDGET_H
#define JOKEBOOKWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include "JokeModel.h"

namespace Ui {
class CJokebookWidget;
}

class CJokeEditor;

class CJokebookWidget : public QWidget
{
    Q_OBJECT

public:
    enum E_SelectType
    {
        ES_World,
        ES_Penfriend,
        ES_MyUpload,
        ES_MyLocal
    };

    explicit CJokebookWidget(QWidget *parent = 0);
    ~CJokebookWidget();
public:
    void saveJoke(const T_Joke & tJoke);
    void uploadJoke(const T_Joke & tJoke);
public slots:
    void onRespUploadJoke(const QByteArray& data);
    void onRespUploadJokeFinished();

private slots:
    void on_comboBox_activated(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_btnUpload_clicked();

    void on_btnAdd_clicked();


    void on_tableView_clicked(const QModelIndex &index);

private slots:
    void onHttpRequestFinished(const QByteArray& data);

private:
    Ui::CJokebookWidget *ui;

    CJokeModel* m_pJokeModel;
    CJokeEditor* m_pJokeEditor;

    QNetworkAccessManager m_networkAccessManager;
};

#endif // JOKEBOOKWIDGET_H
