#ifndef CDAIRYDATETREEMODEL_H
#define CDAIRYDATETREEMODEL_H

#include <QAbstractItemModel>
#include <QSet>
#include "Dairy.h"

// 节点类型
enum E_DairyDateNodeType
{
    ED_Year,
    ED_Month,
    ED_Day
};

struct T_DairyDateItem
{
    E_DairyDateNodeType eDairyDateType;
    QString strYear;
    QString strMonth;
    QString strDay;
    QString strTitle;
    QSet<T_DairyDateItem*> m_lstChildItems;
    T_DairyDateItem *m_parentItem;
    int nUniqueness;

    QString text()
    {
        QString strText;
        switch (eDairyDateType)
        {
        case ED_Year:
            strText = strYear + "年";
            break;
        case ED_Month:
            strText = strMonth + "月";
            break;
        case ED_Day:
            strText = strDay + "日 - " + strTitle;
            break;
        default:
            break;
        }
        return strText;
    }

    int uniqueness()
    {
        int nYear = strYear.toInt() * 365;

    }

    int totalDay()
    {
        int totalDay = 0;
        switch (eDairyDateType)
        {
        case ED_Year:
            totalDay += 365 * strYear.toInt();
            break;
        case ED_Month:
            strText = strMonth + "月";
            break;
        case ED_Day:
            strText = strDay + "日 - " + strTitle;
            break;
        default:
            break;
        }

    }

    bool operator<(const T_DairyDateItem & right)const
    {
        // 必须同一类型才具可比性，才能插入
        if (eDairyDateType != right.eDairyDateType)
        {
            return false;
        }


    }
};

class CDairyDateTreeModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    CDairyDateTreeModel();

    void CreateDataTree(QList<CDairy> m_lstDairy);

private:
    T_DairyDateItem* m_pDairyDateItemRoot;
};

#endif // CDAIRYDATETREEMODEL_H
