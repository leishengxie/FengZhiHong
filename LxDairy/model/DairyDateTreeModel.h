#ifndef CDAIRYDATETREEMODEL_H
#define CDAIRYDATETREEMODEL_H

#include <QAbstractItemModel>

enum E_DairyDateType
{
    ED_Year,
    ED_Month,
    ED_Day
};

struct T_DairyDateItem
{
    E_DairyDateType eDairyDateType;
};

class CDairyDateTreeModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    CDairyDateTreeModel();
};

#endif // CDAIRYDATETREEMODEL_H
