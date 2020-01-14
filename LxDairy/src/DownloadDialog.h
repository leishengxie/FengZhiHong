#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>

namespace Ui {
class CDownloadDialog;
}

class CDownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CDownloadDialog(QWidget *parent = 0);
    ~CDownloadDialog();

private:
    Ui::CDownloadDialog *ui;
};

#endif // DOWNLOADDIALOG_H
