#include "DairyAndroidApp.h"
#include <QQmlApplicationEngine>

//#include "QGuiApplication"
//#include "QApplication"

#include "DairyListModel.h" // 有了ModelManager.h为什么还有包含此文件???
#include "ModelManager.h"
#include "DairyHttpRequest.h"
#include "DairyGlobalInstance.h"

#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QtQml>

// 由于qt打包时并没有把LQtTool依赖的qt库打完整， 所以需要手动加一下pro QT+=
#include <QMediaPlayer>
#include <QDomDocument>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    CDairyAndroidApp app(argc, argv);
    //QApplication app(argc, argv);

//    Qt 提供了两种在 QML 环境中使用 C++ 对象的方式：
//    在 C++ 中实现一个类。注冊到 QML 环境中， QML 环境中使用该类型创建对象
//    在 C++ 中构造一个对象。将这个对象设置为 QML 的上下文属性，在 QML 环境中直接使用改属性
    //qmlRegisterType<CModelManager>("lxdairy.qt.ModelManager", 1, 0,"ModelManager");
    qmlRegisterType<CDairyHttpRequest>("lxdairy.qt.http", 1, 0,"DairyHttpRequest");
    qmlRegisterType<CDairyListModel>("lxdairy.qt.model", 1, 0,"DairyListModel");
    //qmlRegisterType<CModelManager>("lxdairy.qt.ModelManager", 1, 0,"ModelManager");

    // 注册单例类 --看了官方例子
    // 尽量用c++的全局，毕竟c++和qml都可以用c++的全局
    //qmlRegisterSingletonType
    qmlRegisterSingletonType( QUrl("qrc:/qml/global/QmlGlobalObj.qml"), "lxdairy.global", 1, 0, "QmlGlobalObj" );
    qmlRegisterSingletonType<CDairyGlobalInstance>( "lxdairy.cpp.global", 1, 0, "DairyGlobalInstance", provider );
    // -额外了解:
    // QML从ECMAScript继承而来，所以支持这个ECMAScript。经常在QML工程中看到Math、Data.....等方法，但是在Qt手册里搜索不到，这是因为这些方法不是QtQuick的，而是ECMAScript的。
    // QML除了支持ECMAScript内置对象对象外,还自己给用户提供了许多宿主对象.当然用户也可以自己自定义对象.
    // 内置对象 : 由 ECMAScript所提供的对象;如Object、Array、Math、Date等等。
    // 宿主对象 ：即由 ECMAScript 实现的宿主环境提供的对象,比如Qt对象.
    // 自定义对象 ：自定义构造函数所创建的对象。

    QQmlApplicationEngine engine;
    CModelManager::getInstance()->setQmlContext(engine.rootContext());
    CModelManager::getInstance()->loadContextProperty();
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
