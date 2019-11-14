#include "OriginNum.h"
#include <QtDebug>

COriginNum::COriginNum(QString strOrginNum)
    : m_strOrginNum(strOrginNum)
{
    splitOriginNum();
}

COriginNum::~COriginNum()
{

}



///
/// \brief COriginNum::createLstOriginNum 把连续的数字和非数字分割开来
///
///
enum
{
    EN_NotSure, //不确定
    EN_Numeric, //数字
    EN_NonNumeric   //非数字
};
void COriginNum::splitOriginNum()
{
    m_lstOriginNum.clear();
    QString str = "";   // 连续的字符串
    int nPrev = EN_NotSure; // 0-不确定，标示首次 1-数字 2-非数字
    int nThis = EN_NotSure;

     // 轮询每个字符
    for (int i = 0; i < m_strOrginNum.length(); ++i)
    {

        if (isNumber(m_strOrginNum[i].toLatin1()))
        {
            nThis = EN_Numeric;
        }
        else
        {
            nThis = EN_NonNumeric;
        }

        // 如果连续则添加，不连续则加入列表
        if (nPrev == nThis || nPrev == EN_NotSure)
        {
            str += m_strOrginNum[i];
        }
        else
        {
            m_lstOriginNum.append(T_SimpleNum(str));

            str = m_strOrginNum[i];
        }

        if (i == m_strOrginNum.length() - 1)
        {
            m_lstOriginNum.append(T_SimpleNum(str));
        }
        nPrev = nThis;

    }
}

bool COriginNum::isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char* s = ba.data();

    while(*s && *s >= '0' && *s <= '9')
    {
        s++;
    }
    if (*s) //指针指向最后一个0
    {
        //不是纯数字
        return false;
    }
    return true;
}

QString COriginNum::after(int nNum)
{
    QString strResult = "";
    qDebug() << "m_lstOriginNum.size()=" << m_lstOriginNum.size();
    for (int i = 0; i < m_lstOriginNum.size(); ++i)
    {
        strResult += m_lstOriginNum[i].after(nNum);
    }
    return strResult;
}
