//#include "stdafx.h"
#include "CommonInterface.h"
//#include <io.h>
#include<sys/types.h>
#include<dirent.h>


/***************************************************
 * 函数名：chImshow
 * 功能  ：多图显示，可同时显示1-5张图片
 * 说明  ：无限等待
 ***************************************************/
CH_DLL_EXPORT
void chImshow(Mat img1, Mat img2, Mat img3, Mat img4, Mat img5)
{
    // 输入检测
    if(img1.empty())
    {
        return;
    }

    vector<s32> vRows(4);
    vRows[0] = img2.rows;
    vRows[1] = img3.rows;
    vRows[2] = img4.rows;
    vRows[3] = img5.rows;

    vector<Mat> vImgs(4);
    vImgs[0] = img2;
    vImgs[1] = img3;
    vImgs[2] = img4;
    vImgs[3] = img5;

    chImshow1("1", img1);
    for(u32 i = 0; i < vRows.size(); i++)
    {
        if(vRows[i] != i + 2)
        {
            char filename[100];
            sprintf(filename, "%d", i + 2);
            chImshow1(filename, vImgs[i]);
        }
    }
    waitKey(0);
}

/***************************************************
 * 函数名：chImshow1
 * 功能  ：图像显示
 ***************************************************/
CH_DLL_EXPORT
void chImshow1(string str, Mat img, s32 flag)
{
    namedWindow(str, flag);
    imshow(str, img);
}

/***************************************************
 * 函数名：chImshowTargets
 * 功能  ：显示图像目标区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowTargets(Mat img, const vector<TargetInfo> & targets, bool writeFlag)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    if(targets.size() == (u32)0)
    {
        return -1;
    }

    Mat showImg;
    //img.copyTo(showImg);

    vector<Mat> vImg(3);
    img.copyTo(vImg[0]);
    img.copyTo(vImg[1]);
    img.copyTo(vImg[2]);
    cv::merge(vImg, showImg);

    for(u32 i = 0; i < targets.size(); i++)
    {
        rectangle(showImg, targets[i].rt, Scalar(0, 0, 255), 1);
        if(writeFlag)
        {
            char filename[100];
            sprintf(filename, "../Data/sample/%d.bmp", i + 1);
            Mat saveImg = showImg(targets[i].rt);
            imwrite(filename, saveImg);
        }
    }

    chImshow(showImg);
    return 0;
}


/***************************************************
 * 函数名：chImshowTargets
 * 功能  ：显示图像目标区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowTargetsImg(Mat img, const vector<TargetInfo> & targets, Mat & dst)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    if(targets.size() == (u32)0)
    {
        return -1;
    }

    Mat showImg;
    //img.copyTo(showImg);

    vector<Mat> vImg(3);
    img.copyTo(vImg[0]);
    img.copyTo(vImg[1]);
    img.copyTo(vImg[2]);
    cv::merge(vImg, showImg);

    for(u32 i = 0; i < targets.size(); i++)
    {
        rectangle(showImg, targets[i].rt, Scalar(0, 0, 255), 1);
    }

    showImg.copyTo(dst);
    return 0;
}

/***************************************************
 * 函数名：chImshowTargetSingle
 * 功能  ：显示图像单个目标区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowTarget_Single(Mat img,
                          TargetInfo targets,
                          bool writeFlag)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    Mat showImg;
    vector<Mat> vImg(3);
    img.copyTo(vImg[0]);
    img.copyTo(vImg[1]);
    img.copyTo(vImg[2]);
    cv::merge(vImg, showImg);

    Rect rt = targets.rt;
    rectangle(showImg, rt, Scalar(0, 0, 255), 1);
    if(writeFlag)
    {
        char filename[100];
        sprintf(filename, "../Data/sample/%d.bmp", 1);
        Mat saveImg = showImg(rt);
        imwrite(filename, saveImg);
    }

    chImshow(showImg);
    return 0;
}


CH_DLL_EXPORT
s32 chImshowRects(Mat img, vector<Rect> vRects)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    if(vRects.size() == (u32)0)
    {
        return -1;
    }

    Mat showImg;
//	img.copyTo(showImg);

    vector<Mat> vImg(3);
    img.copyTo(vImg[0]);
    img.copyTo(vImg[1]);
    img.copyTo(vImg[2]);
    cv::merge(vImg, showImg);

    for(u32 i = 0; i < vRects.size(); i++)
    {
        rectangle(showImg, vRects[i], Scalar(0, 0, 255), 1);
    }

    chImshow(showImg);
    return 0;
}


/***************************************************
 * 函数名：chImshowRect_Single
 * 功能  ：显示图像单个矩形区域
 ***************************************************/
CH_DLL_EXPORT
s32 chImshowRect_Single(Mat img, Rect rt)
{
    // 输入检测
    if(img.empty())
    {
        return -1;
    }

    Mat showImg;
    img.copyTo(showImg);
    rectangle(showImg, rt, Scalar(128), 2);
    chImshow(showImg);
    return 0;
}


CH_DLL_EXPORT
s32 GrayImgColorRect(Mat grayImg, Rect rt, Mat & dst)
{
    Mat colorImg;
    if(grayImg.channels() == 1)
    {
        vector<Mat> vImg(3);
        grayImg.copyTo(vImg[0]);
        grayImg.copyTo(vImg[1]);
        grayImg.copyTo(vImg[2]);
        merge(vImg, colorImg);
    }
    else if(grayImg.channels() == 3)
    {
        grayImg.copyTo(colorImg);
    }

    rectangle(colorImg, rt, Scalar(0, 0, 255), 1);

    colorImg.copyTo(dst);
    return 0;
}

/*******************************************************
 * 函数名： chThumbnail
 * 功能： 缩略图
 * 参数：
 *	iSubImgW, iSubImgH		子图像宽、高
 *	cols, rows,				缩略图行列
 *  iGap					子图像间隔
 *******************************************************/
CH_DLL_EXPORT
s32 chThumbnail(IN vector<Mat> vImg,
                OUT Mat & dst,
                IN s32 iSubImgW,
                IN s32 iSubImgH,
                IN s32 cols,
                IN s32 rows,
                IN s32 iGap)
{
    // 输入检测
    if(vImg.size() == (u32)0)
    {
        return -1;
    }

    if(iSubImgH <= 0 || iSubImgW <= 0 || cols <= 0 || rows <= 0 || iGap < 0)
    {
        return -1;
    }

    s32 imgNum = vImg.size();
    s32 sz = imgNum;
    if(sz > (cols * rows))
    {
        sz = cols * rows;
    }

    //创建缩略图
    Mat mtImg = vImg[0];
    Mat image(iSubImgH * rows + iGap * (rows - 1), iSubImgW * cols + iGap * (cols - 1), mtImg.type(), cv::Scalar::all(0));
    for (int i = 0; i < sz; i++)
    {
        mtImg = vImg[i];
        resize(mtImg, mtImg, cv::Size(iSubImgW, iSubImgH));

        cv::Rect rt(0, 0, iSubImgW, iSubImgH);
        //计算拷贝区域
        int r = i / cols;
        int c = i % cols;
        rt.x = c * iSubImgW + c * iGap;
        rt.y = r * iSubImgH + r * iGap;
        mtImg.copyTo(image(rt));
    }

    image.copyTo(dst);
    return 0;
}


/***************************************************
 * 函数名：chNormDist
 * 功能  ：两点间距离计算
 ***************************************************/
CH_DLL_EXPORT
f32 chNormDist(Point pt1, Point pt2)
{
    Point pt;
    pt.x = pt1.x - pt2.x;
    pt.y = pt1.y - pt2.y;
    return ((f32)norm(pt));
}


/***************************************************
 * 函数名：chImgFileCheck
 * 功能  ：设置第i行第j列处的像素值
 * 参数
 *	strFileName		文件路径
 * 返回值
 *	1:是图像;		0:不是图像
 ***************************************************/
CH_DLL_EXPORT
s32 chImgFileCheck(string strFileName)
{
    string strNameFilter;
    s32 szPos;
    szPos = strFileName.find_last_of(".", strFileName.length());
    strNameFilter = strFileName.substr(szPos + 1, strFileName.length() - szPos - 1);

    char* pFilter[] = {(char*)"bmp", (char*)"BMP",  (char*)"jpg", (char*)"JPG", (char*)"png", (char*)"PNG", (char*)"tif"};
    s32 bImg = 0;

    //过滤扩展名不是bmp的文件
    int len = sizeof(pFilter) / sizeof(pFilter[0]);
    for (int i = 0; i < len; i++)
    {
        if (strcmp(strNameFilter.c_str(), pFilter[i]) == 0)
        {
            bImg = 1;
            break;
        }
    }

    return bImg;
}


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
                bool addDirectoryName)
{
    filenames.clear();

#if defined(WIN32) | defined(_WIN32)
    struct _finddata_t s_file;
    string str = directoryName + "\\*.*";

    intptr_t h_file = _findfirst(str.c_str(), &s_file);
    if (h_file != static_cast<intptr_t>(-1.0))
    {
        do
        {
            if (addDirectoryName)
            {
                filenames.push_back(directoryName + "\\" + s_file.name);
            }
            else
            {
                filenames.push_back((string)s_file.name);
            }
        }
        while (_findnext(h_file, &s_file) == 0);
    }
    _findclose(h_file);
#else
    DIR* dir = opendir(directoryName.c_str());
    if (dir != NULL)
    {
        struct dirent* dent;
        while ((dent = readdir(dir)) != NULL)
        {
            if (addDirectoryName)
            {
                filenames.push_back(directoryName + "/" + string(dent->d_name));
            }
            else
            {
                filenames.push_back(string(dent->d_name));
            }
        }
    }
#endif

    sort(filenames.begin(), filenames.end());

    return 0;
}


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
                        vector<string> & filenames)
{
    vector<string> vFileNames;
    chSearchDir(directoryName, vFileNames, 1);

    basic_string <char>::size_type szPos;

    szPos = directoryName.find_last_of(":", directoryName.length());
    string name, strNameFilter;

    vector<string> vImgFileName(vFileNames.size());
    int iType = -1;
    int iCn = 0;

    for (u32 i = 0; i < vFileNames.size(); i++)
    {
        //寻找扩展名满足条件的文件
        name = vFileNames[i];
        szPos = name.find_last_of(".", name.length());
        strNameFilter = name.substr(szPos + 1, name.length() - szPos - 1);

        //过滤扩展名不是图像的文件
        if (!chImgFileCheck(strNameFilter))
        {
            continue;
        }

        vImgFileName[iCn++] = vFileNames[i];

    }
    vImgFileName.resize(iCn);
    filenames = vImgFileName;

    return 0;
}

#if 0
/***************************************************
 * 函数名：chClearDirectory
 * 功能  ：清空目录
 * 参数
 *	DirPath		目录路径
 *
 ***************************************************/
CH_DLL_EXPORT
s32 chClearDirectory(string DirPath)
{
    vector<string> vFileList;
    chSearchDir(DirPath, vFileList);

    for(u32 i = 0; i < vFileList.size(); i++)
    {
        DeleteFile(vFileList[i].c_str());
    }

    return 0;
}
#endif


/***************************************************
 * 函数名：chVecNormlize
 * 功能  ：vector向量的归一化
 ***************************************************/
CH_DLL_EXPORT
s32 chVecNormlize(vector<f32> & vSrc, vector<f32> & vDst)
{
    // 输入检测
    if(vSrc.size() == (u32)0)
    {
        return -1;
    }

    Mat src = Mat(vSrc);
    Mat dst;

    normalize(src, dst, 0, 1, CV_MINMAX);

    vDst.clear();
    for(s32 i = 0; i < dst.rows; i++)
    {
        vDst.push_back(dst.at<f32>(i));
    }

    return 0;
}

/***************************************************
 * 函数名：chMatToXml
 * 功能  ：Mat类型数据存入xml文件中
 ***************************************************/
CH_DLL_EXPORT
s32 chMatToXml(Mat img, string strFilePath)
{
    if (strFilePath != "")
    {
        basic_string <char>::size_type szPos;
        string strXlm;
        szPos = strFilePath.find_last_of(".", strFilePath.length());
        string strNameBF = strFilePath.substr(0, szPos);
        strXlm = strNameBF + ".xml";

        FileStorage fs(strXlm, FileStorage::WRITE);
        fs << "img" << img;
    }

    return 0;
}

/***************************************************
 * 函数名：chXmlToMat
 * 功能  ：从xml中读出Mat数据
 ***************************************************/
CH_DLL_EXPORT
s32 chXmlToMat(string strFilePath, Mat & img)
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
        fs["img"] >> img;
    }

    if (!img.empty())
    {
        bRead = 1;
    }

    return bRead;
}


// 两张图像合成
CH_DLL_EXPORT
s32 chSyntheticTwoImage(string ImageName1, string ImageName2, string SyntheticImg)
{
    s32 iSubImgH = 128;
    s32 iSubImgW = 256;
    Mat mtImg1;
    Mat mtImg2;

    Mat TempImage = Mat::zeros(iSubImgH, iSubImgW, CV_8UC3);

    Rect rt1(0, 0, iSubImgH, iSubImgH);
    Rect rt2(iSubImgH, 0, iSubImgH, iSubImgH);

    mtImg1 = imread(ImageName1);
    mtImg2 = imread(ImageName2);

    resize(mtImg1, mtImg1, Size(iSubImgH, iSubImgH));
    resize(mtImg2, mtImg2, Size(iSubImgH, iSubImgH));

    mtImg1.copyTo(TempImage(rt1));
    mtImg2.copyTo(TempImage(rt2));

    imwrite(SyntheticImg, TempImage);
    return 0;
}

/***************************************************
 * 函数名：chTic
 * 功能  ：开始计时
 ***************************************************/
CH_DLL_EXPORT
bool chTic(f64 & t)
{
    t = (f64)getTickCount();
    return true;
}

/***************************************************
 * 函数名：chToc
 * 功能：	结束计时
 * 说明： 输出时间单位为ms
 ***************************************************/
CH_DLL_EXPORT
bool chToc(f64 & t)
{
    f64 timeStart = t;
    t = (getTickCount() - timeStart) / getTickFrequency() * 1000;
    return true;
}


// 排序
CH_DLL_EXPORT
s32 chSort_SP1(IN vector<s32> vIndex,
               IN vector<f32> vConf,
               OUT vector<s32> & vSortIndex,
               OUT vector<f32> & vSortConf)
{
    // 输入检测
    vSortIndex.clear();
    vSortConf.clear();
    if(vConf.size() == 0 || vIndex.size() == 0 || vConf.size() != vConf.size())
    {
        return 0;
    }

    vector<s32> vSort;
    chSortIdx(vConf, vSort, CH_SORT_DESCENDING);
    for(u32 i = 0; i < vSort.size(); i++)
    {
        vSortIndex.push_back(vIndex[vSort[i]]);
        vSortConf.push_back(vConf[vSort[i]]);
    }

    return 0;
}

