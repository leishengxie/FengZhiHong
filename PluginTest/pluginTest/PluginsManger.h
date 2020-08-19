#ifndef QPULGINSMANGER_H
#define QPULGINSMANGER_H

#include <QObject>

class IPlugin;

class CPluginsManger
{
public:
    ~CPluginsManger();

protected:
    CPluginsManger();

public:
    static CPluginsManger* getInstance();

    QList<IPlugin*> loadPlugins();

	void unloadPlugins();
    void unloadPlugin(const QString & strFilePath);

private:
    QList<IPlugin*> m_lstPlugin;
    static CPluginsManger* s_pluginsManger;

};



#endif // QPULGINSMANGER_H
