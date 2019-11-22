#include "DairyApp.h"
#include <QtDebug>

CDairyApp::CDairyApp(int argc, char *argv[])
    : QApplication(argc, argv)
{

}

CDairyApp::~CDairyApp()
{

}

bool CDairyApp::notify(QObject *obj, QEvent *e)
{
    return QApplication::notify(obj, e);
}
