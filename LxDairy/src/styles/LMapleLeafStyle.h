#ifndef CLMAPLELEAFSTYLE_H
#define CLMAPLELEAFSTYLE_H

#include <QProxyStyle>


class CLMapleLeafStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLMapleLeafStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);


};

#endif // CLMAPLELEAFSTYLE_H
