#include "ModelManager.h"

#include <QQuickView>
#include <QQuickItem>
#include <QDebug>
#include <QQmlContext>
#include <QDateTime>

#include "DairyListModel.h"


CModelManager::CModelManager(QObject* pParent)
    : QObject(pParent)
    , m_pQmlContext(NULL)
    , m_pDairyListModel(new CDairyListModel(this))
{

}

CModelManager::~CModelManager()
{

}

void CModelManager::loadContextProperty()
{
    if (NULL == m_pQmlContext)
    {
        return;
    }
    // 对象设置为 QML 的上下文属性
    m_pQmlContext->setContextProperty("ModelManagerInstance", CModelManager::getInstance());

    m_pQmlContext->setContextProperty("dairyListModel", m_pDairyListModel);


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
