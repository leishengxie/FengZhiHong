#ifndef _H_BW_LABEL_H_
#define _H_BW_LABEL_H_

#include "CommonInterface.h"

/***********************************************
 * 函数：bwlabel
 * 功能：二值图像标记，返回标记目标的坐标
 * 参数：
 *   bw			二值图像
 *   MinArea	目标最小面积（像素个数）
 *   target		目标集合
 ***********************************************/
CH_DLL_EXPORT
s32 bwlabel(IN const Mat bw,
            IN s32 MinArea,
            OUT vector<TargetInfo> & target);


/***********************************************
* 函数：TargetMerge
* 功能：目标合并处理
* 参数：
*	SrcTargets	输入目标
*	DstTargets	输出目标
***********************************************/
CH_DLL_EXPORT
s32 TargetMerge(IN const vector<TargetInfo> & SrcTargets,
                OUT vector<TargetInfo> & DstTargets);

/***********************************************
* 函数：TargetMerge
* 功能：目标合并处理
* 参数：
*	SrcTargets	输入目标
*	DstTargets	输出目标
***********************************************/
CH_DLL_EXPORT
s32 TargetMerge1(IN const vector<TargetInfo> & SrcTargets,
                 OUT vector<TargetInfo> & DstTargets);


/***********************************************
* 函数：TargetMerge2
* 功能：目标合并处理（准确）
* 参数：
*	SrcTargets	输入目标
*	DstTargets	输出目标
***********************************************/
CH_DLL_EXPORT
s32 TargetMerge2(IN const vector<TargetInfo> & SrcTargets,
                 OUT vector<TargetInfo> & DstTargets);


/***********************************************
* 函数：TargetMerge3
* 功能：目标合并处理（准确）
* 参数：
*	SrcTargets	输入目标
*	DstTargets	输出目标
***********************************************/
CH_DLL_EXPORT
s32 TargetMerge3(IN const vector<TargetInfo> & SrcTargets,
                 OUT vector<TargetInfo> & DstTargets);



/***********************************************
* 函数：GetTargetsMask
* 功能：获取目标掩码
* 参数：
*	src			原始二值图像
*	targets		目标信息
*   mask		包含目标的掩码图像
***********************************************/
CH_DLL_EXPORT
s32	GetTargetsMask(IN const Mat src,
                   IN const vector<TargetInfo> & targets,
                   OUT Mat & mask);


/***********************************************
* 函数：GetTargetsRect
* 功能：获取目标掩码
***********************************************/
CH_DLL_EXPORT
s32 GetTargetsRect(IN const vector<TargetInfo> & targets,
                   OUT Rect & rt);


/***********************************************
* 函数：TargetToRect
* 功能：目标转化为矩形框
***********************************************/
CH_DLL_EXPORT
s32 TargetToRect(IN const vector<TargetInfo> & targets,
                 OUT vector<Rect> & vRt);


/***********************************************
* 函数：GetTargetsImg
* 功能：获取目标子图像集合
***********************************************/
CH_DLL_EXPORT
s32 GetTargetsImg(IN Mat img,
                  IN const vector<TargetInfo> & targets,
                  OUT vector<Mat> & vImg);


/***********************************************
* 函数：TargetFilter
* 功能：目标过滤
***********************************************/
CH_DLL_EXPORT
s32 TargetFilter(IN const vector<TargetInfo> & srcTargets,
                 OUT vector<TargetInfo> & dstTargets,
                 IN s32 minArea = 10,
                 IN f32 AreaRatio = 0.0,
                 IN f32 whRatio = 0.0);


CH_DLL_EXPORT
s32 Target2to1(IN TargetInfo & target1,
               IN TargetInfo & target2,
               IN TargetInfo & dstTarget);


#endif

