#ifndef CORIGINNUM_H
#define CORIGINNUM_H

#include <QObject>

///
/// \brief The T_SimpleNum struct   单纯的数字字符串 或 非数字字符串
///
struct T_SimpleNum
{
    QString strSimple;     // 源字符串
    int numericalValue;     // 数值
    bool bNumeric;          // 是否数字


    T_SimpleNum(QString strSimple)
        : strSimple(strSimple)
        , bNumeric(false)
        , numericalValue(0)
    {
        numericalValue = strSimple.toInt(&bNumeric);
    }


     // 返回用0占位后的数值字符串
    QString add(int num)
    {
        if (!bNumeric)
        {
            return strSimple;
        }

        numericalValue += num;
        strSimple = QString("%1").arg(numericalValue, strSimple.length(), 10, QLatin1Char('0'));
        return strSimple;

    }

    // 返回当前值后面num的数值字符串
    QString after(int num)
    {
        if (!bNumeric)
        {
            return strSimple;
        }

        int value = numericalValue + num;
        QString strSimpleAfter = QString("%1").arg(value, strSimple.length(), 10, QLatin1Char('0'));
        return strSimpleAfter;
    }
};



///
/// \brief The COriginNum class 复杂数字和非数字混排字符串
///
class COriginNum
{

public:
    explicit COriginNum(QString strOrginNum);
    ~COriginNum();

    // 返回加上nNum的数值字符串
    QString after(int nNum);

private:
    // 实现把连续的数字和非数字分割开来
    void splitOriginNum();

    //判断字符是否数字
    static bool isNumber(char ch)
    {
        if(ch < '0' || ch > '9')
        {
            return false;
        }
        return true;
    }

    // 判断一个字符串是否为纯数字
    static bool isDigitStr(QString src);

private:
    QString m_strOrginNum;
    QList<T_SimpleNum> m_lstOriginNum;
};

#endif // CORIGINNUM_H
