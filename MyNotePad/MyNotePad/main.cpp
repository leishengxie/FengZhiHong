#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // 添加自定义的库
    //engine.addImportPath("E:\\leisx\\Qt5Project\\MyNotePad\\imports");
    //engine.addImportPath("./imports");
    engine.addImportPath("F:\\work\\pro\\LxDairy\\MyNotePad\\MyNotePad\\imports");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
