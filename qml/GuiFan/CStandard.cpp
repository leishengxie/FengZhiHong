#include <QDebug>
#include "CStandard.h"
#include "bin.h"

const char* g_pC1 = "jkl";
char* const g_pC2 = "abc";
const char* const g_pC3 = "def";

int g_nStudent = 5;


void s_InternalFunc(void)
{
    cout << "local fuction" << endl;
}

void g_Func(int nArg)
{
    cout << "external fuction" << endl;
}

int Standard::s_nMan = 5;
double Standard::s_dLand = 56.2;

Standard::Standard():m_nToal(10)
  ,m_fMoney(100.5f)
  ,m_nPeople(10)
{
    cout << "hello world" << endl;
    s_InternalFunc();
    g_Func(1);

    printf("%d",getMaxInt());
    std::cout << getMaxInt() << std::endl;
    qDebug() << mulTwo(5);
}

