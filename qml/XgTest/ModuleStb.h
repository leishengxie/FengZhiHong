#ifndef MODULE_STB_H
#define MODULE_STB_H

#include "ModuleDefine.h"


class CStbModule : public CModule
{
public:
	CStbModule();
	~CStbModule();

	void requreCreat(QString strTemplateName);

	void requreSet();

	void requreDeleteById(int nId);

	void requreGetById(int nId);

	void requreList(int nClubInfoId);

	void parseGet(QJsonObject objRoot);

	void parseList(QJsonObject objRoot);
};







#endif // MODULE_STB_H
