#ifndef CDAIRYDATETREEVIEW_H
#define CDAIRYDATETREEVIEW_H
#include <QTreeView>
#include "Dairy.h"

class CDairyDateTreeModel;

class CDairyDateTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CDairyDateTreeView(QWidget* parent = 0);

public:
    void loadDairyList(const QList<T_Dairy> & lstDairy);

signals:
    void sortDairyByTagFinished(const QString & strTagName, const QList<T_Dairy> & lstDairy);
    void sortDairyByDateFinished(const QString & strYear, const QString & strMonth, const QList<T_Dairy> & lstDairy);
    void requreOpenDairy(const T_Dairy & dairy);

public slots:
    void sortDairyByTag(const QString & strTagName);
    void onOpenDairyClicked(const T_Dairy & dairy);
    void onSaveDairyfinished(const T_Dairy & dairySaveBefore, const T_Dairy & dairySaved);

private slots:
    void on_treeDairy_clicked(const QModelIndex & index);
    void onRequireExpand(const QModelIndex & index);

private:
    CDairyDateTreeModel* pDairyDateTreeModel;

};

#endif // CDAIRYDATETREEVIEW_H
