
#ifndef _H_COMMON_INTERFACE_H_
#define _H_COMMON_INTERFACE_H_

#include "CommonStruct.h"

#define CH_SORT_ASCENDING		0
#define CH_SORT_DESCENDING		1

/***************************************************
 * 函数名：chImshow
 * 功能  ：多图显示，可同时显示1-5张图片
 * 说明  ：无限等待
 ***************************************************/
CH_DLL_EXPORT
void chImshow(Mat img1,
              Mat img2 = Mat::zeros(2, 2, CV_8UC1),
              Mat img3 = Mat::zeros(3, 3, CV_8UC1),
              Mat img4 = Mat::zeros(4, 4, CV_8UC1),
              Mat img5 = Mat::zeros(5, 5, CV_8UC1));


/***************************************************
 * 函数名：chImshow1
 * 功能  ：图像显示
 * 说明  ：无等待
 *	CV_WINDOW_AUTOSIZE	不可缩放
 *  CV_WINDOW_NORMAL	可缩放
 ***************************************************/
CH_DLL_EXPORT
void chImshow1(string str, Mat img, s32 flag = CV_WINDOW_AUTOSIZE);


/***************************************************
 * 函数名：chImshowTargets
 * 功能  ：显示图像目标区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowTargets(Mat img,
                    const vector<TargetInfo> & targets,
                    bool writeFlag = false);

/***************************************************
 * 函数名：chImshowTargets
 * 功能  ：显示图像目标区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowTargetsImg(Mat img,
                       const vector<TargetInfo> & targets,
                       Mat & dst);

/***************************************************
 * 函数名：chImshowTarget_Single
 * 功能  ：显示图像单个目标区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowTarget_Single(Mat img,
                          TargetInfo targets,
                          bool writeFlag = false);


/***************************************************
 * 函数名：chImshowRects
 * 功能  ：显示图像矩形区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowRects(Mat img, vector<Rect> vRects);


/***************************************************
 * 函数名：chImshowRect_Single
 * 功能  ：显示图像单个矩形区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowRect_Single(Mat img, Rect rt);


CH_DLL_EXPORT
s32 GrayImgColorRect(Mat grayImg, Rect rt, Mat & dst);

/*******************************************************
 * 函数名： VisualImgs
 * 功能： 缩略图
 * 参数：
 *	iSubImgW, iSubImgH		子图像宽、高
 *	cols, rows,				缩略图行列
 *  iGap					子图像间隔
 *******************************************************/
CH_DLL_EXPORT
s32 chThumbnail(IN vector<Mat> vImg,
                OUT Mat & dst,
                IN s32 iSubImgW = 64,
                IN s32 iSubImgH = 64,
                IN s32 cols = 10,
                IN s32 rows = 10,
                IN s32 iGap = 2);


/***************************************************
 * 函数名：chNormDist
 * 功能  ：两点间距离计算
 ***************************************************/
CH_DLL_EXPORT
f32 chNormDist(Point pt1, Point pt2);


/***************************************************
 * 函数名：chImgFileCheck
 * 功能  ：图像文件类型检测
 * 参数
 *	strFileName		文件路径
 * 返回值
 *	1:是图像;		0:不是图像
 ***************************************************/
CH_DLL_EXPORT
s32 chImgFileCheck(string strFileName);


/***************************************************
 * 函数名：chSearchDir
 * 功能  ：搜索目录中的文件
 * 参数
 *	directoryName		目录路径
 *  filenames			目录中文件名集合
 *  addDirectoryName	标志位: 1:文件名包含路径信息; 0:文件名不包含文件信息
 *
 ***************************************************/
CH_DLL_EXPORT
s32 chSearchDir(const string & directoryName,
                vector<string> & filenames,
                bool addDirectoryName = true);


/***************************************************
 * 函数名：chSearchDirForImage
 * 功能  ：搜索目录中的图像文件
 * 参数
 *	directoryName		目录路径
 *  filenames			目录中文件名集合
 *
 ***************************************************/
CH_DLL_EXPORT
s32 chSearchDirForImage(const string & directoryName,
                        vector<string> & filenames);

#if 0
    /***************************************************
    * 函数名：chClearDirectory
    * 功能  ：清空目录
    * 参数
    *	DirPath		目录路径
    *
    ***************************************************/
    CH_DLL_EXPORT
    s32 chClearDirectory(string DirPath);
#endif



/***************************************************
 * 函数名：chVecNormlize
 * 功能  ：vector向量的归一化
 ***************************************************/
CH_DLL_EXPORT
s32 chVecNormlize(vector<f32> & vSrc, vector<f32> & vDst);


/***************************************************
 * 函数名：chMatToXml
 * 功能  ：Mat类型数据存入xml文件中
 ***************************************************/
CH_DLL_EXPORT
s32 chMatToXml(Mat img, string strFilePath);


/***************************************************
 * 函数名：chXmlToMat
 * 功能  ：从xml中读出Mat数据
 ***************************************************/
CH_DLL_EXPORT
s32 chXmlToMat(string strFilePath, Mat & img);


// 两张图像合成
CH_DLL_EXPORT
s32 chSyntheticTwoImage(string ImageName1, string ImageName2, string SyntheticImg);


/***************************************************
 * 函数名：chTic
 * 功能  ：开始计时
 ***************************************************/
CH_DLL_EXPORT
bool chTic(f64 & t);


/***************************************************
 * 函数名：chToc
 * 功能：	结束计时
 * 说明： 输出时间单位为ms
 ***************************************************/
CH_DLL_EXPORT
bool chToc(f64 & t);


// 排序
CH_DLL_EXPORT
s32 chSort_SP1(IN vector<s32> vIndex,
               IN vector<f32> vConf,
               OUT vector<s32> & vSortIndex,
               OUT vector<f32> & vSortConf);


// 模版函数
/***************************************************
 * 函数名：chSortIdx
 * 功能  ：排序，输出排序序号
 ***************************************************/
template <typename T>
s32 chSortIdx(const vector<T> & vlabel,
              vector<s32> & vIndex,
              s32 flag = CH_SORT_ASCENDING)
{
    Mat SrcData = Mat(vlabel);
    Mat DstData;

    if(flag == CH_SORT_ASCENDING) //升序
    {
        sortIdx(SrcData, DstData, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);
    }
    else if(flag == CH_SORT_DESCENDING) //降序
    {
        sortIdx(SrcData, DstData, CV_SORT_EVERY_COLUMN + CV_SORT_DESCENDING);
    }
    else
    {
        return -1;
    }

    vIndex.clear();
    for(s32 i = 0; i < DstData.rows; i++)
    {
        vIndex.push_back(DstData.at<s32>(i));
    }

    return 0;
}


/***************************************************
 * 函数名：chSort
 * 功能  ：排序，输出排序结果
 ***************************************************/
template <typename T>
s32 chSort(const vector<T> & vlabel,
           vector<T> & vSortLabel,
           s32 flag = CH_SORT_ASCENDING)
{

    if(vlabel.size() == 0)
    {
        return -1;
    }

    vector<s32> vIndex;
    if( chSortIdx(vlabel, vIndex) == -1)
    {
        return -1;
    }

    vSortLabel.clear();
    for(u32 i = 0; i < vIndex.size(); i++)
    {
        vSortLabel.push_back( vlabel[vIndex[i]]);
    }

    return 0;
}


/***************************************************
 * 函数名：chVecToXml
 * 功能  ：将vector类型数据写入xml文件中
 ***************************************************/
template <typename DataType>
s32 chVecToXml(const vector<DataType> & vDataList, string strFilePath)
{
    if (strFilePath != "")
    {
        basic_string <char>::size_type szPos;
        string strXlm;
        szPos = strFilePath.find_last_of(".", strFilePath.length());
        string strNameBF = strFilePath.substr(0, szPos);
        strXlm = strNameBF + ".xml";

        FileStorage fs(strXlm, FileStorage::WRITE);
        fs << "DataList" << vDataList;
    }

    return 0;
}


/***************************************************
 * 函数名：chXmlToVec
 * 功能  ：从xml中读取vector类型数据
 ***************************************************/
template <typename DataType>
s32 chXmlToVec(string strFilePath, vector<DataType> & vDataList)
{
    s32 bRead = 0;
    if (strFilePath != "")
    {
        basic_string <char>::size_type szPos;
        string strXlm;
        szPos = strFilePath.find_last_of(".", strFilePath.length());
        string strNameBF = strFilePath.substr(0, szPos);
        strXlm = strNameBF + ".xml";

        FileStorage fs(strXlm, FileStorage::READ);
        fs["DataList"] >> vDataList;
    }

    if (vDataList.size() != 0)
    {
        bRead = 1;
    }

    return bRead;
}


/****************************************************************************
 Opencv实用接口汇总

 minMaxLoc 可获取矩阵中的最小值、最大值，及其坐标

 normlize 可进行矩阵的归一化处理

 常用接口：
 创建目录： CreateDirectory(tVIA_Handle->tVIA.DataPath.c_str(), NULL);

 关于Mat类的说明：
 1. 使用imread导入的图像的结构为Mat结构；
 2. Mat结构的图像数据是连续的，可使用isContinuous()函数进行检测是否连续；
 3. 图像的widthStep = *img.step.p;


 ****************************************************************************/


#endif
