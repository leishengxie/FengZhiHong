#ifndef ECHOPLUGIN_H
#define ECHOPLUGIN_H

#include "../qmenuiteminterface.h"

class EchoPlugin : public QObject, public QMenuItemInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "QMenuItemPlugin.QMenuItemPluginLib.QMenuItemInterface" FILE "EchoPluginLib.json")
#endif // QT_VERSION >= 0x050000

	Q_INTERFACES(QMenuItemInterface)

public:
	EchoPlugin(QObject *parent = 0);
	virtual QStringList funcType(void) const;
	virtual double func(const QString &type);
	virtual QAction* getAciton();
	virtual void setCallBack(EMITSIGNAL);	//设置信息回调
	//virtual void doSomething() = 0;		//信号不能为虚
	virtual void unload();
	virtual void updateFileIdFileInfo(const QString& fileId, const QString& md5, const QString& fileName, quint64 filesize);
	virtual bool isExistArchivingFile(const QString& fileId);		//归档中的的文件判断
	QWidget* createProcessCenter(QWidget* parent);
	void login() override;
//private slots:
//	virtual void slot_languageChanged() override;
private:
	QAction *m_action;
};

#endif // ECHOPLUGIN_H
