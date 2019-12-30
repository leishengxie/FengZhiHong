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
    void loadDairyList(const QList<CDairy> & lstDairy);

signals:
    void sortDairyByTagFinished(const QString & strTagName, const QList<CDairy> & lstDairy);
    void sortDairyByDateFinished(const QString & strYear, const QString & strMonth, const QList<CDairy> & lstDairy);
    void requreOpenDairy(const CDairy & dairy);

public slots:
    void sortDairyByTag(const QString & strTagName);
    void onOpenDairyClicked(const CDairy & dairy);
    void onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved);

private slots:
    void on_treeDairy_clicked(const QModelIndex & index);
    void onRequireExpand(const QModelIndex & index);

private:
    CDairyDateTreeModel* pDairyDateTreeModel;

};

#endif // CDAIRYDATETREEVIEW_H
