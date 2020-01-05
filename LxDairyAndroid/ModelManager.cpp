#include "ModelManager.h"

#include <QQuickView>
#include <QQuickItem>
#include <QDebug>
#include <QQmlContext>
#include <QDateTime>

#include "DairyListModel.h"

QQmlContext* CModelManager::g_pQmlContext = NULL;


CModelManager::CModelManager(QObject* pParent)
    : QObject(pParent)
{
    m_pDairyListModel = new CDairyListModel(this);

    g_pQmlContext->setContextProperty("dairyListModel", m_pDairyListModel);
}

CModelManager::~CModelManager()
{
    g_pQmlContext->deleteLater();
}

void CModelManager::onMyselfCompleted()
{
    m_pObjParent = parent();
}

//void CModelManager::onDrinksC(int nIndex)
//{
//	m_pDairyListModel->showModel(nIndex);
//	qDebug() << "nIndex=" << nIndex;
//}
