/******************************************************************************
**
** @file
** main.cpp
** @brief
** 主程序
** @author
** wenn
** @date
** 2017-3-29
**
******************************************************************************/
#include <QApplication>
#include <QQmlApplicationEngine>

// 分支测试
// 主支测试
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

// 主干测试
