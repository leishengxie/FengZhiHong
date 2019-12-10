#include "LGreenNaturalStyle.h"
#include <QStyleFactory>


CLGreenNaturalStyle::CLGreenNaturalStyle(QStyle *style)
    : QProxyStyle(QStyleFactory::create("Windows"))
{

}

void CLGreenNaturalStyle::polish(QPalette &palette)
{

}
