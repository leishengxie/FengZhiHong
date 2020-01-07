#ifndef CMODELMANAGER_H
#define CMODELMANAGER_H

#include <QObject>
#include "Singleton.h"

class CDairyListModel;
class QQmlContext;

class CModelManager: public QObject, public CSingleton<CModelManager>
{

Q_OBJECT
public:

    CModelManager(QObject* pParent = 0);
    ~CModelManager();
public:
    void setQmlContext(QQmlContext* pQmlContext)
    {
        m_pQmlContext = pQmlContext;
    }

    CDairyListModel* dairyListModel()
    {
        return m_pDairyListModel;
    }

    void loadContextProperty();

public slots:
    void onMyselfCompleted();
    //void onDrinksC(int nIndex);

private:
     QObject* m_pObjParent;
     CDairyListModel* m_pDairyListModel;
     QQmlContext* m_pQmlContext;
};

#endif // CMODELMANAGER_H
