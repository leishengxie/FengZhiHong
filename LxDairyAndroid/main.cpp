#include "DairyAndroidApp.h"
#include <QQmlApplicationEngine>

//#include "QGuiApplication"
//#include "QApplication"

#include "ModelManager.h"
#include "DairyHttpRequest.h"

#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    CDairyAndroidApp app(argc, argv);
    //QApplication app(argc, argv);

    qmlRegisterType<CModelManager>("lxdairy.qt.ModelManager", 1, 0,"ModelManager");
    qmlRegisterType<CDairyHttpRequest>("lxdairy.qt.http", 1, 0,"DairyHttpRequest");
    //qmlRegisterType<CModelManager>("lxdairy.qt.ModelManager", 1, 0,"ModelManager");

    QQmlApplicationEngine engine;
    CModelManager::g_pQmlContext = engine.rootContext();
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
