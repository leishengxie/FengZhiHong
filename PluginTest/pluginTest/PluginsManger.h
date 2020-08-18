#ifndef QPULGINSMANGER_H
#define QPULGINSMANGER_H

#include <QObject>

struct PluginItem{
	QString text;
	QObject * plugin;
};
//#define LIBRARY_LIBRARY

class CPluginsManger : public QObject
{
    Q_OBJECT
public:
    ~CPluginsManger();

protected:

    CPluginsManger();
public:

	void loadPlugins();
	void deletePlugins();
	void unloadPlugins();
	void testPlugin();


private:
	void AddToPluginLst(QObject * plugin);
private:
	QMenuItemInterface *m_EchoInterface;
	QMap<QString, PluginItem> m_pluginItemMap;
	QMap<QString, QPluginLoader*>  m_pluginloaderMap;
	//QThreadPool m_pluginsThreadPool;		//插件线程池
};

//宏定义来获取配置
#define QMENUITEMPULGINSMANGER  QPluginsManger::getInstance()

#endif // QPULGINSMANGER_H
