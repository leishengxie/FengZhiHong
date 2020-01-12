#include "DairyGlobalInstance.h"
#include <QQmlEngine>
#include <QJSEngine>
#include <QtDebug>

CDairyGlobalInstance::CDairyGlobalInstance(QObject *parent)
    : QObject(parent)
{

}

QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    qDebug() << "-----provider------";
    CDairyGlobalInstance * p = CDairyGlobalInstance::getInstance();
    QQmlEngine::setObjectOwnership(p, QQmlEngine::CppOwnership);
    return p;
}
