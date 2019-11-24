//#include "stdafx.h"
//#include "StdAfx.h"
#include "ImageProcess.h"

/***************************************************
 * 函数名：chSetMat
 * 功能：设置图像为固定值
 * 说明：
 * 可以直接使用Mat中的重载符，例如：
 *  Mat img(100, 100, CV_8UC3);
 *  img = Scalar(0, 0, 255);
 ***************************************************/
CH_DLL_EXPORT
s32 chSetMat(Mat & img, Scalar s)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    if(s.val[0] < 0 || s.val[0] > 255 ||
            s.val[1] < 0 || s.val[1] > 255 ||
            s.val[2] < 0 || s.val[2] > 255)
    {
        return -1;
    }

    if( img.channels() == 1)	// Gray
    {
        for(s32 i = 0; i < img.rows; i++)
        {
            u8* ptImg = img.ptr<u8>(i);
            for(s32 j = 0; j < img.cols; j++)
            {
                ptImg[j] = (u8)s.val[0];
            }
        }
    }
    else if(img.channels() == 3) // BGR
    {
        for(s32 i = 0; i < img.rows; i++)
        {
            u8* ptImg = img.ptr<u8>(i);
            for(s32 j = 0; j < img.cols; j++)
            {
                ptImg[3 * j] = (u8)s.val[0];
                ptImg[3 * j + 1] = (u8)s.val[1];
                ptImg[3 * j + 2] = (u8)s.val[2];
            }
        }
    }

    return 0;
}


/***************************************************
 * 函数名：chSetMatInv
 * 功能  ： 矩阵取反
 ***************************************************/
CH_DLL_EXPORT
s32 chSetMatInv(Mat img, Mat & dst)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    dst.create(img.rows, img.cols, img.type());
    if(img.channels() == 1)
    {
        for(s32 i = 0; i < img.rows; i++)
        {
            u8* ptrImg = img.ptr<u8>(i);
            u8* ptrDst = dst.ptr<u8>(i);
            for(s32 j = 0; j < img.cols; j++)
            {
                ptrDst[j] = 255 - ptrImg[j];
            }
        }
    }
    else if(img.channels() == 3)
    {
        for(s32 i = 0; i < img.rows; i++)
        {
            u8* ptrImg = img.ptr<u8>(i);
            u8* ptrDst = dst.ptr<u8>(i);
            for(s32 j = 0; j < img.cols; j++)
            {
                ptrDst[3 * j] = 255 - ptrImg[3 * j];
                ptrDst[3 * j + 1] = 255 - ptrImg[3 * j + 1];
                ptrDst[3 * j + 2] = 255 - ptrImg[3 * j + 2];
            }
        }
    }

    return 0;
}


/***************************************************
 * 函数名：chGetPixel
 * 功能  ：获取第i行第j列处的像素值
 * 参数
 *   img		图像数据
 *   iRows		第i行
 *	 jCols		第j列
 *	 iChannels  B:0; G:1; R:2
 ***************************************************/
CH_DLL_EXPORT
u8 chGetPixel(Mat & img, s32 iRows, s32 jCols, s32 iChannels)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    if(iRows < 0 || jCols < 0 || iChannels < 0 || iChannels > 2)
    {
        return -1;
    }

    u8* ptImg = img.ptr<u8>(iRows, jCols);
    return ptImg[iChannels];
}


/***************************************************
 * 函数名：chSetPixel
 * 功能  ：设置第i行第j列处的像素值
 * 参数
 *	 val		设置值
 *   img		图像数据
 *   iRows		第i行
 *	 jCols		第j列
 *	 iChannels  B:0; G:1; R:2
 ***************************************************/
CH_DLL_EXPORT
s32 chSetPixel(u8 val, Mat & img, s32 iRows, s32 jCols, s32 iChannels)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    if(iRows < 0 || jCols < 0 || iChannels < 0 || iChannels > 2)
    {
        return -1;
    }

    u8* ptImg = img.ptr<u8>(iRows, jCols);
    ptImg[iChannels] = val;
    return 0;
}


/***************************************************
 * 函数名：chBwRowSum
 * 功能  ：二值图像行求和( 白点数目)
 ***************************************************/
CH_DLL_EXPORT
s32 chBwRowSum(Mat img, vector<s32> & vRowSum)
{
    // 图像通道检测
    if(img.channels() != 1 )
    {
        return -1;
    }

    vRowSum.clear();
    for(s32 i = 0; i < img.rows; i++)
    {
        s32 RowSum = 0;
        for(s32 j = 0; j < img.cols; j++)
        {
            if(chGetPixel(img, i, j) == 255)
            {
                RowSum++;
            }
        }
        vRowSum.push_back(RowSum);
    }

    return 0;
}


/***************************************************
 * 函数名：chBwColSum
 * 功能  ：二值图像列求和（白点数目）
 ***************************************************/
CH_DLL_EXPORT
s32 chBwColSum(Mat img, vector<s32> & vColSum)
{
    // 图像通道检测
    if(img.channels() != 1 )
    {
        return -1;
    }

    vColSum.clear();
    for(s32 j = 0; j < img.cols; j++)
    {
        s32 ColSum = 0;
        for(s32 i = 0; i < img.rows; i++)
        {
            if(chGetPixel(img, i, j) == 255)
            {
                ColSum++;
            }
        }
        vColSum.push_back(ColSum);
    }

    return 0;
}


/***************************************************
 * 函数名：chGrayRowSum
 * 功能  ：灰度图像行求和
 ***************************************************/
CH_DLL_EXPORT
s32 chGrayRowSum(Mat img, vector<s32> & vRowSum)
{
    // 图像通道检测
    if(img.channels() != 1 )
    {
        return -1;
    }

    vRowSum.clear();
    for(s32 i = 0; i < img.rows; i++)
    {
        s32 RowSum = 0;
        for(s32 j = 0; j < img.cols; j++)
        {
            RowSum += chGetPixel(img, i, j);
        }
        vRowSum.push_back(RowSum);
    }

    return 0;
}


/***************************************************
 * 函数名：chGrayColsum
 * 功能  ：灰度图像列求和
 ***************************************************/
CH_DLL_EXPORT
s32 chGrayColSum(Mat img, vector<s32> & vColSum)
{
    // 图像通道检测
    if(img.channels() != 1 )
    {
        return -1;
    }

    vColSum.clear();
    for(s32 j = 0; j < img.cols; j++)
    {
        s32 ColSum = 0;
        for(s32 i = 0; i < img.rows; i++)
        {
            ColSum += chGetPixel(img, i, j);
        }
        vColSum.push_back(ColSum);
    }

    return 0;
}


/**********************************************************
 * 函数名：chHist
 * 功能 ：直方图统计
 * 参数：
 *	src				输入灰度图像
 *  vCounts			直方图统计结果
***********************************************************/
CH_DLL_EXPORT
s32 chHist(Mat src, vector<s32> & vCounts )
{
    // 检测
    if(src.channels() != 1)
    {
        return -1;
    }

    // 初始化
    vector<s32> vTemp(256);
    for(u32 i = 0; i < vTemp.size(); i++)
    {
        vTemp[i] = 0;
    }

    // 统计
    for(s32 i = 0; i < src.rows; i++)
    {
        u8* ptSrc = src.ptr<u8>(i);
        for(s32 j = 0; j < src.cols; j++)
        {
            vTemp[ptSrc[j]]++;
        }
    }

    vCounts = vTemp;
    return 0;
}


// 直方图显示
CH_DLL_EXPORT
s32 chHistImage(Mat src, Mat & dst )
{
    // 暂时未实现
    dst = src;
    return 0;
}


/****************************************************
 * 函数名：ImageFilter2
 * 功能： 图像直方图等级统计，主要用于检测出直方图等级小于某一阈值的图像
 * 返回值：
 *  1：满足要求； 0：不满足要求
 ****************************************************/
CH_DLL_EXPORT
s32 ImageHistLevelCheck(Mat grayImg, s32 thresh)
{
    // 输入检测
    if(grayImg.empty())
    {
        return -1;
    }

    if(thresh <= 0)
    {
        return -1;
    }

    vector<s32> vCounts;
    chHist(grayImg, vCounts);

    s32	GrayNum = 0;
    for(u32 i = 0; i < vCounts.size(); i++)
    {
        if(vCounts[i] > 10)	// 某个灰度级下，像素点个数小于10，则认为图像无该灰度级
        {
            GrayNum = GrayNum + 1;
        }
    }

    if(GrayNum < thresh)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


/******************************************************
 * 函数名：chResize
 * 功能  ： 图像缩放，将图像按比例缩放到固定像素大小
 *
 ******************************************************/
CH_DLL_EXPORT
s32 chResize2(IN Mat grayImg, OUT Mat & sizeImg, IN s32 pixelLimit, OUT f32 & ratio)
{
    // 输入检测
    if(grayImg.empty())
    {
        return -1;
    }

    if(pixelLimit < 100)
    {
        return -1;
    }

    s32 PixelCount = grayImg.rows * grayImg.cols;
    if(PixelCount > pixelLimit)
    {
        ratio = (f32)(cv::sqrt(grayImg.rows * grayImg.cols * 1.0 / pixelLimit));
        s32 wdith = (s32)(grayImg.cols / ratio);
        s32 height = (s32)(grayImg.rows / ratio);
        resize(grayImg, sizeImg, Size(wdith, height));
    }
    else
    {
        sizeImg = grayImg;
    }

    return 0;
}


/******************************************************
 * 函数名：chTargetRawSize
 * 功能  ： 复原图像目标原始尺寸，可添加边界
 *
 ******************************************************/
CH_DLL_EXPORT
s32 chTargetRawSize(IN Mat src,
                    IN Rect sizeRt,
                    IN f32 ratio,
                    OUT Rect & rt,
                    IN s32 iBorder,
                    IN s32 jBorder)
{
    if(ratio < 0)
    {
        rt = sizeRt;
    }
    else
    {
        rt.x = (s32)(sizeRt.x * ratio);
        rt.y = (s32)(sizeRt.y * ratio);
        rt.width = (s32)(sizeRt.width * ratio);
        rt.height = (s32)(sizeRt.height * ratio);
    }

    rt.x = MAX(1, rt.x - jBorder);
    rt.y = MAX(1, rt.y - iBorder);
    rt.width = MIN(src.cols - rt.x - 1, rt.width + 2 * jBorder);
    rt.height = MIN(src.rows - rt.y - 1, rt.height + 2 * iBorder);

    return 0;
}


/******************************************************
 * 函数名：chGetEqualWHImage
 * 功能  ： 获取等比例图像
 * 参数：
 *	src		原始图像
 *	dst		等比例图像
 *	pt		等比例图像中数据起点
 ******************************************************/
CH_DLL_EXPORT
s32 chGetEqualWHImage(IN Mat src, Mat & dst, Point & pt)
{
    // 输入检测
    if(src.empty())
    {
        return -1;
    }

    Mat img = src;
    Mat ImgUse;
    if(img.rows > img.cols)
    {
        ImgUse.create(img.rows, img.rows, img.type());
        ImgUse = Scalar(128, 128, 128);
        s32 LeftLen = (img.rows - img.cols) / 2;
        img.copyTo(ImgUse(Rect(LeftLen, 0, img.cols, img.rows)));
        pt.x = LeftLen;
        pt.y = 0;
    }
    else if(img.cols > img.rows)
    {
        ImgUse.create(img.cols, img.cols, img.type());
        ImgUse = Scalar(128, 128, 128);
        s32 TopLen = (img.cols - img.rows) / 2;
        img.copyTo(ImgUse(Rect(0, TopLen, img.cols, img.rows)));
        pt.x = 0;
        pt.y = TopLen;
    }

    ImgUse.copyTo(dst);
    return 0;
}


/*************************************************************************************
 * 函数名：chBGR2Gray
 * 功能： 彩色转灰度
 * 原理：
 *	1. 彩色转灰度采用如下公式：	Y = 0.299*R + 0.587*G + 0.114*B
 *************************************************************************************/
CH_DLL_EXPORT
s32 chBGR2Gray(IN Mat ColorImg, OUT Mat & GrayImg)
{
    if(ColorImg.empty())
    {
        return -1;
    }

    if(ColorImg.channels() == 1)
    {
        GrayImg = ColorImg;
    }
    else if(ColorImg.channels() == 3)
    {

        GrayImg.create(ColorImg.rows, ColorImg.cols, CV_8UC1);

        for(s32 i = 0; i < ColorImg.rows; i++)
        {
            u8* ptColor = ColorImg.ptr<u8>(i);
            u8* ptGray = GrayImg.ptr<u8>(i);
            for(s32 j = 0; j < ColorImg.cols; j++)
            {
                ptGray[j] = (u8)(ptColor[3 * j] * 0.114 + ptColor[3 * j + 1] * 0.587 + ptColor[3 * j + 2] * 0.299);
            }
        }
    }

    return 0;
}


/******************************************************
 * 函数名：chResize
 * 功能： 图像缩放
 * 说明：
 ******************************************************/
CH_DLL_EXPORT
s32 chResize(IN Mat & img, OUT Mat & sizeImg,
             IN Size sz,
             IN s32 type)
{

    return 0;
}


/************************************************************************************
 * 函数名：chImfilter2
 * 功能： 图像滤波模板
 * 参数：
 *	img		原图像, 数据类型为 8uc1
 *	model	模型,   数据类型为 32sc1 或 32fc1；
 *	dst		后图像,	数据类型与 model类型一致；
 * 返回值：
 *	0	运行正常
 *	1	输入为空
 *	2	输入图像不是单通道
 *	3	模板不是单通道，或者模板宽高不一致
 *	4	模板尺寸不是奇数
 *	5	模板数据类型不是32sc1或32fc1
 * 原理：
 *	1. model为滤波的模型，必须为奇数x奇数，比如3x3,5x5,7x7之类；
 *	2. 关于边界问题，对于未参与滤波的像素，可赋值为：原图像像素值；0值；
 *	3. 保证滤波后的图像与原图像尺寸保持一致；
 *	4. 为了简化处理流程，必须保证输入图像为单通道；
 ************************************************************************************/
CH_DLL_EXPORT
s32 chImfilter2(IN Mat & img, IN Mat & model, OUT Mat & dst, IN s32 border)
{
    // 输入检测
    if(img.empty() || model.empty())
    {
        return 1;
    }

    if(img.channels() != 1)
    {
        return 2;
    }

    if(model.channels() != 1 || model.rows != model.cols)
    {
        return 3;
    }

    if(model.rows % 2 == 0)
    {
        return 4;
    }

    s32 radius = model.rows / 2;
    s32 widthStep = *img.step.p;

    if(model.type() == CV_32SC1)
    {
        dst.create(img.rows, img.cols, CV_32SC1);
        s32* ptModel = (s32*)model.data;
        s32* ptDst = (s32*)dst.data;
        for(s32 i = 0; i < img.rows; i++)
        {
            for(s32 j = 0; j < img.cols; j++)
            {
                if(i < radius || i >= (img.rows - radius) || j < radius || j >= (img.cols - radius))
                {
                    if(border == CH_BORDER_ZERO)
                    {
                        *(ptDst + i * dst.cols + j) = 0;
                    }
                    else
                    {
                        *(ptDst + i * dst.cols + j) = *(img.data + i * widthStep + j);
                    }
                }
                else
                {
                    s32 sum = 0;
                    for(s32 x = i - radius; x <= i + radius ; x++)
                    {
                        for(s32 y = j - radius; y <= j + radius; y++)
                        {
                            s32 m = x - (i - radius);
                            s32 n = y - (j - radius);
                            s32 val1 = *(img.data + x * widthStep + y);
                            s32 val2 = *(ptModel + m * model.cols + n);
                            sum += (val1 * val2);
                        }
                    }

                    *(ptDst + i * dst.cols + j) = sum;
                }
            }
        }
    }
    else if(model.type() == CV_32FC1)
    {
        dst.create(img.rows, img.cols, CV_32FC1);
        f32* ptModel = (f32*)model.data;
        f32* ptDst = (f32*)dst.data;
        for(s32 i = 0; i < img.rows; i++)
        {
            for(s32 j = 0; j < img.cols; j++)
            {
                if(i < radius || i >= (img.rows - radius) || j < radius || j >= (img.cols - radius))
                {
                    if(border == CH_BORDER_ZERO)
                    {
                        *(ptDst + i * dst.cols + j) = 0;
                    }
                    else
                    {
                        *(ptDst + i * dst.cols + j) = *(img.data + i * widthStep + j);
                    }
                }
                else
                {
                    f32 sum = 0;
                    for(s32 x = i - radius; x <= i + radius ; x++)
                    {
                        for(s32 y = j - radius; y <= j + radius; y++)
                        {
                            s32 m = x - (i - radius);
                            s32 n = y - (j - radius);
                            s32 val1 = *(img.data + x * widthStep + y);
                            f32 val2 = *(ptModel + m * model.cols + n);
                            sum += (val1 * val2);
                        }
                    }

                    *(ptDst + i * dst.cols + j) = sum;
                }
            }
        }

    }
    else
    {
        return 5;
    }

    return 0;
}

