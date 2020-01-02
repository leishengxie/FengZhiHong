#include "QGlobal.h"

QGlobal::QGlobal()
{

}

QString QGlobal::s_getChineseSpell(QString &src)
{
    wchar_t wchr;
    QString strPinYin;
    for (int i=0; i<src.length(); i++)
    {
        QString str = src.at(i);
        QByteArray arr = str.toLocal8Bit();

        wchr = (arr.at(0) & 0xff) << 8;
        wchr |= (arr.at(1) & 0xff);
        strPinYin.append(s_convert(wchr));
    }
    return strPinYin;
}

bool QGlobal::s_in(wchar_t start, wchar_t end, wchar_t code)
{
    if (code >= start && code <= end)
    {
        return true;
    }
        return false;
}


char QGlobal::s_convert(int n)
{
    if (s_in(0xB0A1,0xB0C4,n)) return 'a';
    if (s_in(0XB0C5,0XB2C0,n)) return 'b';
    if (s_in(0xB2C1,0xB4ED,n)) return 'c';
    if (s_in(0xB4EE,0xB6E9,n)) return 'd';
    if (s_in(0xB6EA,0xB7A1,n)) return 'e';
    if (s_in(0xB7A2,0xB8c0,n)) return 'f';
    if (s_in(0xB8C1,0xB9FD,n)) return 'g';
    if (s_in(0xB9FE,0xBBF6,n)) return 'h';
    if (s_in(0xBBF7,0xBFA5,n)) return 'j';
    if (s_in(0xBFA6,0xC0AB,n)) return 'k';
    if (s_in(0xC0AC,0xC2E7,n)) return 'l';
    if (s_in(0xC2E8,0xC4C2,n)) return 'm';
    if (s_in(0xC4C3,0xC5B5,n)) return 'n';
    if (s_in(0xC5B6,0xC5BD,n)) return 'o';
    if (s_in(0xC5BE,0xC6D9,n)) return 'p';
    if (s_in(0xC6DA,0xC8BA,n)) return 'q';
    if (s_in(0xC8BB,0xC8F5,n)) return 'r';
    if (s_in(0xC8F6,0xCBF0,n)) return 's';
    if (s_in(0xCBFA,0xCDD9,n)) return 't';
    if (s_in(0xCDDA,0xCEF3,n)) return 'w';
    if (s_in(0xCEF4,0xD188,n)) return 'x';
    if (s_in(0xD1B9,0xD4D0,n)) return 'y';
    if (s_in(0xD4D1,0xD7F9,n)) return 'z';
    return '\0';
}
