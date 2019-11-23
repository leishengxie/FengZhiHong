#include "TextRecognition.h"

CTextRecognition::CTextRecognition(QObject* parent)
    : QObject(parent)
//    , m_tessBaseApi(new tesseract::TessBaseAPI())
{
    // 新版
    m_tessBaseApi = TessBaseAPICreate();
    init();
}

CTextRecognition::~CTextRecognition()
{
    //delete m_tessBaseApi;
    TessBaseAPIEnd(m_tessBaseApi);
    TessBaseAPIDelete(m_tessBaseApi);
}


void CTextRecognition::init()
{
    QString strTestPath = "./tessdata";
    //chi_sim which is Chinese/eng
//    if (m_tessBaseApi->Init(strTestPath.toLatin1().constData(), "eng"))
//    {
//        qDebug() <<"Could not initialize tesseract.\n";
//        return;
//    }


    //加载字库及设置语言
    if (TessBaseAPIInit3(m_tessBaseApi, strTestPath, "eng+chi_sim") != 0)
    {
        qDebug() << "Could not initialize tesseract.\n";
        return;
    }


}

QString CTextRecognition::recognize(Pix* pixImage)
{

    //设置图片
    // --old
    //m_tessBaseApi->SetImage(pixImage);
    // --new
    TessBaseAPISetImage2(m_tessBaseApi, pixImage);

    // --new add
    if (TessBaseAPIRecognize(m_tessBaseApi, NULL) != 0)
    {
        qDebug() << "Error in Tesseract recognition\n";
    }

    //识别图像中的文字
    //char* pText = m_tessBaseApi->GetUTF8Text();
    char* pText = NULL;
    if ((pText = TessBaseAPIGetUTF8Text(m_tessBaseApi)) == NULL)
    {
        qDebug() << "Error getting text\n";
    }

    QString strText(pText);
//    if (pText != NULL)
//    {
//        delete[] pText;
//    }
    TessDeleteText(pText);
    pixDestroy(&pixImage);

    //m_tessBaseApi->Clear();
    TessBaseAPIClear(m_tessBaseApi);
    return strText;
}

QString CTextRecognition::recognize(const unsigned char* imagedata, int width, int height, int bytes_per_pixel, int bytes_per_line)
{

    //设置图像
    m_tessBaseApi->SetImage(imagedata, width, height, bytes_per_pixel, bytes_per_line);

    //识别图像中的文字
    char* pText = m_tessBaseApi->GetUTF8Text();

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

