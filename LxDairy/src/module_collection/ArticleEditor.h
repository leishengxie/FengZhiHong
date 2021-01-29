#ifndef JOKEEDITOR_H
#define JOKEEDITOR_H

#include <QWidget>
#include "Joke.h"

namespace Ui {
class CArticleEditor;
}


///
/// \brief The CArticleEditor class 文章编辑器
///
class CArticleEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CArticleEditor(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
    ~CArticleEditor();

signals:
    void requreUploadJoke(const T_Joke & tJoke);

private slots:

    void on_btnUpload_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CArticleEditor *ui;
};

#endif // JOKEEDITOR_H
