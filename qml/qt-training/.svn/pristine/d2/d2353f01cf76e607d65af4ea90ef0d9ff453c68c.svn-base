#include "modelManger.h"

#include <QQuickView>
#include <QQuickItem>
#include <QDebug>
#include <QQmlContext>
#include <QDateTime>

QQmlContext* CModelMander::g_pQmlContext = NULL;


CModelMander::CModelMander(QObject* pParent)
	: QObject(pParent)
{
	m_pDrinksModel = new CDrinksModel();
	//g_pQmlContext->setContextProperty("drinksNameModel", m_pDrinksModel->LstDrinks());
	g_pQmlContext->setContextProperty("drinksNameModel", m_pDrinksModel->e_GetLstDrinksCName());
	g_pQmlContext->setContextProperty("drinksModel", m_pDrinksModel);
}

CModelMander::~CModelMander()
{
	CC_SAFE_DELETE(m_pObjParent);
	CC_SAFE_DELETE(m_pDrinksModel);
}

void CModelMander::onMyselfCompleted()
{
	m_pObjParent = parent();
	//g_pQmlContext->setContextProperty("drinksNameModel", m_pDrinksModel->LstDrinks());
}

void CModelMander::onDrinksC(int nIndex)
{
	m_pDrinksModel->showModel(nIndex);
	qDebug() << "nIndex=" << nIndex;
}



