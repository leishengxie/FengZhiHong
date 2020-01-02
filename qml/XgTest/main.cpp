/******************************************************************************
**
** @file
** main.cpp
** @brief
** 应用程序入口main函数
** @par
** 未处理C++异常
** @author
** panxf
** @date
** 2017-4-18
**
******************************************************************************/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "ModelLamplightName.h"
#include "ModelLamplightContent.h"
#include "ModelStbName.h"
#include "ModelStbContent.h"
#include "ModuleManager.h"


int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);


	qmlRegisterType<CModelLamplightName>("com.xunge.Model", 1, 0, "ModelLamplightName");
	qmlRegisterType<CModelLamplightContent>("com.xunge.Model", 1, 0, "ModelLamplightContent");

	qmlRegisterType<CModelStbName>("com.xunge.Model", 1, 0, "ModelStbName");
	qmlRegisterType<CModelStbContent>("com.xunge.Model", 1, 0, "ModelStbContent");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/resource/main.qml")));

	((CLamplightModule*)CModuleManager::getInstance()
			->getModule(EM_Lamplight))->requreGetSongStyle(10000);


	return app.exec();
}


