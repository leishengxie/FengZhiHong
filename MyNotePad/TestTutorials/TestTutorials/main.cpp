#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
	engine.addImportPath("../imports");
	engine.load(QUrl(QStringLiteral("../main.qml")));

    return app.exec();
}
