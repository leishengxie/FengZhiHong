
#ifndef  _H_IMGSEGMENT_H_
#define  _H_IMGSEGMENT_H_

#include "CommonInterface.h"

enum
{
    CH_SOBEL = 0,
    CH_LAPLACIAN = 1,
    CH_CANNY = 2,
};

enum
{
    CH_THRESHOLD=0,
    CH_THRESHOLD_INV=1
};

/******************************************************************************
* 函数：chThreshold
* 参数：
*	img		灰度图像
*	level	分割阈值
*	bg		图像背景
*	flag	类型：目标亮色：CH_THRESHOLD 目标暗色：CH_THRESHOLD_INV
********************************************************************************/
CH_DLL_EXPORT
s32 chThreshold(IN Mat img, IN u32 level, OUT Mat& bw, IN s32 flag = CH_THRESHOLD);


/******************************************************************************
* 函数：OtsuMethod
* 参数：基于最大类间方差的阈值分割方法
*   img			 图像数据
*   threshold    图像阈值
********************************************************************************/
CH_DLL_EXPORT
s32 OtsuMethod(IN const Mat& img, OUT u8& threshold);


/******************************************************************************
* 函数：OtsuMethod2
* 参数：基于最大类间方差的阈值分割方法
*    img		  图像数据
*    binImg		  输出二值图
*    flag		  CH_THRESHOLD:目标为亮色;
                  CH_THRESHOLD_INV:目标为暗色
********************************************************************************/
CH_DLL_EXPORT
s32 OtsuMethod2(IN const Mat& img, OUT Mat& binImg, IN s32 flag = CH_THRESHOLD);


/*******************************************************************************
* 函数：OtsuMethodForBlocks
* 功能：基于图像分块的阈值分割方法，用于应对光照不均匀的情况
* 输入：
*    img		图像数据
*    len1      图像子块的行
*    len2		图像子块的列
* 输出：
*    mask		分割后的二值图像
********************************************************************************/
CH_DLL_EXPORT
s32 OtsuMethodForBlocks(IN const Mat& img,
                         OUT Mat& mask,
                         IN int len1 = 4,
                         IN int len2 = 4,
                         IN int flag = THRESH_BINARY);


/*******************************************************************************
* 函数：chSobel
* 功能：Sobel算子检测
********************************************************************************/
CH_DLL_EXPORT
s32 chSobel(IN Mat& img, OUT Mat& dst);


/*******************************************************************************
* 函数：chSobelX
* 功能：在X方向的Sobel算子检测
********************************************************************************/
CH_DLL_EXPORT
s32 chSobelX(IN Mat& img, OUT Mat& dst);


/*******************************************************************************
* 函数：chSobelY
* 功能：在Y方向的Sobel算子检测
********************************************************************************/
CH_DLL_EXPORT
s32 chSobelY(IN Mat& img, OUT Mat& dst);


/***********************************************
* 函数：ImgEdgeCheck
* 功能：边缘检测算法
* 输入：
*    img		图像数据
*    type		操作类型
* 输出：
*    dst        检测结果
***********************************************/
CH_DLL_EXPORT
s32 EdgeDetection(IN const Mat& img, OUT Mat& dst,
                  IN int type = CH_CANNY,
                  IN s32 lowThresh = 50,
                  IN s32 highThresh = 125);


/***********************************************
* 函数：HoughCircleTransform
* 功能：霍夫圆变化
* 输入：
*    img		图像数据
* 输出：
*    dst        检测结果
***********************************************/
CH_DLL_EXPORT
s32 HoughCircleTransform(IN const Mat& img,
                         OUT Mat& dst);


/***********************************************
* 函数：HoughLineTransform
* 功能：霍夫圆变化
* 输入：
*    img		图像数据
* 输出：
*    dst        检测结果
***********************************************/
CH_DLL_EXPORT
s32 HoughLineTransform(IN const Mat& img,
                       OUT Mat& dst);


#if 0
/***********************************************
* 函数：ImageBackGround
* 参数：
*	img	灰度图像
*	bg  图像背景
* 说明：主要采用开操作，后期被替换
***********************************************/
CH_DLL_EXPORT
    s32 ImageBackGround(IN const Mat& img, OUT Mat& bg);
#endif

#endif

