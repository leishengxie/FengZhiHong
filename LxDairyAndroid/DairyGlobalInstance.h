#ifndef CDAIRYGLOBALINSTANCE_H
#define CDAIRYGLOBALINSTANCE_H

#include <QObject>
#include "Singleton.h"

class QQmlEngine;
class QJSEngine;

///
/// \brief The CDairyGlobalInstance class 本类主要提供给qml用
///
class CDairyGlobalInstance : public QObject, public CSingleton<CDairyGlobalInstance>
{
    Q_OBJECT
public:
    explicit CDairyGlobalInstance(QObject *parent = 0);

signals:
    void httpLoading();
    void httpLoadingFinished();

public slots:
};

QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

#endif // CDAIRYGLOBALINSTANCE_H
