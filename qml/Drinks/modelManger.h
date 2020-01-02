#ifndef QQMLMANGER_H
#define QQMLMANGER_H

#include <QObject>
#include "drinksmodel.h"

class CDrinksModel;
class QQmlContext;

class CModelMander: public QObject
{

Q_OBJECT


public:

	CModelMander(QObject* pParent = 0);
	~CModelMander();


public:
	static QQmlContext* g_pQmlContext;

public slots:
    void onMyselfCompleted();
	void onDrinksC(int nIndex);

private:
     QObject* m_pObjParent;
	 CDrinksModel* m_pDrinksModel;
};


#endif // QQMLMANGER_H
