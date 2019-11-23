#ifndef CTEXTRECOGNITION_H
#define CTEXTRECOGNITION_H

#include <QObject>

//#include "tesseract/baseapi.h"
#include "leptonica/allheaders.h"
#include "tesseract/capi.h"

///
/// \brief The CTextRecognition class   文字识别
///
class CTextRecognition : public QObject
{
    Q_OBJECT
public:
    explicit CTextRecognition(QObject *parent = 0);
    ~CTextRecognition();

    QString recognize(Pix *pixImage);

    QString recognize(const unsigned char* imagedata, int width, int height,
                    int bytes_per_pixel, int bytes_per_line);

    QString recognize(const QString & strLocalPath);
signals:

public slots:

private:
    void init();

private:
    tesseract::TessBaseAPI* m_tessBaseApi;
};

#endif // CTEXTRECOGNITION_H
