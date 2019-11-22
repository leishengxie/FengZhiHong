#include "OcrHandleWidget.h"
#include "ui_OcrHandleWidget.h"
#include "screenshot/ScreenWidget.h"

//OpenCV
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/types_c.h"

#include "tesseract/baseapi.h"
#include "leptonica/allheaders.h"

#include <QDebug>
#include <QImage>
#include <QPixmap>

using namespace cv;


namespace CVS
{
// 将Mat转化位QImage
inline QImage cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );//Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5
#else//这里还有一种写法，最后给出
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
            sColorTable.resize( 256 );

            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
#endif

        return image;
    }

    default:
        qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

//将Mat转化为QPixmap
inline QPixmap cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}
//将QImage转化为Mat
inline cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true )
{
    switch ( inImage.format() )
    {
    // 8-bit, 4 channel
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat  mat( inImage.height(), inImage.width(),
                      CV_8UC4,
                      const_cast<uchar*>(inImage.bits()),
                      static_cast<size_t>(inImage.bytesPerLine())
                      );

        return (inCloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB32:
    case QImage::Format_RGB888:
    {
        if ( !inCloneImageData )
        {
            qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
        }

        QImage   swapped = inImage;

        if ( inImage.format() == QImage::Format_RGB32 )
        {
            swapped = swapped.convertToFormat( QImage::Format_RGB888 );
        }

        swapped = swapped.rgbSwapped();

        return cv::Mat( swapped.height(), swapped.width(),
                        CV_8UC3,
                        const_cast<uchar*>(swapped.bits()),
                        static_cast<size_t>(swapped.bytesPerLine())
                        ).clone();
    }

    // 8-bit, 1 channel
    case QImage::Format_Indexed8:
    {
        cv::Mat  mat( inImage.height(), inImage.width(),
                      CV_8UC1,
                      const_cast<uchar*>(inImage.bits()),
                      static_cast<size_t>(inImage.bytesPerLine())
                      );

        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }

    return cv::Mat();
}

//将QPixmap转化为Mat
inline cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true )
{
    return QImageToCvMat( inPixmap.toImage(), inCloneImageData );
}
}


PIX* cvtMat2PIX(Mat imgGray)
{
    int cols = imgGray.cols;
    int rows = imgGray.rows;

    PIX *pixS = pixCreate(cols, rows, 8);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            pixSetPixel(pixS, j, i, (l_uint32)imgGray.at<uchar>(i, j));
    return pixS;
}


////CV_8UC1另一种写法，不过我觉得上面的一种写法更优雅^_^
//QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
//// Set the color table (used to translate colour indexes to qRgb values)
//image.setColorCount(256);
//for(int i = 0; i < 256; i++)
//{
//    image.setColor(i, qRgb(i, i, i));
//}
//// Copy input Mat
//uchar *pSrc = mat.data;
//for(int row = 0; row < mat.rows; row ++)
//{
//    uchar *pDest = image.scanLine(row);
//    memcpy(pDest, pSrc, mat.cols);
//    pSrc += mat.step;
//}
//return image;




COcrHandleWidget::COcrHandleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::COcrHandleWidget)
{
    ui->setupUi(this);



    // test opencv ---ok
//    Mat im = imread("lena.png");
//    namedWindow("Image");
//    imshow("Image", im);
//    waitKey(0);
//    destroyWindow("Image");

//    QString strtext = picToWord("OCR.png");
//    qDebug() << strtext;


}

//QString OCR::getRecognizeText(const Mat &matSrc)
//{
//    if (matSrc.channels() != 1) return QString();

//    //设置图像
//    m_tessBaseApi.SetImage(matSrc.data, matSrc.cols, matSrc.rows, matSrc.channels(), matSrc.step);

//    //识别图像中的文字
//    char* pText = m_tessBaseApi.GetUTF8Text();
//    QString sText(pText);
//    if (pText != NULL) delete[] pText;
//    m_tessBaseApi.Clear();

//    return QString(sText);
//}

COcrHandleWidget::~COcrHandleWidget()
{
    delete ui;
}



void COcrHandleWidget::onFinishScreenshot(const QPixmap &pixmap)
{
    ui->label->setPixmap(pixmap);

    char *outText;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
//    if (api->Init(NULL, "eng"))//chi_sim which is Chinese/eng
//    {
//        fprintf(stderr, "Could not initialize tesseract.\n");
//        exit(1);
//    }

    //QString strTestPath = QCoreApplication::applicationDirPath() + "/tessdata";
    QString strTestPath = "./tessdata";
    if (api->Init(strTestPath.toLatin1().constData(), "eng"))//chi_sim which is Chinese/eng
    {
        //fprintf(stderr, "Could not initialize tesseract.\n");
        //exit(1);
        qDebug() <<"Could not initialize tesseract.\n";
        return;
    }


    //QString path = "OCR.png";
    QString path = "ocr2.jpg";
    std::string str = path.toStdString();
    const char* ch = str.c_str();
    Pix *image = pixRead(ch); //absolute path of file //ba.data()
    api->SetImage(image);

//    cv::Mat mat = CVS::QPixmapToCvMat(pixmap);
//    Pix *image = cvtMat2PIX(mat);
//    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();
    //printf("OCR output:\n%s", outText);
    ui->textEdit->clear();
    ui->textEdit->append(outText);

    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image);

}


void COcrHandleWidget::on_btnScreenshot_clicked()
{
    CScreenWidget* pScreenWidget = new CScreenWidget();
    connect(pScreenWidget, SIGNAL(finishScreenshot(QPixmap)), this, SLOT(onFinishScreenshot(QPixmap)));
    pScreenWidget->show();

}

void COcrHandleWidget::on_btnSure_clicked()
{
    emit finishOcr(ui->textEdit->toPlainText());
    close();
}
