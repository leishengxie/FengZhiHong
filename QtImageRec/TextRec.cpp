
#include "TextRec.h"
#include "bwlabel.h"
#include "MorOperationAlg.h"
#include "ImgSegAlg.h"
#include "ImageProcess.h"
#include<fstream>
#include<iostream>
#include<string>
#include <cstdlib>
using namespace std;

//#define  IMG_DEBUG
#define  IMG_SAVE
// txtfun文本输出函数
void txtfun(const char* str1)
{
  fstream myfile(str1,ios::in|ios::out);
  string line;
  if(!myfile.is_open()){
    cerr<<"error oprening file myname!"<<endl;
    exit(-1);
  }
   
   while(getline(myfile,line))
    cout<<line<<endl;
}

Mat gSubBw;

//字符上下部分合并
s32 TopBottomMerge(vector<TargetInfo> src, s32 stdWidth, s32 stdHeight, vector<TargetInfo>& dst)
{
	s32 xMin, yMin, xMax, yMax;
	vector<s32> vIndex1;
	vector<s32> vIndex2;
	s32 curWidth, curHeight;
	for(u32 i=0; i< src.size()-1; i++)
	{
		for(u32 j=i+1; j<src.size(); j++)
		{
			xMin = MIN(src[i].xMin, src[j].xMin);
			xMax = MAX(src[i].xMax, src[j].xMax);
			yMin = MIN(src[i].yMin, src[j].yMin);
			yMax = MAX(src[i].yMax, src[j].yMax);
			curWidth = xMax - xMin + 1;
			curHeight = yMax - yMin + 1;

			if(src[i].xMax < src[j].xMin  || src[i].xMin > src[j].xMax)
				continue;

			if((src[i].yMin - src[j].yMax) > stdHeight*0.3 || (src[j].yMin - src[i].yMax) > stdHeight*0.3)
				continue;

			f32 wRatio = curWidth*1.0/stdWidth;
			f32 hRatio = curHeight*1.0/stdHeight;
			if(hRatio > 1.2 || wRatio > 1.2)
				continue;

			vIndex1.push_back(i);
			vIndex2.push_back(j);
		}
	}

	
	vector<TargetInfo> vTarget5;
	for(u32 i=0; i<vIndex1.size(); i++)
	{
		TargetInfo target;
		Target2to1(src[vIndex1[i]], src[vIndex2[i]], target);
		vTarget5.push_back(target);
	}
//	chImshowTargets(gSubBw, vTarget5);

	vector<TargetInfo> vTarget6;
	TargetMerge2(vTarget5, vTarget6);
//	chImshowTargets(gSubBw, vTarget6);

	vector<TargetInfo> vTarget7 = src;
	for(u32 i=0; i<vIndex1.size(); i++)
	{
		vTarget7[vIndex1[i]].width = 0;
		vTarget7[vIndex2[i]].width = 0;
	}

	dst = vTarget6;
	for(u32 i=0; i<vTarget7.size(); i++)
	{
		if(vTarget7[i].width == 0)
			continue;
		dst.push_back(vTarget7[i]);
	}

	return 0;
}


//字符左右合并
s32 LeftRightMerge(vector<TargetInfo>& src, s32 stdWidth, s32 stdHeight, vector<TargetInfo>& dst)
{
	s32 xMin, yMin, xMax, yMax;
	vector<s32> vIndex1;
	vector<s32> vIndex2;
	s32 curWidth, curHeight;
	for(u32 i=0; i< src.size()-1; i++)
	{
		vector<s32> vTemp;
		for(u32 j=i+1; j<src.size(); j++)
		{
			xMin = MIN(src[i].xMin, src[j].xMin);
			xMax = MAX(src[i].xMax, src[j].xMax);
			yMin = MIN(src[i].yMin, src[j].yMin);
			yMax = MAX(src[i].yMax, src[j].yMax);
			curWidth = xMax - xMin + 1;
			curHeight = yMax - yMin + 1;

			if(src[i].yMax < src[j].yMin || src[i].yMin > src[j].yMax)
				continue;

			if(src[i].height < 0.9*stdHeight && src[j].height < 0.9*stdHeight)
				continue;

		//	if(src[i].xMin - src[j].xMax >0.3*stdWidth || src[j].xMax - src[i].xMin >0.3*stdWidth)
		//		continue;

			f32 wRatio = curWidth*1.0/stdWidth;
			f32 hRatio = curHeight*1.0/stdHeight;
			if(hRatio > 1.2 || wRatio > 1.2)
				continue;

			vTemp.push_back(j);
		//	vIndex1.push_back(i);
		//	vIndex2.push_back(j);
		}

		if(vTemp.size() == 0)
			continue;

		if(vTemp.size() == 1)
		{
			vIndex1.push_back(i);
			vIndex2.push_back(vTemp[0]);
		}
		else 
		{
			s32 index = vTemp[0];
			s32 MinDist = MAX(src[i].xMin - src[vTemp[0]].xMax, src[vTemp[0]].xMin - src[i].xMax);
			for(u32 k=1; k<vTemp.size(); k++)
			{
				s32 curDist = MAX(src[i].xMin - src[vTemp[k]].xMax, src[vTemp[k]].xMin - src[i].xMax);
				if(MinDist > curDist)
				{
					MinDist = curDist;
					index = vTemp[k];
				}
			}

			vIndex1.push_back(i);
			vIndex2.push_back(index);
		}
	}


	vector<TargetInfo> vTarget5;
	for(u32 i=0; i<vIndex1.size(); i++)
	{
		TargetInfo target;
		Target2to1(src[vIndex1[i]], src[vIndex2[i]], target);
		vTarget5.push_back(target);
	}
	//	chImshowTargets(gSubBw, vTarget5);

	vector<TargetInfo> vTarget6;
	TargetMerge2(vTarget5, vTarget6);
	//	chImshowTargets(gSubBw, vTarget6);

	vector<TargetInfo> vTarget7 = src;
	for(u32 i=0; i<vIndex1.size(); i++)
	{
		vTarget7[vIndex1[i]].width = 0;
		vTarget7[vIndex2[i]].width = 0;
	}

	dst = vTarget6;
	for(u32 i=0; i<vTarget7.size(); i++)
	{
		if(vTarget7[i].width == 0)
			continue;
		dst.push_back(vTarget7[i]);
	}

	return 0;
}


/**********************************************************
 * 函数名：CharacterSegmentation
 * 功能：字符分割
 *
 ***********************************************************/
s32 CharacterSegmentation(Mat& raw, Mat& OutBw, Mat& OutDst,int *wordcount)
{
	// 1. 获取包含字符的子区域
	// 使用BGR三通道中灰度值最暗的值
	Mat img(raw.rows, raw.cols, CV_8UC1);	
	for(int i=0; i<img.rows; i++)
	{
		u8* ptRaw = raw.ptr<u8>(i);
		u8* ptImg = img.ptr<u8>(i);
		for(int j=0; j<img.cols; j++)
		{
			u8 b = ptRaw[3*j];
			u8 g = ptRaw[3*j+1];
			u8 r = ptRaw[3*j+2];

			ptImg[j] = MIN(b, MIN(g, r));
		}
	}
	
	// 边缘检测
	Mat edgeImg;
	EdgeDetection(img, edgeImg, CH_SOBEL);	//CH_SOBEL CH_LAPLACIAN CH_CANNY

	// 自动阈值分割
	Mat bw;
	OtsuMethod2(edgeImg, bw);

	// 膨胀操作
	Mat mask;
	chMorOp(bw, mask, CH_MOR_DILATE, Size(5,5));

	// 目标标记
	vector<TargetInfo> vTarget;
	bwlabel(mask, 70, vTarget);

	// 过滤非目标
	Mat mask1;
	GetTargetsMask(mask, vTarget, mask1);

	// 获取图片中包含字符的子区域
	s32 xMin = mask1.cols;
	s32 yMin = mask1.rows;
	s32 xMax = 0;
	s32 yMax = 0;
	for(u32 i=0; i<vTarget.size(); i++)
	{
		if(xMin > vTarget[i].xMin)
		{
			xMin = vTarget[i].xMin;
		}

		if(yMin > vTarget[i].yMin)
		{
			yMin = vTarget[i].yMin;
		}

		if(xMax < vTarget[i].xMax)
		{
			xMax = vTarget[i].xMax;
		}

		if(yMax < vTarget[i].yMax)
		{
			yMax = vTarget[i].yMax;
		}
	}

	xMin = MAX(xMin-2, 0);
	yMin = MAX(yMin-2, 0);
	xMax = MIN(xMax+2, img.cols-1);
	yMax = MIN(yMax+2, img.rows-1);

	Rect rt;
	rt.x = xMin;
	rt.y = yMin;
	rt.width = xMax - xMin + 1;
	rt.height = yMax - yMin + 1;

	///////////////////////////////////////////////////////////////////////////
	// 2. 基于包含字符的子区域进行目标字符分割处理
	// 获取子区域图片
	Mat subImg;
	img(rt).copyTo(subImg);
	
	// 进行基于区域的自适应阈值分割
	Mat subBw;
	OtsuMethodForBlocks(subImg, subBw, 2, 2, THRESH_BINARY_INV);

	subBw.copyTo(gSubBw);

#if 0	// 对于 stdWidth > 20 有效
	Mat mask2;
	chMorOp(subBw, mask2, CH_MOR_CLOSE, Size(3,3));
	mask2.copyTo(subBw);
#endif

	// 目标标记
	vector<TargetInfo> vTarget2;
	bwlabel(subBw, 5, vTarget2);

	// 计算中文字符的标准宽度、高度
	vector<TargetInfo> vTarget3;
	vector<s32> vWidth;
	vector<s32> vHeight;
	for(u32 i=0; i<vTarget2.size(); i++)
	{
		if(ABS(vTarget2[i].whRatio - 1) < 0.05)
		{
			vWidth.push_back(vTarget2[i].width);
			vHeight.push_back(vTarget2[i].height);
			vTarget3.push_back(vTarget2[i]);
		//	printf("[%d]%.2f %d %d\n", i+1, vTarget2[i].whRatio, vTarget2[i].width, vTarget2[i].height);
		}
	}
	
	vector<s32> vSortWdith;
	vector<s32> vSortHeight;
	chSort(vWidth, vSortWdith);
	chSort(vHeight, vSortHeight);
	s32 stdWidth = vSortWdith[vSortWdith.size()/2];
	s32 stdHeight = vSortHeight[vSortHeight.size()/2];

        // 字符上下部分合并
	//chImshowTargets(subBw, vTarget2);
	vector<TargetInfo> vTarget4;
	TopBottomMerge(vTarget2, stdWidth, stdHeight, vTarget4);
	//chImshowTargets(subBw, vTarget4);

	// 交叉、包含的目标合并
	vector<TargetInfo> vTarget5;
	TargetMerge2(vTarget4, vTarget5);
//	chImshowTargets(subBw, vTarget5);

	// 字符左右部分合并
	vector<TargetInfo> vTarget6;
	LeftRightMerge(vTarget5, stdWidth, stdHeight, vTarget6);
//	chImshowTargets(subBw, vTarget6);

	// 字符左右部分二次合并
	vector<TargetInfo> vTarget7;
	LeftRightMerge(vTarget6, stdWidth, stdHeight, vTarget7);
//	chImshowTargets(subBw, vTarget7);

	// 保存字符图片
	for(u32 i=0; i<vTarget7.size(); i++)
	{
		char fileName[256] = {0};
		sprintf(fileName, "./Data/Output/%d.bmp", i+1);
		imwrite(fileName, subImg(vTarget7[i].rt));
	}

        //计算分割出来的字符数目
        //const char *str2 = "./Data/TXT/A.txt";
        //const char *str1 = "./Data/TXT/B.txt";
         u32 num=vTarget7.size();
         printf("character num:%d\n",num); 
         *wordcount=num;
        //switch(num)
        //{
         //  case 120:txtfun(str1);break;
           //case 45:txtfun(str2);break;
         // default:puts("cuowu");break;
        //}
               

#ifdef IMG_DEBUG
	imshow("步骤1：原图像", raw);
	imshow("步骤2：RGB中最小值灰度图", img);
	imshow("步骤3：Sobel算子边缘检测", edgeImg);
	imshow("步骤4：边缘图自动阈值分割,并膨胀处理", mask1);

	Mat showImg5;
	GrayImgColorRect(mask1, rt, showImg5);
	imshow("步骤5：目标标记获取包含字符子区域", showImg5);

	imshow("步骤6：字符子区域的原图像", subImg);
	imshow("步骤7：基于区域的自动阈值分割", subBw);

	Mat showImg6;
	Mat showImg7;

#if 0
	chImshowTargetsImg(subBw, vTarget2, showImg6);
	imshow("步骤8：目标标记初步", showImg6);

	chImshowTargetsImg(subBw, vTarget7, showImg7);
	imshow("步骤9：目标上下合并、左右合并、交叉包含合并等处理", showImg7);
#else
	Mat subBwInv;
	chSetMatInv(subBw, subBwInv);
	chImshowTargetsImg(subBwInv, vTarget2, showImg6);
	imshow("步骤8：目标标记初步", showImg6);

	chImshowTargetsImg(subBwInv, vTarget7, showImg7);
	imshow("步骤9：目标上下合并、左右合并、交叉包含合并等处理", showImg7);
#endif
	
	waitKey(0);
#endif

#ifdef IMG_SAVE
	imwrite("./Data/Step/1.jpg", raw);
    //printf("Step1 : ./Data/Step/1.jpg\n");

	imwrite("./Data/Step/2.jpg", img);
    //printf("Step2: ./Data/Step/2.jpg\n");

	imwrite("./Data/Step/3.jpg", edgeImg);
    //printf("Step3: ./Data/Step/3.jpg\n");


	imwrite("./Data/Step/4.jpg", mask1);
    //printf("Step4: ./Data/Step/4.jpg\n");


	Mat showImg5;
	GrayImgColorRect(mask1, rt, showImg5);
	imwrite("./Data/Step/5.jpg", showImg5);
    //printf("Step5: ./Data/Step/5.jpg\n");

	imwrite("./Data/Step/6.jpg", subImg);
    //printf("Step6: ./Data/Step/6.jpg\n");

	imwrite("./Data/Step/7.jpg", subBw);
    //printf("Step7: ./Data/Step/7.jpg\n");

	Mat showImg6;
	Mat showImg7;		
	Mat subBwInv;
	chSetMatInv(subBw, subBwInv);
	chImshowTargetsImg(subBwInv, vTarget2, showImg6);
	imwrite("./Data/Step/8.jpg", showImg6);
    //printf("Step8: ./Data/Step/8.jpg\n");
	
	chImshowTargetsImg(subBwInv, vTarget7, showImg7);
	imwrite("./Data/Step/9.jpg", showImg7);
    //printf("Step9: ./Data/Step/9.jpg\n");

#endif

//	OutDst = img;
	return 0;
}
