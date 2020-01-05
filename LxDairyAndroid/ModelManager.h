#ifndef CMODELMANAGER_H
#define CMODELMANAGER_H

#include <QObject>


class CDairyListModel;
class QQmlContext;

class CModelManager: public QObject
{

Q_OBJECT
public:

    CModelManager(QObject* pParent = 0);
    ~CModelManager();
public:
    static QQmlContext* g_pQmlContext;

public slots:
    void onMyselfCompleted();
    //void onDrinksC(int nIndex);

private:
     QObject* m_pObjParent;
     CDairyListModel* m_pDairyListModel;
};

#endif // CMODELMANAGER_H
