
#ifndef  _H_COMMONSTRUCT_H_
#define  _H_COMMONSTRUCT_H_

#include "opencv2/opencv.hpp"
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;
using namespace cv;
using std::vector;
using std::string;

//#define CREATE_CH_DLL
#ifdef CREATE_CH_DLL
    #define CH_DLL_EXPORT	extern "C" __declspec(dllexport)
#else
    #define CH_DLL_EXPORT
#endif

//#define CREATE_CH_CLASS_DLL
#ifdef CREATE_CH_CLASS_DLL
    #define CH_CLASS_DLL_EXPORT	__declspec(dllexport)
#else
    #define CH_CLASS_DLL_EXPORT
#endif

#define  IN
#define  OUT

#ifndef MAX
    #define MAX(a, b)			((a)>=(b) ? (a):(b))
#endif

#ifndef MIN
    #define MIN(a, b)			((a)<(b) ? (a):(b) )
#endif

#ifndef ABS
    #define ABS(a)				((a)>0 ? (a): -(a))
#endif

#ifndef PI
    #define PI	3.1415926
#endif

typedef  char				s8;
typedef  short				s16;
typedef  int				s32;
typedef  unsigned char		u8;
typedef  unsigned short		u16;
typedef  unsigned int		u32;
typedef  float				f32;
typedef  double				f64;

typedef struct TPoint
{
    s32 x;
    s32 y;
} TPoint;

typedef struct TargetInfo
{
    s32 width;
    s32 height;
    s32 count;
    f32 AreaRatio;
    f32 whRatio;
    s32 xMin;
    s32 yMin;
    s32 xMax;
    s32 yMax;
    Point left;
    Point top;
    Point right;
    Point bottom;
    Rect rt;
    vector<Point> objArea;
} TargetInfo;

typedef struct TRect
{
    s32 top;
    s32 bottom;
    s32 left;
    s32 right;
} TRect;

typedef struct TRect2
{
    s32 xMin;
    s32 yMin;
    s32 xMax;
    s32 yMax;
} TRect2;

typedef struct TPair
{
    s32 first;
    s32 sencond;
} TPair;

typedef struct TagFrameInfo
{
    long timestamp;
    s32 width;
    s32 height;
    s32 depth;
    u8* imageBuf;
} TFrameInfo;

#define IMGWIDTH	640
#define IMGHEIGHT	480

#define MAX_MOVING_OBJECTS	200
#define MAX_COORDINATE_NUM  100

typedef struct TagObjectInfo
{
    s32 min_x;										/* 目标块外接矩形最小的X坐标 */
    s32 max_x;										/* 目标块外接矩形最大的X坐标 */
    s32 min_y;										/* 目标块外接矩形最小的y坐标  */
    s32 max_y;										/* 目标块外接矩形最大的y坐标 */
    s32 coordinaterNum;								/* 目标历史记录数目 */
    TPoint coordinateArray[MAX_COORDINATE_NUM];		/* 目标运动轨迹中心点的纪录 */
    s32 mean_x;
    s32 mean_y;
} TObjectInfo;

/* 检测返回数据 */
typedef struct TagTargetInfo
{
    s32 nTarget;
    TObjectInfo TargetList[MAX_MOVING_OBJECTS];  /* 返回块 */
} TTargetInfoSet;

typedef struct
{
    u32 Handle;
    Mat frame;
} TCallbackData;

typedef s32 (*MT_CallBackFunc)(TCallbackData* val);

enum
{
    CH_OK = 0,
    CH_ERROR = 1
};

#endif
