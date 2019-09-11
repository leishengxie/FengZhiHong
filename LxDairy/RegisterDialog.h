#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class CRegisterDialog;
}

class CRegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRegisterDialog(QWidget *parent = 0);
    ~CRegisterDialog();

private slots:
    void on_btnOK_clicked();


private:
    Ui::CRegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
