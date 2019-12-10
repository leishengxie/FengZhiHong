#ifndef CLQUIETSTYLE_H
#define CLQUIETSTYLE_H
#include <QProxyStyle>

class CLQuietStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLQuietStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);
};

#endif // CLQUIETSTYLE_H
