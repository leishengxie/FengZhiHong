#ifndef JOKEEDITOR_H
#define JOKEEDITOR_H

#include <QWidget>

namespace Ui {
class CJokeEditor;
}

class CJokeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CJokeEditor(QWidget *parent = 0);
    ~CJokeEditor();

private slots:
    void on_btnSave_clicked();

    void on_btnUpload_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CJokeEditor *ui;
};

#endif // JOKEEDITOR_H
