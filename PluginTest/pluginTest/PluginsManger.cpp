#include "PluginsManger.h"



CPluginsManger::CPluginsManger()
    :Singleton<CPluginsManger>(),
	m_EchoInterface(nullptr)

{
	m_pluginItemMap.clear();
	m_pluginloaderMap.clear();
	loadPlugins();
	mdsv_add_logger("QPluginsManger插件加载完成");
}

void CPluginsManger::testPlugin()
{
	//foreach(PluginItem item, m_pluginItemList)
	//{
	//	QMenuItemInterface *eInterface = qobject_cast<QMenuItemInterface *>(item.plugin);
	//	double ret = eInterface->func(item.text);
	//	eInterface->getAciton()->trigger();
	//}
}

CPluginsManger::~CPluginsManger()
{

}


void CPluginsManger::deletePlugins()
{
	QMutableMapIterator<QString, QPluginLoader*> plugins(m_pluginloaderMap);
	for (; plugins.hasNext();)
	{
		QPluginLoader *loader = plugins.next().value();
		QObject *plugin = loader->instance();
		if (plugin != 0)
		{
			//plugin->disconnect();
			//plugin->blockSignals(true);
			plugin->deleteLater();
			//delete plugin;
		}
		if (loader->isLoaded())
		{
			//loader->unload();
			loader->deleteLater();
		}
	}
	m_pluginloaderMap.clear();
}
void CPluginsManger::unloadPlugins()
{
	QMutableMapIterator<QString, QPluginLoader*> plugins(m_pluginloaderMap);
	for (;plugins.hasNext();)
	{
		QPluginLoader *loader = plugins.next().value();
		QObject *plugin = loader->instance();
		if (plugin != 0)
		{
			QMenuItemInterface *eInterface = qobject_cast<QMenuItemInterface *>(plugin);
			//eInterface->setCallBack(nullptr);
			eInterface->unload();
			//emit eInterface->signalUnload();
		}
		//if (loader->isLoaded())
		//{
		//	loader->unload();
		//}
	}
	//m_pluginloaderMap.clear();
}

void CPluginsManger::loadPlugins()
{
	m_pluginItemMap.clear();
	m_pluginloaderMap.clear();
	//QStringList pluginPath = QCoreApplication::libraryPaths();
	//QCoreApplication::addLibraryPath("C:/some/other/path");   //添加库搜索路径
	//静态调用插件
	//Q_IMPORT_PLUGIN(EchoPlugin)
	//foreach(QObject *plugin, QPluginLoader::staticInstances())
	//{
	//	AddToPluginLst(plugin);
	//}

	//动态调用插件
	QDir pluginDir(MDSV_PLUGIN_PATH);

	//遍历当前 文件夹下文件
	foreach(QString filename, pluginDir.entryList(QDir::Files))
	{
		QPluginLoader *pluginloader = new QPluginLoader(pluginDir.absoluteFilePath(filename));
		QObject *plugin = pluginloader->instance();
		if (plugin != 0)
		{
			AddToPluginLst(plugin);
			m_pluginloaderMap.insert(pluginDir.absoluteFilePath(filename), pluginloader);
		}
		else
		{
			pluginloader->unload();
		}
		//m_pluginloaderMap.insert(pluginDir.absoluteFilePath(filename), pluginloader);
	}
}

void CPluginsManger::AddToPluginLst(QObject * plugin)
{
	QMenuItemInterface *eInterface = qobject_cast<QMenuItemInterface *>(plugin);
	if (eInterface != 0)
	{
		QStringList typelist = eInterface->funcType();
		eInterface->setCallBack(dataRecv);
		foreach(QString ctype, typelist)
		{
			PluginItem item;
			item.text = ctype;
			item.plugin = plugin;
			m_pluginItemMap.insert(ctype, item);
		}
	}
}

void CPluginsManger::updateEdtFileInfo(const QString& fileId, const QString& md5, const QString& fileName, quint64 filesize)
{
	QMutableMapIterator<QString, QPluginLoader*> plugins(m_pluginloaderMap);
	for (; plugins.hasNext();)
	{
		QObject *plugin = plugins.next().value()->instance();
		if (plugin != 0)
		{
			QMenuItemInterface *eInterface = qobject_cast<QMenuItemInterface *>(plugin);
			eInterface->updateFileIdFileInfo(fileId, md5, fileName, filesize);
		}
	}
}

