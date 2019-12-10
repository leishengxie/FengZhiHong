#include "LScholarSpiritStyle.h"
#include <QStyleFactory>

CLScholarSpiritStyle::CLScholarSpiritStyle(QStyle *style)
    : QProxyStyle(QStyleFactory::create("Fusion"))
{

}

void CLScholarSpiritStyle::polish(QPalette &palette)
{

}
