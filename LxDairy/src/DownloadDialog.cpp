#include "DownloadDialog.h"
#include "ui_DownloadDialog.h"

#include "QZXing.h"
#include <QPixmap>

static const char* const URL_LXDAIRY_WINDOWS = "http://47.104.141.61/LxDairy0.2.0.1.exe";
static const char* const URL_APK = "http://47.104.141.61/QtApp-debug.apk";

CDownloadDialog::CDownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDownloadDialog)
{
    ui->setupUi(this);

    // how to use

//    QImage imageToDecode("file.png");
//        QZXing decoder;
//        decoder.setDecoder( DecoderFormat_QR_CODE | DecoderFormat_EAN_13 );
//        QString result = decoder.decodeImage(imageToDecode);


        QImage barcode = QZXing::encodeData(URL_APK);
        QPixmap pixmap = QPixmap::fromImage(barcode);
        ui->label->resize(pixmap.size());
        ui->label->setPixmap(pixmap);

//        QString data = "text to be encoded";
//        QImage barcode = QZXing::encodeData(data, QZXing::EncoderFormat_QR_CODE,
//                                        QSize(width.toInt(), height.toInt()), QZXing::EncodeErrorCorrectionLevel_H);


}

CDownloadDialog::~CDownloadDialog()
{
    delete ui;
}
