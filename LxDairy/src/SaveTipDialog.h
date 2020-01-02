#ifndef SAVETIPDIALOG_H
#define SAVETIPDIALOG_H

#include <QDialog>

namespace Ui {
class CSaveTipDialog;
}

class CSaveTipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSaveTipDialog(QWidget *parent = 0);
    ~CSaveTipDialog();

private:
    Ui::CSaveTipDialog *ui;
};

#endif // SAVETIPDIALOG_H
