#ifndef ACCPASSWDWIDGET_H
#define ACCPASSWDWIDGET_H

#include <QWidget>

namespace Ui {
class CAccPasswdWidget;
}

class CAccPasswdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CAccPasswdWidget(QWidget *parent = 0);
    ~CAccPasswdWidget();

private slots:
    void on_btnAdd_clicked();

    void on_btnCommit_clicked();

    void on_btnDelete_clicked();


private:
    Ui::CAccPasswdWidget *ui;
};

#endif // ACCPASSWDWIDGET_H
