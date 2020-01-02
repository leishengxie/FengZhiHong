#include <QApplication>
#include <QQmlApplicationEngine>
#include "QOprateMsg.h"
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	//QQmlApplicationEngine engine;
	//engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	QOprateMsg qOprateMsg;
	qOprateMsg.show();

    return app.exec();
}
