#ifndef TOOLA_H
#define TOOLA_H

#include <QObject>
#include <Plugin.h>
#include <QtPlugin>

class CToolB : public QObject, IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.IPlugin" FILE "ToolB.json")
    Q_INTERFACES(IPlugin)
public:
    CToolB();
    QString name() const Q_DECL_OVERRIDE;
    QIcon icon() const Q_DECL_OVERRIDE;
    QWidget* widget() Q_DECL_OVERRIDE;

};

#endif // TOOLA_H

