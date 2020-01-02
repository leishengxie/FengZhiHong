#ifndef MODULE_LAMPLIGHT_H
#define MODULE_LAMPLIGHT_H

#include "ModuleDefine.h"


class CLamplightModule : public CModule
{
public:
	CLamplightModule();
	~CLamplightModule();

	void requreCreat(QString strTemplateName);

	void requreSet();

	void requreDeleteById(int nId);

	void requreGetById(int nId);

	void requreList(int nClubInfoId);

	void requreGetSongStyle(int nClubInfoId);

	void parseGet(QJsonObject objRoot);

	void parseList(QJsonObject objRoot);

private:
	//默认灯效
	QStringList m_strLstDefaultEffect;
};







#endif // MODULE_LAMPLIGHT_H
