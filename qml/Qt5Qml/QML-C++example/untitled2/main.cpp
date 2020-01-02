//#include <QtGui/QGuiApplication>
//#include "qtquick2applicationviewer.h"
//#include <QtQml>
#include "ColorMaker.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");

  //  QtQuick2ApplicationViewer viewer;
  //  viewer.setMainQmlFile(QStringLiteral("qml/colorMaker/main.qml"));
 //   viewer.showExpanded();

    QQuickView viwer;
      viwer.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    viwer.show();

    return app.exec();
}
