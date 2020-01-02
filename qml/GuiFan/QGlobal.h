#ifndef CGLOBAL_H
#define CGLOBAL_H
#include <QString>


class QGlobal
{
public:
    QGlobal();
    static QString s_getChineseSpell(QString& src);
    static bool s_in(wchar_t start, wchar_t end, wchar_t code);
    static char s_convert(int n);
};

#endif // CGLOBAL_H
