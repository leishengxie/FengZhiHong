
#ifndef _HTTP_PARSER_H_
#define _HTTP_PARSER_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataDefine.h"
//https://192.168.5.59:11443/xgcloud/lighttemplate.html?method=list&clubInfoId=10000


#define HTTP_MAX_HEADER_SIZE (80*1024)

/*

/**
  * http协议头
  */
struct T_HttpHeader
{
    // 1-请求行，包括方法字段、URI和HTTP协议版本。请求行结束后必须有一空行
    char RequestMethod[20];     //客户端请求的方法字段 eg GET
    char FilePath[255];         //统一资源标识符uri(Uniform Resource Identifier)即网络资源路径，是统一资源定位符url(Uniform Resource Locator)的一部分 eg /
    char HttpVersion[10];       //客户端http的版本 eg HTTP/1.1
    // empty line

    // 2-头域检测
    // 通用头域
    char CacheControl[255];    //Cache-Control头域
    char HTTPKeepAlive[255];  //HTTP Keep-Alive头域
    char Date[255];             // Date头域 头域表示消息发送的时间，时间的描述格式由rfc822定义。例如，Date:Mon,31Dec200104:25:57GMT。
                                //Date描述的时间表示世界标准时，换算成本地时间，需要知道用户所在的时区。
    char Pragma[255];           // Pragma头域用来包含实现特定的指令，最常用的是Pragma:no-cache。在HTTP/1.1协议中，它的含义和Cache-Control:no-cache相同

    // 其他头域
    char Host[255];             //Host字段，表示所请求的资源所在的客户端IP(即主机名)和端口号。 HTTP/1.1请求必须包含主机头域，否则系统会以400状态码返回。
    char Range[255];            // Range头域可以请求实体的一个或者多个子范围。例如，表示头500个字节：bytes=0-499
    char UserAgent[255];        // User-Agent头域的内容包含发出请求的用户信息。
    char Language[10];          //
    char Parameter[5000];       //具体最大值，再看协议的说明了。
    char Referer[255];          // Referer头域允许客户端指定请求uri的源资源地址,如果指定的是部分uri地址，则此地址应该是一个相对地址。
    // empty line

    // 3-实体头
    char QueryString[1000];     // 查询字符串，通常用于Get 请求中的数据
    int ContentLength;
    bool IsValid;
};

///
/// \brief 解析http头
/// \param pHttpRequest http头内容
///
void ReadHttpHead(const char* pHttpRequest)
{
    char *pRequest = new char[strlen(pHttpRequest) + 1];
    strcpy(pRequest, pHttpRequest);
    strcat(pRequest, "\0");

    //该服务器不区别大小写，统一用小写。
    strlwr(pRequest);  // strlwr用于将字符串中的字符转换为小写
    T_HttpHeader t_head;
    char *pBegin = pRequest;
    char *pEnd = NULL;
    int nCount=0;

    //防止非法请求或者不合格请求，即前面有若干的空格。
    while(*pBegin == ' ')
    {
        ++pBegin;
    }

    // step1 处理请求行
    // 1.1 get method即获取请求方法
    pEnd = strchr(pBegin, ' '); //strchr 在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置

    // 地址偏移量
    nCount = pEnd-pBegin;
    if(nCount>0)
    {
        strncpy(t_head.RequestMethod, pBegin, nCount); // strncpy函数：多个n代表可以指定字符个数进行赋值
        t_head.RequestMethod[nCount]='\0';
    }
    if (strcmp(t_head.RequestMethod,"post") != 0 && strcmp(t_head.RequestMethod,"get") != 0)
    {
        delete[] pRequest;
        t_head.IsValid=true;
        return t_head;
    }
    else
    {
        t_head.IsValid=true;
    }

    // 1.2 get filepath即获取URI，表示客户希望访问的资源, 如 / 表示根目录
    pBegin = pEnd;
    while(*pBegin == ' ')
    {
        ++pBegin;
    }
    pEnd=strchr(pBegin,' ');
    nCount=0;
    nCount=pEnd-pBegin;
    if(nCount>0)
    {
        strncpy(t_head.FilePath,pBegin,nCount);
        t_head.FilePath[nCount]='\0';
    }

    // 1.3 get HTTP Version即获取HTTP协议的版本，如HTTP/1.1 表示1.1版本
    pBegin = pEnd;
    while(*pBegin == ' ')
    {
        ++pBegin;
    }
    pEnd = strchr(pBegin,'\n'); // 起始行结束
    nCount = 0;
    nCount = pEnd - pBegin;
    if (nCount > 0)
    {
        strncpy(t_head.HttpVersion, pBegin, nCount);
        t_head.HttpVersion[nCount] = '\0';
    }
    // end step1 起始行结束


    // step2 get Reference 获取各个头域
    // Referer头域允许客户端指定请求uri的源资源地址
    if(pBegin = strstr(pBegin,"referer:"))
    {
        pBegin += 8;
        while(*pBegin==' ')pBegin++;
        pEnd=strchr(pBegin,'\n');
        nCount=0;
        nCount=pEnd-pBegin;
        if(nCount>0)
        {
            strncpy(t_head.Referer,pBegin,nCount-1);
            t_head.Referer[nCount-1]='\0';
        }
    }


    //get host;
    // Host头域指定请求资源的Intenet主机和端口号，必须表示请求url的原始服务器或网关的位置。HTTP/1.1请求必须包含主机头域，否则系统会以400状态码返回。
    pBegin=pRequest;
    pBegin=strstr(pBegin,"host:"); // 函数用于判断字符串str2是否是str1的子串。如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL
    pEnd=strchr(pBegin,'\n');
    pBegin+=5;
    while(*pBegin==' ')pBegin++;
    nCount=0;
    nCount=pEnd-pBegin;
    if(nCount)
    {
        strncpy(t_head.Host,pBegin,nCount-1);
        t_head.Host[nCount-1]='\0';
    }

    //继续分析文件名
    //如果采用get的方法传递参数,会以?的形式跟在文件路径后面的。
    pBegin=t_head.FilePath;
    pBegin=strchr(pBegin,'?');
    if(pBegin)
    {
        strcpy(t_head.QueryString,pBegin+1);
        *pBegin='\0';
    }
    //从完整路径里面分离出相对路径
    pBegin=t_head.FilePath;
    if(strrchr(pBegin,'.'))
    {
        if(pBegin=strrchr(pBegin,'/'))
        {
            strcpy(t_head.FileName,pBegin+1);
            *(pBegin+1)='\0';
        }
    }
    else
    {
        t_head.FileName[0]='\0';
    }

    //when is method is post,get the parameter;
    //在post方式里面，表单数据与请求头之间一定会有一空行。
    //content-length:实体信息的长度
    if(strcmp(t_head.RequestMethod,"post")==0)
    {
        pBegin=pRequest;
        pBegin=strstr(pBegin,"content-length:");
        pEnd=strchr(pBegin,'\n');
        pBegin+=15;
        while(*pBegin==' ')pBegin++;
        nCount=pEnd-pBegin;
        if(nCount)
        {
            char temp[10];
            strncpy(temp,pBegin,nCount);
            temp[nCount]='\0';
            t_head.ContentLength=atoi(temp);
        }
        pBegin=pRequest;
        if(pBegin=strrchr(pBegin,'\n'))
        {
            strncpy(t_head.Parameter,pBegin+1,t_head.ContentLength);//直接复制到尾即可
            t_head.Parameter[t_head.ContentLength]='\0';
        }
    }
    else//Get时了最好欠赋一下初值。
    {
        t_head.ContentLength=0;
        t_head.Parameter[0]='\0';
    }
    delete[] pRequest;
    return t_head;

}

#endif //_HTTP_PARSER_H_
