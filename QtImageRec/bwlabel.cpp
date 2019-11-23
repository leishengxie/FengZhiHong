//#include "stdafx.h"
#include "bwlabel.h"

#define MIN_AREA   4*4//标记函数的参数

#define LABELMODE_1  1
#define LABELMODE_2  2

#if 0
#define MAXSLINK     (256*4)   /* 0 --- 255  */
#define MAXLINK      (1024*4)  /* 0 --- 1023 */
#define MAXSUBBLOCK  (1023*4)  /* 1 --- 1023 */
#define MAXBLOCK     (255*4)   /* 1 --- 255  */
#define MAXGREYLEVEL (255*4)   /* 0 --- 255  */
#else
#define MAXSLINK     (1024)
#define MAXLINK      (100000)
#define MAXSUBBLOCK  (8192)  /* 1 --- 1023 */
#define MAXBLOCK     (8192)
#endif

s32 Gray[MAXSLINK];
u16 stack[MAXSLINK];
u16 TmpArea[MAXBLOCK+1];
u16 TemArray[2000*2000];
u16 mapArr[MAXSUBBLOCK+1];
u16 neighbor[2*MAXLINK];


/***********************************************
* 函数：GetNeighborTable
* 功能：
*
***********************************************/
u16 GetNeighborTable(u8 *array,
                     s32 RowLen,
                     s32 ColLen,
                     u16 *neighbor,
                     u16 *TemArray,
                     s32 *TabLen,
                     u16 *area)
{
    s32 StartPos, EndPos, GrayNoLastLine;
    s32 i, j, k;
    s32 *pGray;
    u16 GrayNo = 0;

    pGray = Gray;
    memset(pGray, 0, MAXSLINK*sizeof(s32));
    *TabLen = 0;

    for(i=0; i<RowLen; i++)
    {
        for(j=0; j<ColLen; j++)
        {
            if(array[i*ColLen+j] != 0)
            {
                StartPos = j;

                do
                {
                    j++;
                    if(j==ColLen)
                    {
                        break;
                    }
                }while(array[i*ColLen+j]!=0);

                EndPos = j-1;
                GrayNoLastLine = 0;

                for(k=StartPos-1; k<=EndPos+1; k++)
                {
                    //  第一行
                    if(i-1<0)
                    {
                        break;
                    }

                    // 第一列或最后一列
                    if((k<0) || (k>=ColLen))
                    {
                        continue;
                    }

                    if(TemArray[(i-1)*ColLen+k]!=0)
                    {
                        if(GrayNoLastLine>=MAXSLINK)
                        {
                            return 0;
                        }

                        pGray[GrayNoLastLine] = TemArray[(i-1)*ColLen+k];
                        GrayNoLastLine++;

                        while(TemArray[(i-1)*ColLen+k]!=0)
                        {
                            k++;
                        }
                    }
                }


                if(GrayNoLastLine==0)
                {
                    GrayNo++;
                    if(GrayNo > MAXBLOCK)
                    {
                        return 0;
                    }

                    if(*TabLen >= MAXLINK)
                    {
                        return 0;
                    }

                    neighbor[*TabLen] = GrayNo;
                    neighbor[*TabLen+MAXLINK] = GrayNo;
                    (*TabLen)++;

                    area[GrayNo] = EndPos - StartPos + 1;

                    for(k=StartPos; k<=EndPos; k++)
                    {
                        TemArray[i*ColLen+k] = GrayNo;
                    }
                }
                else
                {
                    for(k=StartPos; k<=EndPos; k++)
                    {
                        TemArray[i*ColLen+k] = pGray[0];
                    }

                    area[pGray[0]] += EndPos - StartPos + 1;

                    for(k=1; k<GrayNoLastLine; k++)
                    {
                        if(*TabLen>=MAXLINK)
                        {
                            return 0;
                        }

                        neighbor[*TabLen] = pGray[0];
                        neighbor[*TabLen+MAXLINK] = pGray[k];
                        (*TabLen)++;
                    }
                }
            }
        }
    }

    return GrayNo;
}


/***********************************************
* 函数：GetMapTable
* 功能：
*
***********************************************/
s32 GetMapTable(u16 *neighbor,
                s32 TabLen,
                u16 *map )
{
    s32   i, j, TrueObj, StackPtr, TmpValue;
    u16 *pstack,*pneighbor0,*pneighbor1,*pneighbor2,*pneighbor3;

    pstack = &(stack[0]);
    for(i=0;i<MAXSLINK;i++)
    {
        pstack[i] = 0;
    }

    TrueObj  = 0;
    StackPtr = 0;
    pneighbor0 = &(neighbor[0]);
    pneighbor1 = &(neighbor[MAXLINK]);

    for (i=0; i<TabLen; i++,pneighbor0++,pneighbor1++)
    {
        if (*pneighbor0!=0)
        {
            pstack[StackPtr] = *pneighbor0;
            StackPtr++;
            TrueObj++;
            *pneighbor0 = 0;
            *pneighbor1 = 0;
        }

        while (StackPtr!=0)
        {
            StackPtr--;
            TmpValue = pstack[StackPtr];
            map[TmpValue] = TrueObj;

            pneighbor2 = pneighbor0;
            pneighbor3 = pneighbor1;

            for (j=i; j<TabLen; j++, pneighbor2++, pneighbor3++)
            {
                if ((*pneighbor2 == TmpValue) || (*pneighbor3 == TmpValue))
                {
                    if (*pneighbor2!=*pneighbor3)
                    {
                        stack[StackPtr] = (*pneighbor2!=TmpValue)? *pneighbor2: *pneighbor3;
                        StackPtr++;
                    }

                    *pneighbor2 = 0;
                    *pneighbor3 = 0;
                }
            }
        }
    }

    return(TrueObj);
}


/***********************************************
* 函数：ModifyMapTable1
* 功能：
*
***********************************************/
s32 ModifyMapTable1(u16 *map,
                    u16 *area,
                    u16 GrayNo,
                    s32 TrueObj,
                    s32 MinArea )
{
    s32 TrueTrueObj;
    s32 i, j;
    s32 TmpArea;

    u16 *pmap;
    u16 *parea;

    TrueTrueObj = 0;
    for (i=1; i<=TrueObj; i++)
    {
        TmpArea = 0;
        pmap  = &(map[1]);
        parea = &(area[1]);

        for (j=1; j<=GrayNo; j++, pmap++, parea++)
        {
            if (*pmap==i)
            {
                TmpArea += *parea;
            }
        }

        if (TmpArea<MinArea)
        {
            pmap  = &(map[1]);

            for (j=1; j<=GrayNo; j++, pmap++)
            {
                if (*pmap==i)
                {
                    *pmap = 0;
                }
            }
        }
        else
        {
            TrueTrueObj++;
            if (TrueTrueObj>MAXBLOCK)
            {
                return 0;
            }

            pmap  = &(map[1]);

            for (j=1; j<=GrayNo; j++, pmap++)
            {
                if (*pmap==i)
                {
                    *pmap = TrueTrueObj;
                }
            }
        }
    }

    return(TrueTrueObj);
}


/***********************************************
* 函数：ModifyMapTable2
* 功能：
*
***********************************************/
void ModifyMapTable2(u16 *map,
                     u16 *area,
                     u16 GrayNo,
                     s32 TrueObj)
{
    s32 MaxBlockNo=0;
    s32 i, j;
    s32 MaxBlockArea;
    long Tmp = 0;

    for(i=0;i<MAXBLOCK+1;i++)
    {
        TmpArea[i] = 0;
    }

    /* Get the area of all blocks */
    for (i=1; i<=TrueObj; i++)
    {
        TmpArea[i] = 0;

        for (j=1; j<=GrayNo; j++)
        {
            if (map[j]==i)
            {
                TmpArea[i] += area[j];
            }
        }

        Tmp +=  TmpArea[i];
    }

    /* Find the block number of the max block */
    MaxBlockArea = 0;
    for (i=1;i<=TrueObj;i++)
    {
        if (TmpArea[i]>MaxBlockArea)
        {
            MaxBlockArea = TmpArea[i];
            MaxBlockNo = i;
        }
    }

    for (i=1;i<=GrayNo;i++)
    {
        if (map[i]!=MaxBlockNo)
        {
            map[i] = 0;
        }
        else
        {
            map[i] = 1;
        }
    }
}


/***********************************************
* 函数：DoMap
* 功能：
*
***********************************************/
void DoMap(u16 *labelDst,
           u16 *TemArray,
           s32 RowLen,
           s32 ColLen,
           u16 *map)
{
    s32 i;
    u16  *pTemArray = &(TemArray[0]);
    u16  *parray = &(labelDst[0]);

    map[0] = 0;

    for (i=0; i<RowLen*ColLen;i++,parray++, pTemArray++)
    {
        if (map[*pTemArray]!=0)
        {
            *parray = map[*pTemArray];
        }
        else
        {
            *parray = 0;
        }
    }
}

/***********************************************
* 函数：Label
* 功能：得到8邻域标记函数，存储在array中，
*	    第一个目标被标记为maxgraylevel, 依次递减
* 参数：
*	array		图像的二值图
*	labelDst	图像的标记图像
*	RowLen		图像的高
*	ColLen		图像的宽
*	MinArea		目标最小面积
* 返回值：
*   >= 0  目标个数
*   -1:   图像尺寸过大
*	-2：   标记异常
***********************************************/
s32 Label(u8 *array,
          u16 *labelDst,
          s32 RowLen,
          s32 ColLen,
          s32 MinArea)
{
    u16 *pmap = mapArr;
    u16 *pneighbor = neighbor;
    u16 *pTemArray = TemArray;
    u16 *pTmpArea = TmpArea;
    s32 TabLen;
    s32 GrayNo;
    s32 TrueObj;

    /* 防止尺寸过大引起崩溃 */
    if(RowLen*ColLen > (2000*2000))
    {
        return -1;
    }

    memset(pmap, 0, (MAXSUBBLOCK+1)*2);
    memset(pTmpArea, 0, (MAXBLOCK+1)*2);
    memset(pneighbor, 0, (2*MAXLINK)*2);
    memset(pTemArray, 0, (RowLen*ColLen)*2);

    GrayNo = GetNeighborTable(array, RowLen, ColLen, pneighbor, pTemArray, &TabLen, pTmpArea);
    if ((GrayNo>MAXBLOCK)||(GrayNo==0))
    {
        return -2;
    }

    TrueObj = GetMapTable(pneighbor, TabLen, pmap);
    int LabelMode = 1;
    if (LabelMode==1)
    {
        TrueObj = ModifyMapTable1(pmap, pTmpArea, GrayNo, TrueObj, MinArea);
    }
    else
    {
        ModifyMapTable2(pmap, pTmpArea, GrayNo, TrueObj);
        TrueObj = 1;
    }

    DoMap(labelDst, pTemArray, RowLen, ColLen, pmap);

    return TrueObj;
}


/***********************************************
* 函数：GetLabelCoordinate
* 功能：获取所有目标区域的坐标信息
* 参数：
*
***********************************************/
s32 GetLabelCoordinate(IN u16 *labelDst,
                       IN s32 RowLen,
                       IN s32 ColLen,
                       IN s32 objNum,
                       OUT vector<TargetInfo>& target)
{
    TargetInfo tar;
    Point p;
    vector<Point> objArea;
    s32 matchVal;

    for(s32 k=0; k<objNum; k++)
    {
        matchVal = k+1;
        for(s32 i=0; i<RowLen; i++)
        {
            for(s32 j=0; j<ColLen; j++)
            {
                if( *(labelDst + i*ColLen + j) == matchVal )
                {
                    p.x = j;
                    p.y = i;
                    objArea.push_back(p);
                }
            }
        }

        s32 iMin = RowLen;
        s32 jMin = ColLen;
        s32 iMax = 0;
        s32 jMax = 0;
        Point left, top, right, bottom;
        for(u32 l=0; l<objArea.size(); l++)
        {
            if(objArea[l].x > jMax)
            {
                jMax = objArea[l].x;
                right = objArea[l];
            }

            if(objArea[l].y > iMax)
            {
                iMax = objArea[l].y;
                bottom = objArea[l];
            }

            if(objArea[l].x < jMin)
            {
                jMin = objArea[l].x;
                left = objArea[l];
            }

            if(objArea[l].y < iMin)
            {
                iMin = objArea[l].y;
                top = objArea[l];
            }
        }

        tar.objArea = objArea;
        tar.count = objArea.size();
        tar.xMin = jMin;
        tar.yMin = iMin;
        tar.xMax = jMax;
        tar.yMax = iMax;
        tar.left = left;
        tar.top = top;
        tar.right = right;
        tar.bottom = bottom;
        tar.width = tar.xMax - tar.xMin + 1;
        tar.height = tar.yMax - tar.yMin + 1;
        tar.AreaRatio = (f32)(tar.count*1.0/(tar.width*tar.height));
        tar.whRatio = (f32)(tar.width*1.0/tar.height);
        tar.rt.x = tar.xMin;
        tar.rt.y = tar.yMin;
        tar.rt.width = tar.width;
        tar.rt.height = tar.height;

        target.push_back(tar);
        objArea.clear();
    }

    return 0 ;
}


/***********************************************
 * 函数：bwlabel
 * 功能：二值图像标记，返回标记目标的坐标
 * 参数：
 *   bw			二值图像
 *   target		目标集合
 ***********************************************/
CH_DLL_EXPORT
s32 bwlabel(IN const Mat bw,
            IN s32 MinArea,
            OUT vector<TargetInfo>& target)
{
    // 输入检测
    if(bw.empty())
        return -1;

    if(MinArea <= 0)
        return -1;

    if(bw.channels() !=1)
        return -1;

    Mat temp(bw.rows, bw.cols, CV_16UC1);
    s32 num = Label(bw.data, (u16*)temp.data, bw.rows, bw.cols, MinArea);
    if(num<0)
        return -1;
    target.clear();
    GetLabelCoordinate((u16*)temp.data, bw.rows, bw.cols, num, target);
    return (target.size());
}


/***********************************************
* 函数：TargetMerge
* 功能：目标合并处理
* 参数：
*	SrcTargets	输入目标
*	DstTargets	输出目标
***********************************************/
CH_DLL_EXPORT
s32 TargetMerge(IN const vector<TargetInfo>& SrcTargets, OUT vector<TargetInfo>& DstTargets)
{
#if 1
    // 输入检测
    if(SrcTargets.size() == (u32)0)
        return -1;

    Point p1;
    int len = SrcTargets.size();
    vector<vector<int> > vSimilar;
    vector<int> similar;

    f32 xCenter, yCenter;
    for(int i=0; i<len-1; i++)
    {
        for(int j=i+1; j<len; j++)
        {
            similar.clear();
            s32 xMin = MAX(SrcTargets[i].xMin, SrcTargets[j].xMin);
            s32 yMin = MAX(SrcTargets[i].yMin, SrcTargets[j].yMin);
            s32 xMax = MIN(SrcTargets[i].xMax, SrcTargets[j].xMax);
            s32 yMax = MIN(SrcTargets[i].yMax, SrcTargets[j].yMax);

            xCenter = (xMin + yMax)*1.0/2;
            yCenter = (yMin + yMax)*1.0/2;

            Point pI, pJ;
            pI.x = (SrcTargets[i].xMin + SrcTargets[i].xMax)/2;
            pI.y = (SrcTargets[i].yMin + SrcTargets[i].yMax)/2;
            pJ.x = (SrcTargets[j].xMin + SrcTargets[j].xMax)/2;
            pJ.y = (SrcTargets[j].yMin + SrcTargets[j].yMax)/2;

            // 包含
            if((pI.x >= SrcTargets[j].xMin && pI.x <= SrcTargets[j].xMax && pI.y >= SrcTargets[j].yMin && pI.y <= SrcTargets[j].yMax) ||
               (pJ.x >= SrcTargets[i].xMin && pJ.x <= SrcTargets[i].xMax && pJ.y >= SrcTargets[i].yMin && pJ.y <= SrcTargets[i].yMax))
            {
                similar.push_back(i);
                similar.push_back(j);
                vSimilar.push_back(similar);
            }
            else if((SrcTargets[i].xMin >= SrcTargets[j].xMin && SrcTargets[i].xMax <= SrcTargets[j].xMax &&
                SrcTargets[i].yMin >= SrcTargets[j].yMin && SrcTargets[i].yMax <= SrcTargets[j].yMax) ||
                (SrcTargets[i].xMin <= SrcTargets[j].xMin && SrcTargets[i].xMax >= SrcTargets[j].xMax &&
                SrcTargets[i].yMin <= SrcTargets[j].yMin && SrcTargets[i].yMax >= SrcTargets[j].yMax))
            {
                similar.push_back(i);
                similar.push_back(j);
                vSimilar.push_back(similar);
            }
            // 交叉
            else if(xCenter >= SrcTargets[i].xMin && xCenter <= SrcTargets[i].xMax &&
                yCenter >= SrcTargets[i].yMin && yCenter <= SrcTargets[i].yMax &&
                xCenter >= SrcTargets[j].xMin && xCenter <= SrcTargets[j].xMax &&
                yCenter >= SrcTargets[j].yMin && yCenter <= SrcTargets[j].yMax)
            {
                similar.push_back(i);
                similar.push_back(j);
                vSimilar.push_back(similar);
            }
        }
    }

    DstTargets = SrcTargets;
    for(u32 i=0; i<vSimilar.size(); i++)
    {
        TargetInfo target1 = DstTargets[vSimilar[i][0]];
        TargetInfo target2 = DstTargets[vSimilar[i][1]];
        TargetInfo newTarget;

        if(target1.count==0 || target2.count==0)
            continue;

        newTarget.objArea = target1.objArea;
        for(u32 m=0; m< target2.objArea.size(); m++)
        {
            newTarget.objArea.push_back(target2.objArea[m]);
        }
        newTarget.count = newTarget.objArea.size();
        newTarget.xMin = MIN(target1.xMin, target2.xMin);
        newTarget.yMin = MIN(target1.yMin, target2.yMin);
        newTarget.xMax = MAX(target1.xMax, target2.xMax);
        newTarget.yMax = MAX(target1.yMax, target2.yMax);
        newTarget.AreaRatio = (f32)(1.0*newTarget.count/((newTarget.xMax - newTarget.xMin)*(newTarget.yMax - newTarget.yMin)));
        newTarget.width = newTarget.xMax - newTarget.xMin + 1;
        newTarget.height = newTarget.yMax - newTarget.yMin + 1;
        newTarget.whRatio = (f32)(newTarget.width*1.0/newTarget.height);
        newTarget.rt.x = newTarget.xMin;
        newTarget.rt.y = newTarget.yMin;
        newTarget.rt.width = newTarget.width;
        newTarget.rt.height = newTarget.height;

        DstTargets[vSimilar[i][0]] = newTarget;
        DstTargets[vSimilar[i][1]].count = 0;
    }

    vector<TargetInfo> TempTargets;
    for(u32 i=0; i< DstTargets.size(); i++)
    {
        if(DstTargets[i].count == 0)
            continue;

        TempTargets.push_back(DstTargets[i]);
    }

    DstTargets = TempTargets;

#else
    // 输入检测
    if(SrcTargets.size() == (u32)0)
        return -1;

    Point p1;
    int len = SrcTargets.size();
    vector<vector<int>> vSimilar;
    vector<int> similar;

    for(int i=0; i<len-1; i++)
    {
        for(int j=i+1; j<len; j++)
        {
            similar.clear();
            s32 xMin = MAX(SrcTargets[i].xMin, SrcTargets[j].xMin);
            s32 yMin = MAX(SrcTargets[i].yMin, SrcTargets[j].yMin);
            s32 xMax = MIN(SrcTargets[i].xMax, SrcTargets[j].xMax);
            s32 yMax = MIN(SrcTargets[i].yMax, SrcTargets[j].yMax);

            Point pI, pJ;
            pI.x = (SrcTargets[i].xMin + SrcTargets[i].xMax)/2;
            pI.y = (SrcTargets[i].yMin + SrcTargets[i].yMax)/2;
            pJ.x = (SrcTargets[j].xMin + SrcTargets[j].xMax)/2;
            pJ.y = (SrcTargets[j].yMin + SrcTargets[j].yMax)/2;
            f32 dist = sqrt(f32((pI.x - pJ.x)*(pI.x - pJ.x) + (pI.y - pJ.y)*(pI.y - pJ.y)));

            p1.x = (xMin + xMax)/2;
            p1.y = (yMin + yMax)/2;
            if( p1.x > SrcTargets[i].xMin && p1.x < SrcTargets[i].xMax &&
                p1.y > SrcTargets[i].yMin && p1.y < SrcTargets[i].yMax )
            {
                similar.push_back(i);
                similar.push_back(j);
                vSimilar.push_back(similar);
            }
            else if( dist < 5)
            {
                similar.push_back(i);
                similar.push_back(j);
                vSimilar.push_back(similar);
            }
        }
    }

    DstTargets = SrcTargets;
    for(u32 i=0; i<vSimilar.size(); i++)
    {
        TargetInfo target1 = DstTargets[vSimilar[i][0]];
        TargetInfo target2 = DstTargets[vSimilar[i][1]];
        TargetInfo newTarget;

        if(target1.count==0 || target2.count==0)
            continue;

        newTarget.objArea = target1.objArea;
        for(u32 m=0; m< target2.objArea.size(); m++)
        {
            newTarget.objArea.push_back(target2.objArea[m]);
        }
        newTarget.count = newTarget.objArea.size();
        newTarget.xMin = MIN(target1.xMin, target2.xMin);
        newTarget.yMin = MIN(target1.yMin, target2.yMin);
        newTarget.xMax = MAX(target1.xMax, target2.xMax);
        newTarget.yMax = MAX(target1.yMax, target2.yMax);
        newTarget.AreaRatio = (f32)(1.0*newTarget.count/((newTarget.xMax - newTarget.xMin)*(newTarget.yMax - newTarget.yMin)));
        newTarget.width = newTarget.xMax - newTarget.xMin + 1;
        newTarget.height = newTarget.yMax - newTarget.yMin + 1;
        newTarget.whRatio = (f32)(newTarget.width*1.0/newTarget.height);
        newTarget.rt.x = newTarget.xMin;
        newTarget.rt.y = newTarget.yMin;
        newTarget.rt.width = newTarget.width;
        newTarget.rt.height = newTarget.height;

        DstTargets[vSimilar[i][0]] = newTarget;
        DstTargets[vSimilar[i][1]].count = 0;
    }

    vector<TargetInfo> TempTargets;
    for(u32 i=0; i< DstTargets.size(); i++)
    {
        if(DstTargets[i].count == 0)
            continue;

        TempTargets.push_back(DstTargets[i]);
    }

    DstTargets = TempTargets;
#endif
    return 0;
}

/***********************************************
* 函数：TargetMerge2
* 功能：目标合并处理
* 参数：
*	SrcTargets	输入目标
*	DstTargets	输出目标
***********************************************/
CH_DLL_EXPORT
s32 TargetMerge2(IN const vector<TargetInfo>& SrcTargets,
                 OUT vector<TargetInfo>& DstTargets)
{

    // 输入检测
    if(SrcTargets.size() == (u32)0)
        return -1;

    vector<TargetInfo> temp;
    vector<TargetInfo> temp1;

    temp = SrcTargets;
    DstTargets = SrcTargets;

    while(1)
    {
        TargetMerge(temp, temp1);
        if(temp.size() == temp1.size())
        {
            DstTargets = temp1;
            break;
        }

        temp = temp1;
    }

    return 0;
}


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
                   IN const vector<TargetInfo>& targets,
                   OUT Mat& mask)
{
    // 输入检测
    if(src.empty())
        return -1;

    if(targets.size() == (u32)0)
        return -1;

    mask = Mat::zeros(src.rows, src.cols, CV_8UC1);
    for(u32 i=0; i<targets.size(); i++)
    {
        for(u32 k=0; k< targets[i].objArea.size(); k++)
        {
            s32 x = targets[i].objArea[k].x;
            s32 y = targets[i].objArea[k].y;
            if( *(src.ptr<u8>(y, x)) == 255)
            {
                *(mask.ptr<u8>(y, x)) = 255;
            }
        }
    }

    return 0;
}


/***********************************************
* 函数：GetTargetsRect
* 功能：获取目标掩码
***********************************************/
CH_DLL_EXPORT
s32 GetTargetsRect(const vector<TargetInfo>& targets, Rect& rt)
{
    // 输入检测
    if(targets.size() == (u32)0)
        return -1;

    s32 xMin = targets[0].xMin;
    s32 yMin = targets[0].yMin;
    s32 xMax = targets[0].xMax;
    s32 yMax = targets[0].yMax;

    for(u32 i=1; i<targets.size(); i++)
    {
        if( xMin > targets[i].xMin)  { xMin = targets[i].xMin; }
        if( yMin > targets[i].yMin)  { yMin = targets[i].yMin; }
        if( xMax < targets[i].xMax)  { xMax = targets[i].xMax;}
        if( yMax < targets[i].yMax)  { yMax = targets[i].yMax;}
    }

    rt.x = xMin;
    rt.y = yMin;
    rt.width = xMax - xMin;
    rt.height = yMax - yMin;
    return 0;
}


/***********************************************
* 函数：TargetToRect
* 功能：目标转化为矩形框
***********************************************/
CH_DLL_EXPORT
s32 TargetToRect(const vector<TargetInfo>& targets,
                 vector<Rect>& vRt)
{
    // 输入检测
    if(targets.size() == (u32)0)
        return -1;

    for(u32 i=0; i<targets.size(); i++)
        vRt.push_back(targets[i].rt);
    return 0;
}


/***********************************************
* 函数：GetTargetsImg
* 功能：获取目标子图像集合
***********************************************/
CH_DLL_EXPORT
s32 GetTargetsImg(Mat img,
                  const vector<TargetInfo>& targets,
                  vector<Mat>& vImg)
{
    // 输入检测
    if(img.empty())
        return -1;

    if(targets.size() == (u32)0)
        return -1;

    vector<Rect> vRt;
    TargetToRect(targets, vRt);
    for(u32 i=0; i<vRt.size(); i++)
    {
        Mat subImg(vRt[i].height, vRt[i].width, CV_8UC1);
        Mat temp = img(vRt[i]);
        temp.copyTo(subImg);
        vImg.push_back(subImg);
    }
    return 0;
}


/***********************************************
* 函数：TargetFilter
* 功能：目标过滤
***********************************************/
CH_DLL_EXPORT
s32 TargetFilter(IN const vector<TargetInfo>& srcTargets,
                 OUT vector<TargetInfo>& dstTargets,
                 IN s32 minArea,
                 IN f32 AreaRatio,
                 IN f32 whRatio)
{
    // 输入检测
    if(srcTargets.size() == (u32)0)
        return -1;

    if(minArea < 0)
        return -1;

    if(AreaRatio < 0.0 || AreaRatio > 1.0)
        return -1;

    if(whRatio < 0.0)
        return -1;

    dstTargets.clear();
    for(u32 i=0; i<srcTargets.size(); i++)
    {
        if(srcTargets[i].count < minArea)
            continue;

        if(srcTargets[i].AreaRatio < AreaRatio)
            continue;

        if(srcTargets[i].whRatio < whRatio)
            continue;

        dstTargets.push_back(srcTargets[i]);
    }

    return 0;
}


CH_DLL_EXPORT
s32 Target2to1(IN TargetInfo& target1,
    IN TargetInfo& target2,
    IN TargetInfo& dstTarget)
{

    dstTarget.xMin = MIN(target1.xMin, target2.xMin);
    dstTarget.yMin = MIN(target1.yMin, target2.yMin);
    dstTarget.xMax = MAX(target1.xMax, target2.xMax);
    dstTarget.yMax = MAX(target1.yMax, target2.yMax);

    dstTarget.width = dstTarget.xMax - dstTarget.xMin + 1;
    dstTarget.height = dstTarget.yMax - dstTarget.yMin + 1;
    dstTarget.count = target1.count + target2.count;
    dstTarget.whRatio = dstTarget.width * 1.0/dstTarget.height;
    dstTarget.AreaRatio = dstTarget.count*1.0/(dstTarget.width*dstTarget.height);

    dstTarget.rt.x = dstTarget.xMin;
    dstTarget.rt.y = dstTarget.yMin;
    dstTarget.rt.width = dstTarget.width;
    dstTarget.rt.height = dstTarget.height;

    vector<Point> objArea(dstTarget.count);
    for(u32 i=0; i< target1.count; i++)
    {
        objArea[i] = target1.objArea[i];
    }

    for(u32 j=0; j<target2.count; j++)
    {
        objArea[j + target1.count] = target2.objArea[j];
    }

    dstTarget.objArea = objArea;
    return 0;
}
