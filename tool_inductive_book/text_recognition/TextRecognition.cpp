#include "TextRecognition.h"

#include <QtDebug>

CTextRecognition::CTextRecognition(QObject* parent)
    : QObject(parent)
    , m_tessBaseApi(new tesseract::TessBaseAPI())
{

    init();
}

CTextRecognition::~CTextRecognition()
{
    m_tessBaseApi->End();
    delete m_tessBaseApi;

}


void CTextRecognition::init()
{
//    控制台输出提示如下内容可忽略：
//    Tesseract Open Source OCR Engine v4.0.0-beta.1 with Leptonica
//    Warning. Invalid resolution 0 dpi. Using 70 instead.

    //加载字库及设置语言
    QString strTestPath = "./tessdata";
    //chi_sim which is Chinese/eng
    if (m_tessBaseApi->Init(strTestPath.toLatin1().constData(), "eng+chi_sim"))
    {
        qDebug() <<"Could not initialize tesseract.\n";
        return;
    }


}

QString CTextRecognition::recognize(Pix* pixImage)
{
    //设置图片
    m_tessBaseApi->SetImage(pixImage);

    //识别图像中的文字
    //m_tessBaseApi->Recognize(0);

    char* pText = m_tessBaseApi->GetUTF8Text();
    if (pText == NULL)
    {
        qDebug() << "Error getting text\n";
    }

    QString strText(pText);
    if (pText != NULL)
    {
        delete[] pText;
    }
    pixDestroy(&pixImage);

    m_tessBaseApi->Clear();
    return strText;
}

QString CTextRecognition::recognize(const unsigned char* imagedata, int width, int height, int bytes_per_pixel, int bytes_per_line)
{
/** c形式调用
    //设置图像
    TessBaseAPISetImage(m_tessBaseApi, imagedata, width, height, bytes_per_pixel, bytes_per_line);
    if (TessBaseAPIRecognize(m_tessBaseApi, NULL) != 0)
    {
        qDebug() << "Error in Tesseract recognition\n";
    }
    char* pText = NULL;
    if ((pText = TessBaseAPIGetUTF8Text(m_tessBaseApi)) == NULL)
    {
        qDebug() << "Error getting text\n";
    }

    QString strText(pText);
    TessDeleteText(pText);
    TessBaseAPIClear(m_tessBaseApi);
    return strText;
    */

    //设置图片
    m_tessBaseApi->SetImage(imagedata, width, height, bytes_per_pixel, bytes_per_line);

    //识别图像中的文字
    //m_tessBaseApi->Recognize(0);

    char* pText = m_tessBaseApi->GetUTF8Text();
    if (pText == NULL)
    {
        qDebug() << "Error getting text\n";
    }

    QString strText(pText);
    if (pText != NULL)
    {
        delete[] pText;
    }

    m_tessBaseApi->Clear();
    return strText;
}

///
/// \brief CTextRecognition::recognize
/// \param strLocalPath     absolute path of file
/// \return
///
QString CTextRecognition::recognize(const QString & strLocalPath)
{
    Pix* image = pixRead(strLocalPath.toStdString().c_str());
    return recognize(image);
}

