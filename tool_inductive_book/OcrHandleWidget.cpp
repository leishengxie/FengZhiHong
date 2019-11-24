#include "OcrHandleWidget.h"
#include "ui_OcrHandleWidget.h"
#include "screenshot/ScreenWidget.h"
#include "text_recognition/TextRecognition.h"
#include "text_extractor/TextExtractor.h"

#include <QDebug>
#include <QImage>
#include <QPixmap>


COcrHandleWidget::COcrHandleWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::COcrHandleWidget)
    , m_pTextExtractor(new CTextExtractor(this))
    , m_pTextRecognition(new CTextRecognition(this))
{
    ui->setupUi(this);

}


COcrHandleWidget::~COcrHandleWidget()
{
    delete ui;
}



void COcrHandleWidget::onFinishScreenshot(const QPixmap & pixmap)
{
    ui->label->setPixmap(pixmap);

    // test1 --ok
    //QString strResult = m_pTextRecognition->recognize("./OCR.png");

    // test2 -- 3%
    //QString strResult = m_pTextRecognition->recognize("./ocr2.jpg");

    // test2-1 -- 3%
//    cv::Mat mat = cv::imread("./ocr2.jpg");
//    QString strResult = m_pTextRecognition->recognize(mat.data
//                                                      , mat.cols
//                                                      , mat.rows
//                                                      , mat.channels()
//                                                      , mat.step);

    // test3 -- bug
//    cv::Mat mat = cv::imread("./ocr2.jpg");
//    cv::Mat matResult;
//    m_pTextExtractor->segmentText(mat, matResult);
//    QString strResult = m_pTextRecognition->recognize(matResult.data
//                                                      , matResult.cols
//                                                      , matResult.rows
//                                                      , matResult.channels()
//                                                      , matResult.step);

    // test4 -- 3%
    //QString strResult = m_pTextRecognition->recognize("./7.jpg");
    //QString strResult = m_pTextRecognition->recognize("./8.jpg");
    //QString strResult = m_pTextRecognition->recognize("./9.jpg");
    //QString strResult = m_pTextRecognition->recognize("test.jpg");
    //QString strResult = m_pTextRecognition->recognize("1.jpg"); // 80%

    // test5
//    cv::Mat mat = cv::imread("./ocr2.jpg");
//    cv::Mat matResult = m_pTextExtractor->extractor(mat);
//    QString strResult = m_pTextRecognition->recognize(matResult.data
//                                                      , matResult.cols
//                                                      , matResult.rows
//                                                      , matResult.channels()
//                                                      , matResult.step);

    // test
//    QPixmap pixmapLocal("weixin.png");
//    cv::Mat matResult = m_pTextExtractor->extractor(pixmapLocal);
//    QString strResult = m_pTextRecognition->recognize(matResult.data
//                                                      , matResult.cols
//                                                      , matResult.rows
//                                                      , matResult.channels()
//                                                      , matResult.step);

    // my -
    cv::Mat matResult = m_pTextExtractor->extractor(pixmap);
        QString strResult = m_pTextRecognition->recognize(matResult.data
                                                          , matResult.cols
                                                          , matResult.rows
                                                          , matResult.channels()
                                                          , matResult.step);

    ui->textEdit->clear();
    ui->textEdit->append(strResult);
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
