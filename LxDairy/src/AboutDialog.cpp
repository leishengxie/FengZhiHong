#include "AboutDialog.h"
#include "ui_AboutDialog.h"

CAboutDialog::CAboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(moviePlay()));
    setWindowTitle("关于");

//    QLabel *label = new QLabel(this);
//    label->setFrameStyle(QFrame::Box | QFrame::Sunken);//设置label的形状和阴影模式的,这里采用的box形状和凹陷模式
//    label->setText(tr("<a href = \"www.cnblogs.com/tornadomeet\">www.cnblogs.com/tornadomeet</a>"));//设置文本内容
//    label->setTextFormat(Qt::RichText);//设置文本格式为富文本格式，又称多文本格式，用于跨平台使用的
//    label->setOpenExternalLinks(true);//运行打开label上的链接
//    ui->statusBar->addPermanentWidget(label);//将label附加到状态栏上，永久性的
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
