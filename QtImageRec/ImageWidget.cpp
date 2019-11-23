#include "ImageWidget.h"
#include "ProcessThread.h"

#include <QDebug>

ImageWidget::ImageWidget(QWidget *parent)
    :QWidget(parent),image_cur_index(1),image_max_index(8),
      image_path_prefix("./Data/Image/")
{
    setupUi(this);

    init();
}


ImageWidget::~ImageWidget()
{

}

void ImageWidget::init()
{
    uppushButton->setEnabled(false);
    //originallabel->setScaleContents(true);
    //originallabel->setPixmap(QPixmap(getCurrentImagePath()));

    connect(uppushButton,SIGNAL(clicked()),this,SLOT(click_UpPushButton()));
    connect(downpushButton,SIGNAL(clicked()),this,SLOT(click_DownPushButton()));

    originalgroupBox->setTitle(QString::fromUtf8("原图片"));
    step8groupBox->setTitle(QString::fromUtf8("初次分割"));
    step9groupBox->setTitle(QString::fromUtf8("分割结果"));
    resultgroupBox->setTitle(QString::fromUtf8("识别结果"));
    uppushButton->setText(QString::fromUtf8("上一张"));
    downpushButton->setText(QObject::tr("下一张"));
    resultlabel->setWordWrap(true);
    setWindowTitle(QString::fromUtf8("OpenCV文字识别"));

    QRect deskRect = QApplication::desktop()->availableGeometry();
    int w = deskRect.width() - 40 ;
    int h = deskRect.height() -30;
    //originalgroupBox->setFixedSize(w/2+10,h*2/3+20);
    //originallabel->setFixedSize(w/2,h*2/3);
    originallabel->setGeometry(5,5,w/2-5,h*2/3-5);
    setFixedSize(w,h);

    // start the first thread
    startProcessThread(getCurrentImagePath());
    displayImageInLabel(originallabel,getCurrentImagePath());
    //qDebug() << "W : "  << originallabel->width() << "H :" << originallabel->height();

}



QString ImageWidget::getCurrentImagePath()
{
    qDebug() << " Current path " << QString("%1%2.jpg").arg(image_path_prefix).arg(image_cur_index);
    return QString("%1%2.jpg").arg(image_path_prefix).arg(image_cur_index);
}


void ImageWidget::displayImageInLabel(QLabel *label,const QString& imagename)
{
    QPixmap pixmap;
    if( !pixmap.load(imagename) ){
        QMessageBox::warning(this,"Warning","Image " + imagename + " not exist !\n");
        return;
    }
    int w = label->width();
    int h = label->height();
    QPixmap fitpixmap = pixmap.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    label->setPixmap(fitpixmap);

}

void ImageWidget::displayImageInLabel(QLabel *label,const QPixmap& pixmap)
{
    int w = label->width();
    int h = label->height();
    QPixmap fitpixmap = pixmap.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    label->setPixmap(fitpixmap);
}

void ImageWidget::startProcessThread(const QString& filename)
{
    //qDebug() << filename;
    QThread* thread = new ProcessThread(filename);

    //qDebug() << " 66 connetc  here!" << endl ;
    connect(thread, SIGNAL(errorStringSignal(const QString&)), this, SLOT(errorStringSlot(const QString&)));
    connect(thread, SIGNAL(sendResutlTextSignal(const QByteArray&)), this, SLOT(sendResutlTextSlot(const QByteArray&)));
    //qDebug() << " 68 connetc  here!" << endl ;
    connect(thread, SIGNAL(displayStepsImageSignal()), this, SLOT(displayStepsImageSlot()));
    //qDebug() << " 70 connetc  here!" << endl ;
    connect(thread, SIGNAL(finished()), this, SLOT(deleteProcessThread()));
    //qDebug() << " 72 connetc  here!" << endl ;
    thread->start();
}

void ImageWidget::deleteProcessThread()
{
    QObject* obj = sender();
    ProcessThread * th = qobject_cast<ProcessThread*>(obj);
    obj->deleteLater();
}

void ImageWidget::click_UpPushButton()
{
    image_cur_index -= 1;
    //originallabel->setPixmap(QPixmap(getCurrentImagePath()));
    displayImageInLabel(originallabel,getCurrentImagePath());
    startProcessThread(getCurrentImagePath());

    if( !downpushButton->isEnabled() ){
        downpushButton->setEnabled(true);
    }
    if( image_cur_index == 1 )
    {
        uppushButton->setEnabled(false);
    }

}


void ImageWidget::click_DownPushButton()
{
    image_cur_index += 1;
    //originallabel->setPixmap(QPixmap(getCurrentImagePath()));
    displayImageInLabel(originallabel,getCurrentImagePath());
    startProcessThread(getCurrentImagePath());

    if( !uppushButton->isEnabled() ){
        uppushButton->setEnabled(true);
    }
    if( image_cur_index == image_max_index )
    {
        downpushButton->setEnabled(false);
    }

}


void ImageWidget::errorStringSlot(const QString& err)
{
   QMessageBox::warning(this,"Warning",err);
}

void ImageWidget::displayStepsImageSlot()
{
    //const QString steps_image_path_prefix = "./Data/Step/";
    QPixmap step8_pixmap ,step9_pixmap;
    const QString step8_image_path = "./Data/Step/8.jpg";
    const QString step9_image_path = "./Data/Step/9.jpg";

    if( !step8_pixmap.load(step8_image_path) ){
         QMessageBox::warning(this,"Warning","Step 8 Image is not exist !");
         return;
    }

    if( !step9_pixmap.load(step9_image_path) ){
         QMessageBox::warning(this,"Warning","Step 9 Image is not exist !");
         return;
    }
    //step8label->setPixmap(step8_pixmap);
    //step9label->setPixmap(step9_pixmap);
    displayImageInLabel(step8label,step8_pixmap);
    displayImageInLabel(step9label,step9_pixmap);
}


void ImageWidget::sendResutlTextSlot(const QByteArray& text)
{
    qDebug() << "text = " << text << endl;
    //QByteArray ba = text.toLatin1();
    resultlabel->setText(text);
}


