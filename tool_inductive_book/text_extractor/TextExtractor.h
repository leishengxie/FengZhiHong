#ifndef CTEXTEXTRACTOR_H
#define CTEXTEXTRACTOR_H

#include <QObject>
#include "opencv2/core/core.hpp"

class CTextExtractor : public QObject
{
    Q_OBJECT
public:
    explicit CTextExtractor(QObject *parent = 0);

    cv::Mat extractor(const QPixmap &pixmap);


public:
    QImage cvMatToQImage( const cv::Mat & inMat );
    QPixmap cvMatToQPixmap( const cv::Mat & inMat );
    cv::Mat QImageToCvMat( const QImage & inImage, bool inCloneImageData = true );
    cv::Mat QPixmapToCvMat( const QPixmap & inPixmap, bool inCloneImageData = true );

private:
    void segmentText(cv::Mat &spineImage, cv::Mat &segSpine, bool removeNoise);
    void imgQuantize(cv::Mat &src, cv::Mat &dst, double level);
    void findKEdgeFirst(cv::Mat &data, int edgeValue,int k,vector<int> &rows,vector<int> &cols);
    void findKEdgeLast(cv::Mat &data, int edgeValue,int k,vector<int> &rows, vector<int> &cols);
    void adaptiveHistEqual(cv::Mat &src,cv::Mat &dst,double clipLimit);
signals:

public slots:
};

#endif // CTEXTEXTRACTOR_H
