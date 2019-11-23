//#include "stdafx.h"
#include "ImgSegAlg.h"
#include "MorOperationAlg.h"
#include "ImageProcess.h"

/******************************************************************************
* 函数：chThreshold
* 参数：
*	img		灰度图像
*	level	分割阈值
*	bg		图像背景
*	flag	类型：目标亮色：CH_THRESHOLD 目标暗色：CH_THRESHOLD_INV
* 原理：
*	1. 目标为亮色时，如果f(x,y) >= 阈值，则f(x,y)= 255, 否则f(x,y)=0；
*	2. 目标为暗色时，如果f(x,y) <= 阈值，则f(x,y)= 255, 否则f(x,y)=0；
********************************************************************************/
CH_DLL_EXPORT
s32 chThreshold(IN Mat img, IN u32 level, OUT Mat& bw, IN s32 flag)
{
    // 输入检测
    if(img.empty())
        return -1;

    if(level <0 || level > 255)
        return -1;

    // 图像通道检测
    Mat grayImg;
    if( img.channels() == 1)
        grayImg = img;
    else if(img.channels() == 3)
        chBGR2Gray(img, grayImg);

    // 阈值分割
    bw.create(grayImg.rows, grayImg.cols, CV_8UC1);
    if(flag == CH_THRESHOLD)
    {
        for(s32 i=0; i<grayImg.rows; i++)
        {
            u8* ptGray = grayImg.ptr<u8>(i);
            u8* ptBw = bw.ptr<u8>(i);
            for(s32 j=0; j<grayImg.cols; j++)
            {
                if( ptGray[j] >= level)
                    ptBw[j] = 255;
                else
                    ptBw[j] = 0;
            }
        }
    }
    else if(flag == CH_THRESHOLD_INV)
    {
        for(s32 i=0; i<grayImg.rows; i++)
        {
            u8* ptGray = grayImg.ptr<u8>(i);
            u8* ptBw = bw.ptr<u8>(i);
            for(s32 j=0; j<grayImg.cols; j++)
            {
                if( ptGray[j] <= level)
                    ptBw[j] = 255;
                else
                    ptBw[j] = 0;
            }
        }
    }

    return 0;
}


/******************************************************************************
* 函数：OtsuMethod
* 参数：基于最大类间方差的阈值分割方法
*   img			 图像数据
*   threshold    图像阈值
* 原理：
*	1. 检测图像是否为灰度图像，如果不是则将彩色图片转换为灰度图片；
*	2. 图像的直方图统计；
*	3. 计算直方图的累积概率P(k)；
*	4. 计算像素的累加均值m(k) = ∑(i*P(i))，i属于[0, k]；
*	5. 计算像素的全局均值mG = ∑(i*P(i))，i属于[0, L-1]；
*   6. 计算类间方差taoB(k) = (mG*P1(k) - m(k))^2/(P1(k)*(1-P1(k)))，k属于[0, L-1]；
*	7. 取taoB(k)中的最大值所对应的k,作为分割阈值；
********************************************************************************/
CH_DLL_EXPORT
s32 OtsuMethod(IN const Mat& img, OUT u8& threshold)
{
    // 输入检测
    if(img.empty())
        return -1;

    Mat grayImg;
    if(img.channels()==1)
    {
        grayImg = img;
    }
    else if(img.channels()==3)
    {
        chBGR2Gray(img, grayImg);
    }

    vector<f32> histArr(256, 0.0);
    u8 val = 0;
    s32 width = grayImg.cols;
    s32 height = grayImg.rows;
    s32 widthStep = grayImg.step;

    /* 直方图统计 */
    for(s32 i=0; i<height; i++)
    {
        for(s32 j=0; j<width; j++)
        {
            val = *(grayImg.data + i*widthStep + j);
            histArr[val]++;
        }
    }

    for(s32 i=0; i<256; i++)
    {
        histArr[i] /= (width*height) ;
    }

    /* 累积概率 */
    vector<f32> Prob(256, 0.0);
    for(s32 i=0; i<256; i++)
    {
        for(s32 j=0; j<=i; j++)
        {
            Prob[i] += histArr[j] ;
        }
    }

    /* mk */
    vector<f32> mk(256, 0.0);
    for(s32 i=0; i<256; i++)
    {
        for(s32 j=0; j<=i; j++)
        {
            mk[i] += j*histArr[j];
        }
    }

    /* mG */
    f32 mG = mk[255];
    vector<f32> taoB(256, 0.0);
    for(s32 i=0; i<256; i++)
    {
        if( histArr[i]>0 && histArr[i]<1)
            taoB[i] = (mG*Prob[i] - mk[i])*(mG*Prob[i] - mk[i])/(Prob[i]*(1-Prob[i])) ;
        else
            taoB[i] = 0;
    }

    /* 最大类间方差排序 */
    f32 MaxtaoB = 0.0;
    for(s32 i=0; i<256; i++)
    {
        if(taoB[i] > MaxtaoB)
        {
            MaxtaoB = taoB[i];
            threshold = i;
        }
    }

    return 0;
}


/******************************************************************************
* 函数：OtsuMethod2
* 参数：基于最大类间方差的阈值分割方法
*    img		  图像数据
*    binImg		  输出二值图
*    flag		  CH_THRESHOLD:目标为亮色;
                  CH_THRESHOLD_INV:目标为暗色
********************************************************************************/
CH_DLL_EXPORT
s32 OtsuMethod2(IN const Mat& img,
                 OUT Mat& binImg,
                 IN s32 flag)
{
    // 输入检测
    if(img.empty())
        return -1;

    Mat grayImg;
    if(img.channels() == 1)
        grayImg = img;
    else if(img.channels() == 3)
        cvtColor(img, grayImg, CV_BGR2GRAY);

    u8 level;
    OtsuMethod(grayImg, level);
    chThreshold(grayImg, level, binImg, flag);

    return 0;
}


/********************************************************************************
* 函数：ImgSubBlocksThreshold
* 功能：基于图像分块的阈值分割方法，用于应对光照不均匀的情况
* 参数：
*    img		灰度图像数据
*    len1      图像子块的行
*    len2		图像子块的列
*    mask		分割后的二值图像
* 原理：
*	1. 按照图像分块的数目，对每个子区域使用自动阈值分割算法，得出子区域阈值；
*	2. 对应每个区域，按照子区域的阈值进行分割；
*********************************************************************************/
s32 OtsuMethodForBlocks(IN const Mat& img, OUT Mat& mask,
                        IN int len1, IN int len2, IN int flag )
{
    // 输入检测
    if(img.empty())
        return -1;

    if(len1 <=0 || len2 <=0)
        return -1;

    int m = img.rows;
    int n = img.cols;
    Mat A;

    // 图像通道检测
    if(img.channels() == 1)
        A = img;
    else if(img.channels() == 3)
        chBGR2Gray(img, A);

    int nRows, nCols;
    nRows = (m - (m%len1))/len1;
    nCols = (n - (n%len2))/len2;

    vector<u8> level;
    for(int i=0; i<len1; i++)
    {
        for(int j=0; j<len2; j++)
        {
            Rect rt;
            rt.x = j*nCols;
            rt.y = i*nRows;
            rt.width = nCols;
            rt.height = nRows;

            Mat temp = A(rt);
            u8 tempLevel;

            OtsuMethod(temp, tempLevel);
            level.push_back(tempLevel);
        }
    }

    Mat B = Mat::zeros(m, n, CV_8UC1);
    for(int i=0; i<m; i++)
    {
        u8* ptA = A.ptr<u8>(i);
        u8* ptB = B.ptr<u8>(i);
        for(int j=0; j<n; j++)
        {
            int ilabel = 0;
            int jlabel = 0;
            for(int k=0; k<len1; k++)
            {
                if( i>=k*nRows && i<(k+1)*nRows )
                {
                    ilabel = k;
                    break;
                }
            }

            for(int k=0; k<len2; k++)
            {
                if( j>=k*nCols && j<(k+1)*nCols)
                {
                    jlabel = k;
                    break;
                }
            }

            u8 indexLevel = level[ilabel*len2 + jlabel];
            if(flag == THRESH_BINARY)
            {
                if( ptA[j] > indexLevel)
                {
                    ptB[j] = 255;
                }
            }
            else if(flag == THRESH_BINARY_INV)
            {
                if( ptA[j] <= indexLevel)
                {
                    ptB[j] = 255;
                }
            }
        }
    }

    mask = B;
    return 0;
}


/*******************************************************************************
* 函数：chSobel
* 功能：Sobel算子检测
* 原理：
*	1. Sobel算子是图像的一阶导数，即是图像的梯度；
*	2. x方向的梯度算子：
*			-1	-2	-1
*			0	0	0
*			1	2	2
*	3. y方向的梯度算子：
*			-1	0	1
*			-2	0	2
*			-1	0	1
********************************************************************************/
CH_DLL_EXPORT
s32 chSobel(IN Mat& img, OUT Mat& dst)
{
    // 输入检测
    if(img.empty())
        return -1;

    Mat grayImg;
    if(img.channels() == 1)
        grayImg = img;
    else if(img.channels() == 3)
        chBGR2Gray(img, grayImg);

#if 1
    s32 xVec[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    s32 yVec[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    Mat xModel(3, 3, CV_32SC1, xVec);
    Mat yModel(3, 3, CV_32SC1, yVec);

    Mat xDst, yDst;
    chImfilter2(grayImg, xModel, xDst, CH_BORDER_ZERO);
    chImfilter2(grayImg, yModel, yDst, CH_BORDER_ZERO);

    dst.create(grayImg.rows, grayImg.cols, CV_8UC1);
    for(s32 i=0; i<dst.rows; i++)
    {
        s32* ptxDst = xDst.ptr<s32>(i);
        s32* ptyDst = yDst.ptr<s32>(i);
        u8* ptDst = dst.ptr<u8>(i);
        for(s32 j=0; j<dst.cols; j++)
        {
            s32 val1 = ABS(ptxDst[j]);
            s32 val2 = ABS(ptyDst[j]);
            s32 val3 = (val1 >> 1) + (val2 >> 1);
            ptDst[j] = val3 > 255 ? 255 : val3;
        }
    }
#else

    Mat GradX, GradY;
    Mat AbsGradX, AbsGradY;
    int scale = 1;
    int delta = 0;

    Sobel(grayImg, GradX, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(GradX, AbsGradX);

    Sobel(grayImg, GradY, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(GradY, AbsGradY);

    addWeighted(AbsGradX, 0.5, AbsGradY, 0.5, 0, dst);
#endif

    return CH_OK;
}


/*******************************************************************************
* 函数：chSobelX
* 功能：在X方向的Sobel算子检测
* 原理：
* 原理：
*	1. Sobel算子是图像的一阶导数，即是图像的梯度；
*	2. x方向的梯度算子：
*			-1	-2	-1
*			0	0	0
*			1	2	2
********************************************************************************/
CH_DLL_EXPORT
s32 chSobelX(IN Mat& img, OUT Mat& dst)
{
    // 输入检测
    if(img.empty())
        return -1;

    Mat grayImg;
    if(img.channels() == 1)
        grayImg = img;
    else if(img.channels() == 3)
        chBGR2Gray(img, grayImg);

    s32 xVec[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    Mat xModel(3, 3, CV_32SC1, xVec);

    Mat xDst;
    chImfilter2(grayImg, xModel, xDst, CH_BORDER_ZERO);

    dst.create(grayImg.rows, grayImg.cols, CV_8UC1);
    for(s32 i=0; i<dst.rows; i++)
    {
        s32* ptxDst = xDst.ptr<s32>(i);
        u8* ptDst = dst.ptr<u8>(i);
        for(s32 j=0; j<dst.cols; j++)
        {
            s32 val1 = ABS(ptxDst[j]);
            ptDst[j] = val1 > 255 ? 255 : val1;
        }
    }

    return 0;
}


/*******************************************************************************
* 函数：chSobelY
* 功能：在Y方向的Sobel算子检测
********************************************************************************/
CH_DLL_EXPORT
s32 chSobelY(IN Mat& img, OUT Mat& dst)
{
    // 输入检测
    if(img.empty())
        return -1;

    Mat grayImg;
    if(img.channels() == 1)
        grayImg = img;
    else if(img.channels() == 3)
        chBGR2Gray(img, grayImg);

    s32 yVec[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    Mat yModel(3, 3, CV_32SC1, yVec);

    Mat yDst;
    chImfilter2(grayImg, yModel, yDst, CH_BORDER_ZERO);

    dst.create(grayImg.rows, grayImg.cols, CV_8UC1);
    for(s32 i=0; i<dst.rows; i++)
    {
        s32* ptyDst = yDst.ptr<s32>(i);
        u8* ptDst = dst.ptr<u8>(i);
        for(s32 j=0; j<dst.cols; j++)
        {
            s32 val2 = ABS(ptyDst[j]);
            ptDst[j] = val2 > 255 ? 255 : val2;
        }
    }

    return 0;
}




/*********************************************************************************
* 函数：ImgEdgeCheck
* 功能：边缘检测算法
* 参数
*    img		图像数据
*    type		操作类型
*    dst        检测结果
**********************************************************************************/
CH_DLL_EXPORT
s32 EdgeDetection(IN const Mat& img, OUT Mat& dst,
                  IN int type,
                  IN s32 lowThresh,
                  IN s32 highThresh)
{
    // 输入检测
    if(img.empty())
        return -1;

    if(lowThresh > highThresh)
        return -1;

    Mat temp;
    Mat grayImg;

    if(img.channels() == 1)
        grayImg = img;
    else if(img.channels() == 3)
        cvtColor(img, grayImg, CV_BGR2GRAY);

    // 处理
    if(type == CH_SOBEL)
    {
        Mat GradX, GradY;
        Mat AbsGradX, AbsGradY;
        int scale = 1;
        int delta = 0;

        Sobel(grayImg, GradX, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
        convertScaleAbs(GradX, AbsGradX);

        Sobel(grayImg, GradY, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);
        convertScaleAbs(GradY, AbsGradY);

        addWeighted(AbsGradX, 0.5, AbsGradY, 0.5, 0, dst);
    }
    else if(type == CH_LAPLACIAN)
    {
        Mat temp, AbsDst;
        Laplacian(grayImg, temp, CV_16S, 3, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(temp, AbsDst);
        dst = AbsDst;
    }
    else if(type == CH_CANNY)
    {
        Canny(grayImg, dst, lowThresh, highThresh, 3);
    }

    return 0;
}


CH_DLL_EXPORT
s32 HoughCircleTransform(IN const Mat& img,
                         OUT Mat& dst)
{
    // 输入检测
    if(img.empty())
        return -1;

    Mat GrayImg;
    if(img.channels() == 3)
        cvtColor(img, GrayImg, CV_BGR2GRAY);
    else if(img.channels() == 1)
        GrayImg = img;

    GaussianBlur(GrayImg, GrayImg, Size(9, 9), 2, 2);

    vector<Vec3f> circles;

    HoughCircles(GrayImg, circles, CV_HOUGH_GRADIENT, 1, GrayImg.rows/8, 200, 100, 0, 0);

    dst = img;
    for(size_t i=0; i<circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        circle(dst, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        circle(dst, center, radius, Scalar(0,0,255), 3, 8, 0);
    }

    return 0;
}


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
                       OUT Mat& dst)
{
    Canny(img, dst, 50, 200, 3);

    vector<Vec4i> lines;

    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10);

    for(u32 i=0; i<lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(200), 2 );
    }

    return 0;
}


///////////////////////////////////////////////////////////////////////////
// 历史接口版本，已不用
#if 0

/***********************************************
* 函数：EdgeBasedTargetDetect
* 功能：基于边缘的目标检测
* 输入：
*    img		图像数据
* 输出：
*    dst        检测结果
***********************************************/
CH_DLL_EXPORT
    s32 TargetDectEB(IN const Mat& img, OUT Mat& dst )
{
    // 输入检测
    if(img.empty())
        return -1;

    Mat temp, temp2, temp3;
    u8 level;

    // 边缘检测
    EdgeDetection(img, temp, CH_SOBEL);	// CH_LAPLACIAN_ALG

    // 自动阈值分割
    OtsuMethod(temp, level);
    threshold(temp, temp2, (level-20), 255, THRESH_BINARY);

    // 形态学操作
    chMorOp(temp2, temp3, CH_MOR_CLOSE, Size(15, 15), CH_ELE_RECT);

    chHoleFilling(temp3, temp3);

    chMorOp(temp3, temp3, CH_MOR_OPEN, Size(3, 3), CH_ELE_RECT);

    dst = temp3;

    return 0;
}

/***********************************************
* 函数：GetImageBackground
* 参数：
*    img	灰度图像
*    bg    图像背景
***********************************************/
CH_DLL_EXPORT
    s32 ImageBackGround(IN const Mat& img, OUT Mat& bg)
{
    // 输入检测
    if(img.empty())
        return -1;

    /* 获取结构元素 */
    s32 morpSize = 15;
    Mat element = getStructuringElement(MORPH_RECT, Size(2*(morpSize-1)+1, 2*(morpSize-1)+1));

    /* 开操作 */
    morphologyEx(img, bg, MORPH_OPEN, element);
    return 0;
}


/***********************************************
* 函数：ImgSegNouniformIllumination
* 参数：
*    img		图像数据
*    binImg		二值图像
***********************************************/
CH_DLL_EXPORT
    void ImgSegNouniformIllumination(IN const Mat& img,
    OUT Mat& binImg)
{
    Mat bg, tmp1, tmp2, tmp3, tmp4;
    u8 thresh;

    /* 获取图像背景 */
    ImageBackGround(img, bg);

    /* 减背景，去除不均匀光照影响 */
    subtract(img, bg, tmp1);

    /* 对比度增强 */
    tmp1.convertTo(tmp2, -1, 2);

    /* 获取最佳全局阈值 */
    OtsuMethod(tmp2, thresh);

    /* 阈值分割 */
    threshold(tmp2, binImg, thresh, 255, THRESH_BINARY) ;

    return ;
}

#endif
