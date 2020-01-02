#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
	//engine.addImportPath("E:\\leisx\\Qt5Project\\Qt5Qml\\ListViewEx");
	engine.addImportPath("E:\\leisx\\Qt5Project\\Qt5Qml");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
