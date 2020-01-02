#include "ModuleManager.h"


CModuleManager* CModuleManager::m_ModuleManager = NULL;

CModuleManager* CModuleManager::getInstance()
{
	if (NULL == m_ModuleManager)
	{
		m_ModuleManager = new CModuleManager();
	}
	return m_ModuleManager;
}

CModuleManager::CModuleManager()
	: m_pModuleLamplight(new CLamplightModule)
	, m_pModuleStb(new CStbModule)
{

}


CModule* CModuleManager::getModule(E_ModuleType moduleType)
{
	switch (moduleType)
	{
	case EM_Lamplight:
		return m_pModuleLamplight;
	case EM_STB:
		return m_pModuleStb;
	default:
		break;
	}
}

