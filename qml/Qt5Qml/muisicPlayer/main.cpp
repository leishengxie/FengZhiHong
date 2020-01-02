#include <QApplication>
#include <QQuickView>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView view(QUrl(QStringLiteral("qrc:/main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setFlags(Qt::FramelessWindowHint);
    view.setDefaultAlphaBuffer(true);
    view.setColor(QColor(Qt::transparent));
   // view.setGeometry(50,0,400,650);
    view.rootContext() -> setContextProperty("mainWindow", &view);
    view.show();
    //view.showFullScreen();
    return app.exec();
}
