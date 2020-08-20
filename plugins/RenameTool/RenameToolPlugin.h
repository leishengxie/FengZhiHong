#ifndef CRENAMETOOLPLUGIN_H
#define CRENAMETOOLPLUGIN_H

#include <Plugin.h>

#include <QObject>
#include <QtPlugin>

class CRenameToolPlugin : public QObject, IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.IPlugin" FILE "RenameToolPlugin.json")
    Q_INTERFACES(IPlugin)
public:
    explicit CRenameToolPlugin(QObject *parent = nullptr);
    QString name() const Q_DECL_OVERRIDE;
    QIcon icon() const Q_DECL_OVERRIDE;
    QWidget* widget() Q_DECL_OVERRIDE;

signals:

};

#endif // CRENAMETOOLPLUGIN_H


