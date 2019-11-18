#include "widget.h"
#include "ui_widget.h"

//OpenCV
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include "tesseract/baseapi.h"
#include "leptonica/allheaders.h"

#include <QtDebug>

using namespace cv;



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // test opencv ---ok
//    Mat im = imread("lena.png");
//    namedWindow("Image");
//    imshow("Image", im);
//    waitKey(0);
//    destroyWindow("Image");

    QString strtext = picToWord("OCR.png");
    qDebug() << strtext;

//    //1、加载原图
//    Mat matSrc = imread("/home/mark/Desktop/OCR.png", IMREAD_GRAYSCALE);

//    //2、二值化原图(这一步可以优化)
//    Mat matBinary;
//    threshold(matSrc, matBinary, 128, 255, THRESH_BINARY);

//    //3、调用tesseract-3.00的借口识别字符
//    OCR ocr;
//    ocr.init("/home/mark/Desktop/tessdata"); //加载训练库
//    QString sText = ocr.getRecognizeText(matBinary); //调用借口识别字符

//    //4、输出识别结果
//    qDebug() << "szText:" << sText;
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

Widget::~Widget()
{
    delete ui;
}

QString Widget::picToWord(const QString &path)
{
    char *outText;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
//    if (api->Init(NULL, "eng"))//chi_sim which is Chinese/eng
//    {
//        fprintf(stderr, "Could not initialize tesseract.\n");
//        exit(1);
//    }

    QString strTestPath = "./tessdata";
    if (api->Init(strTestPath.toLatin1().constData(), NULL))//chi_sim which is Chinese/eng
    {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }


    //QByteArray ba=fileNames.at(0).toLatin1();
    // Open input image with leptonica library
    //qDebug()<<ba;
    std::string str = path.toStdString();
    const char* ch = str.c_str();
    //qDebug()<<ch;
    Pix *image = pixRead(ch); //absolute path of file //ba.data()
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image);
    return outText;
}

