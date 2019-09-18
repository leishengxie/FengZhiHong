#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class AboutDialog;
}

class CAboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAboutDialog(QWidget *parent = 0);
    ~CAboutDialog();
private slots:
    void moviePlay();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUT_H
