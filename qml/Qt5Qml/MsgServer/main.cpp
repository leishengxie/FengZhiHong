#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include "QUdpConnect.h"
#include "QQmlManger.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<QQmlManger>("msg.qt.qQmlManger", 1, 0,"QQmlManger");

    QQmlApplicationEngine engine;
	QQmlManger::g_pQmlContext = engine.rootContext();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
