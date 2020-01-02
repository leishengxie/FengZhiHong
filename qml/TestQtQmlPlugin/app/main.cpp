#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
	//engine.addImportPath("E:\\leisx\\Qt5Project");
	engine.addImportPath("E:\\leisx\\Qt5Project\\QMLPlugin");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
