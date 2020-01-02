/******************************************************************************
**
** @file
** main.cpp
** @brief
** 迅歌主界面
** @author
** wangrm
** @date
** 2017-4-6
**
******************************************************************************/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include "Interface.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<Interface>("com.test.QObject", 1, 0, "Interface");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}
