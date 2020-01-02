#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include "CStandard.h"
#include "QQmlManger.h"
#include <iostream>

#include <QGuiApplication>

#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //QGuiApplication app(argc, argv);

    qmlRegisterType<QQmlManger>("guifan.qt.qQmlManger", 1, 0,"QQmlManger");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//    QQuickView viwer;
//      viwer.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
//      viwer.show();

    //Standard s;

    return app.exec();
}
