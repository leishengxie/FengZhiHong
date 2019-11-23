
#ifndef _H_TEXT_REC_H_
#define _H_TEXT_REC_H_

#include <fstream>
#include "CommonInterface.h"

/************************************************
 * 函数名：CharacterSegmentation
 * 功能：字符分割
 *
 ************************************************/
//s32 CharacterSegmentation();
s32 CharacterSegmentation(Mat& raw, Mat& OutBw, Mat& OutDst, int *wordcount);


#endif
