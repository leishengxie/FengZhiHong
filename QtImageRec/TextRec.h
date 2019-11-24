
#ifndef _H_TEXT_REC_H_
#define _H_TEXT_REC_H_

#include "CommonInterface.h"

///
/// \brief CharacterSegmentation    字符分割
/// \param raw
/// \param OutBw
/// \param OutDst
/// \param wordcount
/// \return
///
s32 CharacterSegmentation(Mat & raw, Mat & OutBw, Mat & OutDst, int* wordcount);

s32 TopBottomMerge(vector<TargetInfo> src, s32 stdWidth, s32 stdHeight, vector<TargetInfo> & dst);
s32 LeftRightMerge(vector<TargetInfo> & src, s32 stdWidth, s32 stdHeight, vector<TargetInfo> & dst);

#endif
