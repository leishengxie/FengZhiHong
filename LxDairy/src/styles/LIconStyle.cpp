#include "LIconStyle.h"

///
/// \brief CustomIconStyle::CustomIconStyle
///
///

CLIconStyle::CLIconStyle()
{
    mSize = 20;
}

CLIconStyle::~CLIconStyle()
{

}


void CLIconStyle::setCustomSize( int nSize )
{
    mSize = nSize;
}

int CLIconStyle::pixelMetric( PixelMetric metric, const QStyleOption * option, const QWidget * widget ) const
{
    int s = QCommonStyle::pixelMetric(metric, option, widget);
    if (metric == QStyle::PM_SmallIconSize)
    {
        s = mSize;
    }

    return s;
}
