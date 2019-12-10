#ifndef CLSCHOLARSPIRITSTYLE_H
#define CLSCHOLARSPIRITSTYLE_H

#include <QProxyStyle>

class CLScholarSpiritStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLScholarSpiritStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);
};

#endif // CLSCHOLARSPIRITSTYLE_H
