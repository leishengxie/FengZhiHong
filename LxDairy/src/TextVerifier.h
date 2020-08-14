#ifndef CTEXTVERIFIER_H
#define CTEXTVERIFIER_H

#include <QObject>
#include <QValidator>


///
/// \brief The CTextVerifier class @用于验证文本的合法性
/// 1.掩码 mask input, 针对QLineEdit setInputMask, 主要验证哪个位置的何种字符是允许的。
/// 2.验证器 validator 针对QLineEdit setValidator, 包含数字，正则表达式等
///
class CTextVerifier : public QObject
{
    Q_OBJECT
public:
    explicit CTextVerifier(QObject *parent = 0);

public:
    static bool isValidPasswd(QString strPasswd, unsigned int unMaxLength, bool bCkeckP);

    QString phoneMask() const;

signals:

public slots:
};

// 回文字符串验证
class Palindate : public QValidator
{
    Q_OBJECT
public:
    explicit Palindate(QObject* parent = 0);
    QValidator::State validate(QString & strInput, int &) const;
};

#endif // CTEXTVERIFIER_H
