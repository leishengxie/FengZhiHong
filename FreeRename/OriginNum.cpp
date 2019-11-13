#include "OriginNum.h"
#include <QtDebug>

COriginNum::COriginNum(QString strOrginNum)
    : m_strOrginNum(strOrginNum)
{
    createLstOriginNum();
}

COriginNum::~COriginNum()
{

}

void COriginNum::createLstOriginNum()
{
    m_lstOriginNum.clear();
    QString str = "";
    int nPrev = 0; //0-不确定 1-数字 2-非数字
    int nThis = 0;
    for (int i = 0; i < m_strOrginNum.length(); ++i) //轮询每个字符
    {
        qDebug() << "......1. " << m_strOrginNum[i];
        if (isNumber(m_strOrginNum[i].toLatin1()))
        {
            nThis = 1;
        }
        else
        {
            nThis = 2;
        }

        if (nPrev == nThis || nPrev == 0)
        {
            str += m_strOrginNum[i];
        }
        else
        {
            T_OriginNum tOriginNum;
            tOriginNum.lenth = str.length();
            tOriginNum.strNum = str;
            m_lstOriginNum.append(tOriginNum);
            str = m_strOrginNum[i];
        }

        if (i == m_strOrginNum.length() - 1)
        {
            T_OriginNum tOriginNum;
            tOriginNum.lenth = str.length();
            tOriginNum.strNum = str;
            m_lstOriginNum.append(tOriginNum);
        }
        nPrev = nThis;
        //        if (isNumber(m_strOrginNum[i].toLatin1()))
        //        {
        //            if ((nPrev != 2))
        //            {
        //                str = str + m_strOrginNum[i];
        //                qDebug() << "......2. " << str;
        //                if (i == m_strOrginNum.length() - 1)
        //                {
        //                    T_OriginNum tOriginNum;
        //                    tOriginNum.lenth = str.length();
        //                    tOriginNum.strNum = str;
        //                    m_lstOriginNum.append(tOriginNum);
        //                }
        //            }
        //            else
        //            {

        //                T_OriginNum tOriginNum;
        //                tOriginNum.lenth = str.length();
        //                tOriginNum.strNum = str;
        //                m_lstOriginNum.append(tOriginNum);
        //                str = "";
        //                if (i == m_strOrginNum.length() - 1)
        //                {
        //                    T_OriginNum tOriginNum;
        //                    tOriginNum.lenth = 1;
        //                    tOriginNum.strNum = m_strOrginNum[i];
        //                    m_lstOriginNum.append(tOriginNum);
        //                }
        //            }
        //            nPrev = 1;
        //        }
        //        else
        //        {
        //            if (nPrev != 1)
        //            {
        //                str = str + m_strOrginNum[i];
        //                qDebug() << "......3. " << str;
        //                if (i == m_strOrginNum.length() - 1)
        //                {
        //                    T_OriginNum tOriginNum;
        //                    tOriginNum.lenth = str.length();
        //                    tOriginNum.strNum = str;
        //                    m_lstOriginNum.append(tOriginNum);
        //                }
        //            }
        //            else
        //            {
        //                qDebug() << "......4. " << str;
        //                T_OriginNum tOriginNum;
        //                tOriginNum.lenth = str.length();
        //                tOriginNum.strNum = str;
        //                m_lstOriginNum.append(tOriginNum);
        //                str = "";
        //                if (i == m_strOrginNum.length() - 1)
        //                {
        //                    T_OriginNum tOriginNum;
        //                    tOriginNum.lenth = 1;
        //                    tOriginNum.strNum = m_strOrginNum[i];
        //                    m_lstOriginNum.append(tOriginNum);
        //                }
        //            }
        //            nPrev = 2;
        //        }
    }
}

QString COriginNum::add(int nNum)
{
    QString strResult = "";
    qDebug() << "m_lstOriginNum.size()=" << m_lstOriginNum.size();
    for (int i = 0; i < m_lstOriginNum.size(); ++i)
    {
        qDebug() << m_lstOriginNum[i].strNum;
        strResult += m_lstOriginNum[i].add(nNum);
    }
    return strResult;
}
