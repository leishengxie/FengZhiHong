#ifndef JOKEEDITOR_H
#define JOKEEDITOR_H

#include <QWidget>
#include "Joke.h"

namespace Ui {
class CJokeEditor;
}

class CJokeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CJokeEditor(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
    ~CJokeEditor();

signals:
    void requreUploadJoke(const T_Joke & tJoke);

private slots:

    void on_btnUpload_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CJokeEditor *ui;
};

#endif // JOKEEDITOR_H
