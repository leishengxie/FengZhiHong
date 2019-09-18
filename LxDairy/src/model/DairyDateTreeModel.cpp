#include "DairyDateTreeModel.h"

CDairyDateTreeModel::CDairyDateTreeModel()
    : m_pDairyDateItemRoot(NULL)
{

}

void CDairyDateTreeModel::CreateDataTree(QList<CDairy> m_lstDairy)
{
    foreach (CDairy dairy, m_lstDairy)
    {
        //QMultiMap
        //"2010-07-02 17:35:00";
        QString strDateTime = dairy.getDateTime();
        QString strYear = strDateTime.mid(0, 4);
        QString strMonth = strDateTime.mid(5, 2);
        QString strDay = strDateTime.mid(8, 2);

    }
}
