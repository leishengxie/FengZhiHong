#ifndef CORIGINNUM_H
#define CORIGINNUM_H

#include <QObject>

// 用户需要输入的数字前加0占位才能确定占位长度， 如001表示3位占位
struct T_OriginNum
{
    int lenth; //占位长度
    QString strNum; //起始值
    T_OriginNum()
        : lenth(0)
        , strNum("0")
    {

    }

    QString add(int num) // 返回用0占位后的数值
    {
        QString strResult;
        bool bOk;
        int result = strNum.toInt(&bOk);
        if (!bOk)
        {
            return strNum;
        }
            result += num;
            strResult = QString("%1").arg(result,lenth,10,QLatin1Char('0'));
        return strResult;
        //strNum = QString::number(result);
    }
};





//起始值
/****
 *
 产生数字列
 */
class COriginNum : public QObject
{
    Q_OBJECT

public:
    explicit COriginNum(QString strOrginNum);
    ~COriginNum();

    QString add(int nNum);

private:
    void createLstOriginNum();
    //判断字符是否数字
    bool isNumber(char ch)
    {
        if(ch <'0'|| ch >'9')
        {
            return false;
        }
        return true;
    }

    /***
      *判断一个字符串是否为纯数字
      */
    bool isDigitStr(QString src)
    {
        QByteArray ba = src.toLatin1();//QString 转换为 char*
        const char *s = ba.data();

        while(*s && *s>='0' && *s<='9')
        {
            s++;
        }
        if (*s) //指针指向最后一个0
        { //不是纯数字
            return false;
        }
        return true;
    }

private:
    QString m_strOrginNum;
    QList<T_OriginNum> m_lstOriginNum;
};

#endif // CORIGINNUM_H
