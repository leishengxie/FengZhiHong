#ifndef CTEXTRECOGNITION_H
#define CTEXTRECOGNITION_H

#include <QObject>

// c++形式
#include "tesseract/baseapi.h"
#include "leptonica/allheaders.h"

// The C-API can of course also be used by regular C programs c形式
// C-API in python c形式可供python
//#include "tesseract/capi.h"

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
    //TessBaseAPI* m_tessBaseApi; //c形式
    tesseract::TessBaseAPI* m_tessBaseApi;
};

#endif // CTEXTRECOGNITION_H
