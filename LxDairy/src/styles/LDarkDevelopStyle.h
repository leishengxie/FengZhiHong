#ifndef CLDARKDEVELOPSTYLE_H
#define CLDARKDEVELOPSTYLE_H

#include <QProxyStyle>


class CLDarkDevelopStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLDarkDevelopStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);
};


#endif // CLDARKDEVELOPSTYLE_H
