#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include "modelManger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	qmlRegisterType<CModelMander>("leisx.qt.ModelMander", 1, 0,"ModelMander");
    QQmlApplicationEngine engine;
	CModelMander::g_pQmlContext = engine.rootContext();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
