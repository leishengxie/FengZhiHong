#ifndef CMODULEMANAGER_H
#define CMODULEMANAGER_H

#include <QObject>
#include "ModuleLamplight.h"
#include "ModuleStb.h"

class CModuleManager: public QObject
{
	Q_OBJECT

public:
	CModuleManager();

	static CModuleManager* getInstance();

	CModule* getModule(E_ModuleType moduleType);


private:
	//实例
	static CModuleManager* m_ModuleManager;

private:
	//灯光模块
	CLamplightModule* m_pModuleLamplight;

	//机顶盒模块
	CStbModule* m_pModuleStb;

};

#endif // CMODULEMANAGER_H
