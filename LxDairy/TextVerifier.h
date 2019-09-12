#ifndef CTEXTVERIFIER_H
#define CTEXTVERIFIER_H

#include <QObject>


///
/// \brief The CTextVerifier class @用于验证文本的合法性
///
class CTextVerifier : public QObject
{
    Q_OBJECT
public:
    explicit CTextVerifier(QObject *parent = 0);

public:
    static bool isValidPasswd(QString strPasswd, unsigned int unMaxLength, bool bCkeckP);

signals:

public slots:
};

#endif // CTEXTVERIFIER_H
