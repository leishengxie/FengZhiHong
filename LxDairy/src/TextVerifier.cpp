#include "TextVerifier.h"

CTextVerifier::CTextVerifier(QObject *parent) : QObject(parent)
{

}


///
/// \brief Palindate::Palindate 回文验证
/// \param parent
///
Palindate::Palindate(QObject *parent)
    : QValidator(parent)
{

}

QValidator::State Palindate::validate(QString &strInput, int &) const
{
    QString strInputLower(strInput.toLower());
    QString strSkip("-_!,k. \t");
    foreach (QChar ch, strSkip) {
        strInputLower = strInputLower.remove(ch);
    }
    QString strRev;
    for (int i = strInput.length(); i > 0; --i)
    {
        strRev.append(strInput[i - 1]);
    }
    if (strInput == strRev)
    {
        return Acceptable;
    }
    else
    {
        return Intermediate;
    }
}


///
/// \brief CCommonRegExpValidator::CCommonRegExpValidator
/// \param parent
///
CCommonRegExpValidator::CCommonRegExpValidator(QObject *parent)
{
    // 正则表达式
    QRegExp regExp("[1][3,4,5,7,8][0-9]{9}");

    //
    QRegExp rxNum("[^ \u4e00-\u9fa5]+"); //非中文
    //QRegExp rx("[\u4e00-\u9fa5]");//中文
    //QRegExp rx("(([/xB0-/xF7][/xA1-/xFE])|([/x81-/xA0][/x40-/xFE])|([/xAA-/xFE][/x40-/xA0])|(/w))+"); //中文
}
