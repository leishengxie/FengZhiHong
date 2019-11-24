
#ifndef _H_IMAGE_PROCESS_H_
#define _H_IMAGE_PROCESS_H_

#include "CommonInterface.h"

enum
{
    CH_INTER_NEAREST = 0,
    CH_INTER_LINEAR = 1,
    CH_INTER_CUBIC = 2
};

enum
{
    CH_BORDER_ZERO = 0,
    CH_BORDER_PIXEL = 1
};

/***************************************************
 * 函数名：chSetMat
 * 功能：设置图像为固定值
 * 说明：
 * 可以直接使用Mat中的重载符，例如：
 *  Mat img(100, 100, CV_8UC3);
 *  img = Scalar(0, 0, 255);
 ***************************************************/
CH_DLL_EXPORT
s32 chSetMat(IN Mat & img, IN Scalar s);


/***************************************************
 * 函数名：chSetMatInv
 * 功能  ： 图像取反
 ***************************************************/
CH_DLL_EXPORT
s32 chSetMatInv(IN Mat img, OUT Mat & dst);


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
u8 chGetPixel(IN Mat & img, IN s32 iRows, IN s32 jCols, IN s32 iChannels = 0);


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
s32 chSetPixel(IN u8 val, IN OUT Mat & img, IN s32 iRows, IN s32 jCols, IN s32 iChannels = 0);


/***************************************************
 * 函数名：chBwRowSum
 * 功能  ：二值图像行求和( 白点数目)
 ***************************************************/
CH_DLL_EXPORT
s32 chBwRowSum(IN Mat img, OUT vector<s32> & vRowSum);


/***************************************************
 * 函数名：chBwColSum
 * 功能  ：二值图像列求和（白点数目）
 ***************************************************/
CH_DLL_EXPORT
s32 chBwColSum(IN Mat img, OUT vector<s32> & vColSum);


/***************************************************
 * 函数名：chGrayRowSum
 * 功能  ：灰度图像行求和
 ***************************************************/
CH_DLL_EXPORT
s32 chGrayRowSum(IN Mat img, OUT vector<s32> & vRowSum);


/***************************************************
 * 函数名：chGrayColsum
 * 功能  ：灰度图像列求和
 ***************************************************/
CH_DLL_EXPORT
s32 chGrayColSum(IN Mat img, OUT vector<s32> & vColSum);


/**********************************************************
 * 函数名：chHist
 * 功能 ：直方图统计
 * 参数：
 *	src				输入灰度图像
 *  vCounts			直方图统计结果
***********************************************************/
CH_DLL_EXPORT
s32 chHist(IN Mat src, OUT vector<s32> & vCounts );


// 直方图显示
CH_DLL_EXPORT
s32 chHistImage(Mat src, Mat & dst );


/****************************************************
 * 函数名：ImageFilter2
 * 功能： 图像直方图等级统计，主要用于检测出直方图等级小于某一阈值的图像
 * 返回值：
 *  1：满足要求； 0：不满足要求
 ****************************************************/
CH_DLL_EXPORT
s32 ImageHistLevelCheck(IN Mat grayImg, IN s32 thresh);


/******************************************************
 * 函数名：chResize
 * 功能  ： 图像缩放，将图像按比例缩放到固定像素大小
 *
 ******************************************************/
CH_DLL_EXPORT
s32 chResize2(IN Mat grayImg, OUT Mat & sizeImg, IN s32 pixelLimit, OUT f32 & ratio);


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
                    IN s32 iBorder = 30,
                    IN s32 jBorder = 10);


/******************************************************
 * 函数名：chGetEqualWHImage
 * 功能  ： 获取等比例图像
 * 参数：
 *	src		原始图像
 *	dst		等比例图像
 *	pt		等比例图像中数据起点
 ******************************************************/
CH_DLL_EXPORT
s32 chGetEqualWHImage(IN Mat src, Mat & dst, Point & pt);


/******************************************************
 * 函数名：chBGR2Gray
 * 功能： 彩色转灰度
 * 说明：
 ******************************************************/
CH_DLL_EXPORT
s32 chBGR2Gray(IN Mat ColorImg, OUT Mat & GrayImg);


/******************************************************
 * 函数名：chResize
 * 功能： 图像缩放
 * 说明：
 ******************************************************/
CH_DLL_EXPORT
s32 chResize(IN Mat & img, OUT Mat & sizeImg,
             IN Size sz,
             IN s32 type = CH_INTER_NEAREST);


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
 ************************************************************************************/
CH_DLL_EXPORT
s32 chImfilter2(IN Mat & img, IN Mat & model, OUT Mat & dst, IN s32 border = CH_BORDER_ZERO);



#endif
