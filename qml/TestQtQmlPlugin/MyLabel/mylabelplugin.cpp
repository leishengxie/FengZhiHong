#include "cmylabel.h"
#include "mylabelplugin.h"

#include <QtPlugin>

CMyLabelPlugin::CMyLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CMyLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CMyLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CMyLabelPlugin::createWidget(QWidget *parent)
{
    return new CMyLabel(parent);
}

QString CMyLabelPlugin::name() const
{
    return QLatin1String("CMyLabel");
}

QString CMyLabelPlugin::group() const
{
    return QLatin1String("");
}

QIcon CMyLabelPlugin::icon() const
{
    return QIcon();
}

QString CMyLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CMyLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CMyLabelPlugin::isContainer() const
{
    return false;
}

QString CMyLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CMyLabel\" name=\"cMyLabel\">\n</widget>\n");
}

QString CMyLabelPlugin::includeFile() const
{
    return QLatin1String("cmylabel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(cmylabelplugin, CMyLabelPlugin)
#endif // QT_VERSION < 0x050000
