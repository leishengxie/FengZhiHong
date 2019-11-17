#include <stdio.h>
#include <QDebug>
#include <QTime>
#include <OCR.h>

int main()
{
    //1、加载原图
    Mat matSrc = imread("/home/mark/Desktop/OCR.png", IMREAD_GRAYSCALE);

    //2、二值化原图(这一步可以优化)
    Mat matBinary;
    threshold(matSrc, matBinary, 128, 255, THRESH_BINARY);

    //3、调用tesseract-3.00的借口识别字符
    OCR ocr;
    ocr.init("/home/mark/Desktop/tessdata"); //加载训练库
    QString sText = ocr.getRecognizeText(matBinary); //调用借口识别字符

    //4、输出识别结果
    qDebug() << "szText:" << sText;

    return 0;
}
