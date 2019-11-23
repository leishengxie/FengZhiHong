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

PIX* cvtMat2PIX(cv::Mat imgGray)
{
    int cols = imgGray.cols;
    int rows = imgGray.rows;

    PIX* pixS = pixCreate(cols, rows, 8);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            pixSetPixel(pixS, j, i, (l_uint32)imgGray.at<uchar>(i, j));
        }
    }
    return pixS;
}

void COcrHandleWidget::onFinishScreenshot(const QPixmap & pixmap)
{
    ui->label->setPixmap(pixmap);

    cv::Mat mat = m_pTextExtractor->extractor(pixmap);
    Pix* image = cvtMat2PIX(mat);
    QString strResult = m_pTextRecognition->recognize(image);

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
