#include "TextExtractor.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/types_c.h"

using namespace cv;

CTextExtractor::CTextExtractor(QObject* parent) : QObject(parent)
{

}

cv::Mat CTextExtractor::extractor(const QPixmap & pixmap)
{

}


void CTextExtractor::segmentText(cv::Mat & spineImage, cv::Mat & segSpine, bool removeNoise)
{

    cv::Mat spineGray;
    cvtColor(spineImage, spineGray, CV_BGR2GRAY);
    imshow("gray source", spineGray);
    spineGray = spineGray - 0.5;
//    WriteData("/Users/eternity/Desktop/未命名文件夹/gray1.txt", spineGray);
//    waitKey();

    cv::Mat spineAhe;
    adaptiveHistEqual(spineGray, spineAhe, 0.01);
    imshow("ahe", spineAhe);
//    WriteData("/Users/eternity/Desktop/未命名文件夹/gray2.txt", spineAhe);

    int window_num = 40;
    double window_h = (spineImage.rows / (double)window_num + 1e-3);
    int window_w = spineImage.cols;
    cv::Mat spine_th = cv::Mat::zeros(spineGray.size(), CV_8U);

    for (int i = 0; i < window_num; i ++)
    {
        double cut_from_r = window_h * i;
        double cut_to_r = window_h * (i + 1);
        cv::Mat window_img = cv::Mat::zeros(Size(cut_to_r - cut_from_r + 1, window_w), CV_8U);
        cv::Rect rect = cv::Rect(0, cut_from_r, window_w - 1, cut_to_r - cut_from_r + 1);
        window_img = cv::Mat(spineGray, rect);
        imshow("window section", window_img);

        sharpenImage(window_img, window_img);
        imshow("sharpen", window_img);
//        waitKey();
//        WriteData("/Users/eternity/Desktop/未命名文件夹/gray4.txt", window_img);
        double max_local, min_local;
        minMaxLoc(window_img, &min_local, &max_local);
        double color_diff = max_local - min_local;
        double thresh;
        cv::Mat window_tmp;
        if (color_diff > 50)
        {
            thresh = threshold(window_img, window_tmp, 1, 255, THRESH_OTSU);
        }
        else
        {
            thresh = 0;
        }
//        cout<<thresh<<endl;
        cv::Mat seg_window(window_img.size(), CV_64F);
        imgQuantize(window_img, seg_window, thresh);
//        WriteData("/Users/eternity/Desktop/未命名文件夹/quantize2.txt", seg_window);
        seg_window = seg_window == 1;
//        seg_window = seg_window / 255;
        //处理0边界值
        vector<int> cols1, cols2, rows1, rows2;
        findKEdgeFirst(seg_window, 0, 5, rows1, cols1);
        findKEdgeLast (seg_window, 0, 5, rows2, cols2);
        float max_zero_dist, max_one_dist;
        if(cols1.empty() || cols2.empty())
        {
            max_zero_dist = 0.0;
        }
        else
        {
            float avg_right = (rows2[0] + rows2[1] + rows2[2] + rows2[3] + rows2[4]) / (float)sizeof(rows2);
            float avg_left  = (rows1[0] + rows1[1] + rows1[2] + rows1[3] + rows1[4]) / (float)sizeof(rows1);
            max_zero_dist = avg_right - avg_left;
        }
        cols1.clear();
        cols2.clear();
        rows1.clear();
        rows2.clear();

        //处理1边界值
        findKEdgeFirst(seg_window, 255, 5, rows1, cols1);
        findKEdgeLast (seg_window, 255, 5, rows2, cols2);
        if(cols1.empty() || cols2.empty())
        {
            max_one_dist = 0;
        }
        else
        {
            float avg_right = (rows2[0] + rows2[1] + rows2[2] + rows2[3] + rows2[4]) / (float)sizeof(rows2);
            float avg_left  = (rows1[0] + rows1[1] + rows1[2] + rows1[3] + rows1[4]) / (float)sizeof(rows1);
            max_one_dist = avg_right - avg_left;
        }
        cols1.clear();
        cols2.clear();
        rows1.clear();
        rows2.clear();

        cv::Mat idx;
        findNonZero(seg_window, idx);
        int one_count = (int)idx.total();
        int zero_count = (int)seg_window.total() - one_count;

        float one_zero_diff = max_one_dist - max_zero_dist;
        float  dist_limit = 5;

        if(one_zero_diff > dist_limit)
        {
            seg_window = ~ seg_window;
        }
        else
        {
            if(one_zero_diff > -dist_limit && one_count > zero_count)
            {
                seg_window = ~ seg_window;
            }
        }

        seg_window.copyTo(cv::Mat( spine_th, rect));
//        imshow("spine_th", spine_th);
//        waitKey();


    }
    //去除噪声
    if (removeNoise)
    {
        vector<vector<cv::Point>> contours;
        imshow("spine_th", spine_th);
//        WriteData("/Users/eternity/Desktop/未命名文件夹/quantize1.txt", spine_th);
//        waitKey();
        findContours(spine_th, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

        for (int i = 0; i < contours.size(); i ++)
        {
            //compute bounding rect
            cv::Rect rect = boundingRect(contours[i]);
            double bbox_aspect = rect.width / (double)rect.height;
            int bbox_area = rect.width * rect.height;
            //compute solidity
            vector<vector<Point>> hull(1);
            convexHull( contours[i], hull[0] );
            double convex_area = contourArea(hull[0]);
            double solidity = bbox_area / convex_area;

            for (int j = 0; j < contours[i].size(); j ++)
            {
                if ( (rect.width > spineImage.cols / 1.001)
                        || (rect.width > spineImage.cols / 1.4 && bbox_aspect > 5.0)
                        || (rect.height > spineImage.cols / 1.1)
                        || (bbox_area < pow(spineImage.cols / 30, 2))
                        || (bbox_aspect > 0.5 && bbox_aspect < 1.7 && solidity > 0.9) )

                {
                    spine_th.at<int>(contours[i][j].x, contours[i][j].y) = 0;
                }
//                WriteData("/Users/eternity/Desktop/未命名文件夹/quantize2.txt", spine_th);
            }


        }

    }
    segSpine = spine_th;
    spine_th.release();

}



//对图片进行level量化
void CTextExtractor::imgQuantize(cv::Mat & src, cv::Mat & dst, double level)
{
    dst = cv::Mat::zeros(src.rows, src.cols, CV_8U);
    for (int i = 0; i < src.rows; i ++)
    {
        uchar* data = src.ptr<uchar>(i);
        uchar* data2 = dst.ptr<uchar>(i);
        for (int j = 0; j < src.cols; j ++)
        {
            if(data[j] <= level)
            {
                data2[j] = 1;
            }
            else
            {
                data2[j] = 2;
            }

        }
    }

}
//找出最左边界处，前edgeValue个值为k的边界值
void CTextExtractor::findKEdgeFirst(cv::Mat & data, int edgeValue, int k, vector<int> & rows, vector<int> & cols)
{
    int count = 0;
    for (int i = 0; i < data.cols; i ++)
    {
        uchar* u = data.ptr<uchar>(i);
        for (int j = 0; j < data.rows; j ++)
        {
            if(edgeValue == (int)u[j])
            {
                if(count < k)
                {
                    count ++;
                    cols.push_back(i);
                    rows.push_back(j);
                }

            }

        }
    }

}
//找出最右边界处，倒数edgeValue个值为k的边界值
void CTextExtractor::findKEdgeLast(cv::Mat & data, int edgeValue, int k, vector<int> & rows, vector<int> & cols)
{
    int count = 0;
    for (int i = data.cols - 1; i >= 0; i --)
    {
        uchar* u = data.ptr<uchar>(i);
        for (int j = data.rows - 1; j >= 0; j --)
        {
            if(edgeValue == (int)u[j])
            {
                if(count < k)
                {
                    count ++;
                    cols.push_back(i);
                    rows.push_back(j);
                }

            }
        }

    }

}
//直方图均衡
void CTextExtractor::adaptiveHistEqual(cv::Mat & src, cv::Mat & dst, double clipLimit)
{
    Ptr<cv::CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(clipLimit);
    clahe->apply(src, dst);
}



///
/// \brief CTextExtractor::cvMatToQImage
/// \param inMat
/// \return
///
QImage CTextExtractor::cvMatToQImage(const Mat & inMat)
{
    switch ( inMat.type() )
    {
        // 8-bit, 4 channel
        case CV_8UC4:
            {
                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_ARGB32 );

                return image;
            }

        // 8-bit, 3 channel
        case CV_8UC3:
            {
                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_RGB888 );

                return image.rgbSwapped();
            }

        // 8-bit, 1 channel
        case CV_8UC1:
            {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_Grayscale8 );//Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5
#else//这里还有一种写法，最后给出
                static QVector<QRgb>  sColorTable;

                // only create our color table the first time
                if ( sColorTable.isEmpty() )
                {
                    sColorTable.resize( 256 );

                    for ( int i = 0; i < 256; ++i )
                    {
                        sColorTable[i] = qRgb( i, i, i );
                    }
                }

                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_Indexed8 );

                image.setColorTable( sColorTable );
#endif

                return image;
            }

        default:
            qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
    }

    return QImage();
}


//将Mat转化为QPixmap
QPixmap CTextExtractor::cvMatToQPixmap(const Mat & inMat)
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

Mat CTextExtractor::QImageToCvMat(const QImage & inImage, bool inCloneImageData)
{
    switch ( inImage.format() )
    {
        // 8-bit, 4 channel
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            {
                cv::Mat  mat( inImage.height(), inImage.width(),
                              CV_8UC4,
                              const_cast<uchar*>(inImage.bits()),
                              static_cast<size_t>(inImage.bytesPerLine())
                            );

                return (inCloneImageData ? mat.clone() : mat);
            }

        // 8-bit, 3 channel
        case QImage::Format_RGB32:
        case QImage::Format_RGB888:
            {
                if ( !inCloneImageData )
                {
                    qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
                }

                QImage   swapped = inImage;

                if ( inImage.format() == QImage::Format_RGB32 )
                {
                    swapped = swapped.convertToFormat( QImage::Format_RGB888 );
                }

                swapped = swapped.rgbSwapped();

                return cv::Mat( swapped.height(), swapped.width(),
                                CV_8UC3,
                                const_cast<uchar*>(swapped.bits()),
                                static_cast<size_t>(swapped.bytesPerLine())
                              ).clone();
            }

        // 8-bit, 1 channel
        case QImage::Format_Indexed8:
            {
                cv::Mat  mat( inImage.height(), inImage.width(),
                              CV_8UC1,
                              const_cast<uchar*>(inImage.bits()),
                              static_cast<size_t>(inImage.bytesPerLine())
                            );

                return (inCloneImageData ? mat.clone() : mat);
            }

        default:
            qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
            break;
    }

    return cv::Mat();
}

Mat CTextExtractor::QPixmapToCvMat(const QPixmap & inPixmap, bool inCloneImageData)
{
    return QImageToCvMat( inPixmap.toImage(), inCloneImageData );
}

