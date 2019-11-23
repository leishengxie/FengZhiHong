
#ifndef _H_MOR_OPERATION_H_
#define _H_MOR_OPERATION_H_

#include "CommonInterface.h"

/* 形态学操作类型 */
enum { CH_MOR_ERODE=0,
       CH_MOR_DILATE=1,
       CH_MOR_OPEN=2,
       CH_MOR_CLOSE=3 };


/* 结构元素类型  */
enum { CH_ELE_RECT=0,
       CH_ELE_CROSS=1,
       CH_ELE_ELLIPSE=2 };


/* 结构元素尺寸 */
enum { CH_ELE_3X3=0,
       CH_ELE_5X5=1,
       CH_ELE_7X7=2,
       CH_ELE_9X9=3,
       CH_ELE_11X11=4,
       CH_ELE_13X13=5,
       CH_ELE_15X15=6,
       CH_ELE_21X21=7,
       CH_ELE_31X31=8,
       CH_ELE_41X41=9,
       CH_ELE_61X61=10,
       CH_ELE_81X81=11,
       CH_ELE_101X101=12
    };


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
s32 chMorOp(IN Mat src, OUT Mat& dst, IN int type,
            IN Size StructSize = Size(3,3),
            IN int StructEle = CH_ELE_RECT );


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
s32 chMorOp2(IN Mat src, OUT Mat& dst, IN int type,
             IN int StructSize = CH_ELE_3X3,
             IN int StructEle = CH_ELE_RECT);


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
s32 chBorderExtract(IN Mat src, OUT Mat& dst,
                    IN int StructSize = CH_ELE_3X3,
                    IN int StructEle = CH_ELE_RECT);


/**********************************************************
 * 函数名：chHoleFilling
 * 功能 ：孔洞填充
***********************************************************/
CH_DLL_EXPORT
s32 chHoleFilling(IN Mat src, OUT Mat& dst);


#endif

