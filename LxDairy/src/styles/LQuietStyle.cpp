#include "LQuietStyle.h"
#include <QStyleFactory>


CLQuietStyle::CLQuietStyle(QStyle *style)
    : QProxyStyle(QStyleFactory::create("WindowsXP"))
{

}

void CLQuietStyle::polish(QPalette &palette)
{



}
