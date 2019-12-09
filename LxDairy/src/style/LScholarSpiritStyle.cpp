#include "LScholarSpiritStyle.h"
#include <QStyleFactory>

CLScholarSpiritStyle::CLScholarSpiritStyle(QStyle *style)
    : QProxyStyle(QStyleFactory::create("windows")) // 默认windows风格
{

}

void CLScholarSpiritStyle::polish(QPalette &palette)
{

}
