/***************************************
//@par 模块名
// Standard
// @par 相关文件
// Standard.cpp
// @par 功能详细描述
// C++ Standard
// @par 多线程安全性
// 否，多线程共享时需要显式同步和互斥
// @par 异常时安全性
// 是，满足资源申请即初始化准则
// @par 备注
// c++标准书写测试
// @file Standard.h
// @brief C++标准书写测试
// @author leishengxie
// @version 1.0
// @date 2017-3-8
// @todo -
******************************************/
#ifndef STANDARD_H
#define STANDARD_H

#include <iostream>
#include <vector>
using namespace std;

typedef std::vector< int > vint;
typedef vector<string> vstr;


enum E_ButtonType
{
LB_ButtonSet,
LB_ButtonTool,
LB_Number
};

union U_Panel
{
int nID;
char cType;
};

struct T_Man
{
    int nHand;
    int nFoot;
    T_Man(): nHand(2), nFoot(2){}
};



static int s_nInternal = 1;
static void s_InternalFunc(void);
static int s_nWoman = 5;

extern int g_nStudent;
extern void g_Func(int nArg);

class Standard
{
public:
    Standard();

public:
    static int s_nMan;
    static double s_dLand;

private:
    //volatile int m_nToal;
    int m_nToal;
    float m_fMoney;
    int m_nPeople;


};

#endif // STANDARD_H
