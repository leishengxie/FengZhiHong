#include "LGreenNaturalStyle.h"
#include <QStyleFactory>


CLGreenNaturalStyle::CLGreenNaturalStyle(QStyle *style)
    : QProxyStyle(QStyleFactory::create("windows")) // 默认windows风格
{

}

void CLGreenNaturalStyle::polish(QPalette &palette)
{

}
