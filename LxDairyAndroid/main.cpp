#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ModelManager.h"
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CModelManager>("lxdairy.qt.ModelManager", 1, 0,"ModelManager");
    QQmlApplicationEngine engine;
    CModelManager::g_pQmlContext = engine.rootContext();
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
