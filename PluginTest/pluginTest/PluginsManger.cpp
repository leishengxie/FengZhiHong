#include "PluginsManger.h"
#include <Plugin.h>
#include <QPluginLoader>
#include <QApplication>
#include <QDir>

CPluginsManger* CPluginsManger::s_pluginsManger = nullptr;

CPluginsManger::CPluginsManger()
{

}

CPluginsManger *CPluginsManger::getInstance()
{
    if(nullptr == s_pluginsManger)
    {
        s_pluginsManger = new CPluginsManger();
    }
    return s_pluginsManger;
}


CPluginsManger::~CPluginsManger()
{

}


QList<IPlugin *> CPluginsManger::loadPlugins()
{
    // 加载静态插件
    foreach (QObject *plugin, QPluginLoader::staticInstances())
    {
        //plugin->metaObject()->className();
    }

    // 加载动态插件
    QDir dirPlugins(qApp->applicationDirPath());

    // 新建了plugins文件夹，把上面生成的dll文件放到此文件夹下
    dirPlugins.cd("plugins");

    //加载当前文件夹下的库文件
    foreach(QString fileName, dirPlugins.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(dirPlugins.absoluteFilePath(fileName));
        QObject *objPlugin = pluginLoader.instance();
        if (objPlugin)
        {
            IPlugin * pPlugin = qobject_cast<IPlugin *>(objPlugin);
            if (pPlugin)
            {
                m_lstPlugin.append(pPlugin);
            }
        }
    }
    return m_lstPlugin;
}

void CPluginsManger::unloadPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances())
    {
        //
    }

    // 加载动态插件
    QDir dirPlugins(qApp->applicationDirPath());

    // 新建了plugins文件夹，把上面生成的dll文件放到此文件夹下
    dirPlugins.cd("plugins");

    //加载当前文件夹下的库文件
    foreach(QString fileName, dirPlugins.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(dirPlugins.absoluteFilePath(fileName));
        QObject *objPlugin = pluginLoader.instance();
        if (objPlugin)
        {
            pluginLoader.unload();
        }
    }
}

void CPluginsManger::unloadPlugin(const QString &strFilePath)
{

}



