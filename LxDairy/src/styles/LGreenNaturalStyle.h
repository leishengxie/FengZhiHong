#ifndef CLGREENNATURALSTYLE_H
#define CLGREENNATURALSTYLE_H

#include <QProxyStyle>


class CLGreenNaturalStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLGreenNaturalStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);
};

#endif // CLGREENNATURALSTYLE_H
