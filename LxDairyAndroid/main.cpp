#include "DairyAndroidApp.h"
#include <QQmlApplicationEngine>

//#include "QGuiApplication"
//#include "QApplication"

#include "DairyListModel.h" // 有了ModelManager.h为什么还有包含此文件???
#include "ModelManager.h"
#include "DairyHttpRequest.h"

#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    CDairyAndroidApp app(argc, argv);
    //QApplication app(argc, argv);

//    Qt 提供了两种在 QML 环境中使用 C++ 对象的方式：
//    在 C++ 中实现一个类。注冊到 QML 环境中， QML 环境中使用该类型创建对象
//    在 C++ 中构造一个对象。将这个对象设置为 QML 的上下文属性，在 QML 环境中直接使用改属性
    //qmlRegisterType<CModelManager>("lxdairy.qt.ModelManager", 1, 0,"ModelManager");
    qmlRegisterType<CDairyHttpRequest>("lxdairy.qt.http", 1, 0,"DairyHttpRequest");
    qmlRegisterType<CDairyListModel>("lxdairy.qt.model", 1, 0,"DairyListModel");
    //qmlRegisterType<CModelManager>("lxdairy.qt.ModelManager", 1, 0,"ModelManager");

    // 注册单例类 --看了官方例子，没看出哪里是单例，所以没什么卵用
    //qmlRegisterSingletonType

    QQmlApplicationEngine engine;
    CModelManager::getInstance()->setQmlContext(engine.rootContext());
    CModelManager::getInstance()->loadContextProperty();
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
