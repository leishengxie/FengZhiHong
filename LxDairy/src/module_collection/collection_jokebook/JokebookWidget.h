#ifndef JOKEBOOKWIDGET_H
#define JOKEBOOKWIDGET_H

#include <QWidget>
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
public:
    void saveJoke(const T_Joke & tJoke);
    void uploadJoke(const T_Joke & tJoke);

private slots:
    void on_comboBox_activated(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_btnUpload_clicked();

    void on_btnAdd_clicked();


    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::CJokebookWidget *ui;

    CJokeModel* m_pJokeModel;
    CJokeEditor* m_pJokeEditor;
};

#endif // JOKEBOOKWIDGET_H
