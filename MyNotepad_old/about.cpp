#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    QObject::connect(ui->ok,SIGNAL(clicked()),this,SLOT(moviePlay()));
}

about::~about()
{
    delete ui;
}
void about::moviePlay()
{
    /*
    QLabel label;
    QMovie *movie = new QMovie("animations/fire.gif");

    label.setMovie(movie);
    movie->start();
    */

    QMovie *movie = new QMovie ("animation.gif");
    ui->movieTextLabel->setMovie(movie);
    movie->start();
}
