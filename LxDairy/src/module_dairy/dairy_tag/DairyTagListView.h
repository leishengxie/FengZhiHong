#ifndef CDAIRYTAGLISTVIEW_H
#define CDAIRYTAGLISTVIEW_H
#include <QListView>
#include "Dairy.h"

class CDairyTagListModel;


class CDairyTagListView : public QListView
{
    Q_OBJECT
public:
    CDairyTagListView(QWidget* parent);

    void loadDiaryList(const QList<CDairy> &lstDairy);

signals:
    void dairyTagListClicked(const QString & strTag);

private slots:
    void on_listViewTag_clicked(const QModelIndex &index);

private:
    // model管理
    CDairyTagListModel* pDairyTagListModel;
};

#endif // CDAIRYTAGLISTVIEW_H
