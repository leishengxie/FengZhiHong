//#include "stdafx.h"
#include "MorOperationAlg.h"

int StructArr[13] = {3, 5, 7, 9, 11, 13, 15, 21, 31, 41, 61, 81, 101};

/**********************************************************
 * 函数名：chMorOp
 * 功能 ：基础形态学操作
 * 参数：
 *	src				输入二值图
 *	dst				输出二值图
 *  type			形态学操作类型：膨胀、腐蚀、开操作、闭操作
 *  StructSize		结构元素尺寸
 *  StructEle		结构元素类型
 *
***********************************************************/
CH_DLL_EXPORT
s32 chMorOp(IN Mat src, OUT Mat& dst, IN int type, IN Size StructSize, IN int StructEle )
{
    // 输入检测
    if(src.empty())
        return -1;

    Mat img;
    if(src.channels() == 1)
        img = src;
    else if(src.channels() == 3)
        cvtColor(src, img, CV_BGR2GRAY);

    Mat element1 = getStructuringElement(StructEle, StructSize);
    morphologyEx(src, dst, type, element1);
    return 0;
}


/**********************************************************
 * 函数名：chMorOp2
 * 功能 ：基础形态学操作
 * 参数：
 *	src				输入二值图
 *	dst				输出二值图
 *  type			形态学操作类型：膨胀、腐蚀、开操作、闭操作
 *  StructSize		结构元素尺寸
 *  StructEle		结构元素类型
 *
***********************************************************/
CH_DLL_EXPORT
s32 chMorOp2(IN Mat src, OUT Mat& dst, IN int type, IN int StructSize, IN int StructEle)
{
    // 输入检测
    if(src.empty())
        return -1;

    Mat img;
    if(src.channels() == 1)
        img = src;
    else if(src.channels() == 3)
        cvtColor(src, img, CV_BGR2GRAY);

    Mat element1 = getStructuringElement(StructEle,
                        Size(StructArr[StructSize], StructArr[StructSize]));
    morphologyEx(img, dst, type, element1);

    return 0;
}


/**********************************************************
 * 函数名：chBorderExtract
 * 功能 ：边界提取
 * 参数：
 *	src				输入二值图
 *  dst				输出二值图
 *  StructSize		结构元素尺寸
 *  StructEle		结构元素类型
***********************************************************/
CH_DLL_EXPORT
s32 chBorderExtract(IN Mat src, OUT Mat& dst,IN int StructSize, IN int StructEle)
{
    // 输入检测
    if(src.empty())
        return -1;

    Mat img;
    if(src.channels() == 1)
        img = src;
    else if(src.channels() == 3)
        cvtColor(src, img, CV_BGR2GRAY);

    Mat temp;
    chMorOp2(img, temp, CH_MOR_ERODE, StructSize, StructEle);
    subtract(img, temp, dst);

    return 0;
}


/**********************************************************
 * 函数名：chHoleFilling
 * 功能 ：孔洞填充
***********************************************************/
CH_DLL_EXPORT
s32 chHoleFilling(IN Mat src, OUT Mat& dst)
{
    // 输入检测
    if(src.empty())
        return -1;

    Mat grayImg;
    if(src.channels()==1)
        grayImg = src;
    else if(src.channels()==3)
        cvtColor(src, grayImg, CV_BGR2GRAY);

    Mat m;
    threshold(grayImg, m, 128, 255, THRESH_BINARY);

    // Step1: make a border
    Mat m_with_border;
    copyMakeBorder(m, m_with_border, 1, 1, 1, 1, BORDER_CONSTANT, Scalar());

    // Step2: find the contour fill holes and fill external contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(m_with_border, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    if( !contours.empty() && !hierarchy.empty())
    {
        for(u32 idx = 0; idx<contours.size(); idx++)
        {
            drawContours(m_with_border, contours, idx, Scalar::all(255), CV_FILLED, 8);
        }
    }

    // Step3: remove the border
    dst = m_with_border(Rect(1, 1, m_with_border.cols-2, m_with_border.rows-2));

    return 0;
}




