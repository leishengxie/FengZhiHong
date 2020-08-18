#include "custom.h"
#include "customplugin.h"

#include <QtPlugin>

CustomPlugin::CustomPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CustomPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CustomPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CustomPlugin::createWidget(QWidget *parent)
{
    return new Custom(parent);
}

QString CustomPlugin::name() const
{
    return QLatin1String("Custom");
}

QString CustomPlugin::group() const
{
    return QLatin1String("");
}

QIcon CustomPlugin::icon() const
{
    return QIcon(QLatin1String(":/label_red.png"));
}

QString CustomPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CustomPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CustomPlugin::isContainer() const
{
    return false;
}

QString CustomPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Custom\" name=\"custom\">\n</widget>\n");
}

QString CustomPlugin::includeFile() const
{
    return QLatin1String("custom.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(customplugin, CustomPlugin)
#endif // QT_VERSION < 0x050000
