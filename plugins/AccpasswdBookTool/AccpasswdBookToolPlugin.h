#ifndef CACCPASSWDBOOKTOOLPLUGIN_H
#define CACCPASSWDBOOKTOOLPLUGIN_H

#include <Plugin.h>

#include <QObject>
#include <QtPlugin>

class CAccpasswdBookToolPlugin : public QObject, IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.IPlugin" FILE "AccpasswdBookToolPlugin.json")
    Q_INTERFACES(IPlugin)
public:
    explicit CAccpasswdBookToolPlugin(QObject *parent = nullptr);
    QString name() const Q_DECL_OVERRIDE;
    QIcon icon() const Q_DECL_OVERRIDE;
    QWidget* widget() Q_DECL_OVERRIDE;

signals:

};

#endif // CACCPASSWDBOOKTOOLPLUGIN_H
