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
