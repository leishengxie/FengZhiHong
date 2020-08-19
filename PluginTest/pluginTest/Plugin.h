#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QString>
#include <QIcon>
#include <QWidget>

class IPlugin
{
public:
    virtual ~IPlugin() {}
    virtual QString name() const = 0;
    virtual QIcon icon() const = 0;
    virtual QWidget* widget() = 0;
};

QT_BEGIN_NAMESPACE

#define IPlugin_iid "org.qt-project.Qt.IPlugin"
Q_DECLARE_INTERFACE(IPlugin, IPlugin_iid)

QT_END_NAMESPACE

#endif // IPLUGIN_H
