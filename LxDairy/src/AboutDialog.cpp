#include "AboutDialog.h"
#include "ui_AboutDialog.h"

CAboutDialog::CAboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(moviePlay()));
    setWindowTitle("关于");
}

CAboutDialog::~CAboutDialog()
{
    delete ui;
}
void CAboutDialog::moviePlay()
{
    /*
    QLabel label;
    QMovie *movie = new QMovie("animations/fire.gif");

    label.setMovie(movie);
    movie->start();
    */

//    QMovie *movie = new QMovie ("animation.gif");
//    ui->movieTextLabel->setMovie(movie);
//    movie->start();
}
