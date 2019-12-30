#include "DairyTagListView.h"

#include "DairyTagListModel.h"
#include "DairyTagDelegate.h"

CDairyTagListView::CDairyTagListView(QWidget *parent)
    : QListView(parent)
{
    // 初始化listViewTag
    pDairyTagListModel = new CDairyTagListModel(this);
    CDairyTagDelegate* pDairyTagDelegate = new CDairyTagDelegate;
    setModel(pDairyTagListModel);
    setItemDelegate(pDairyTagDelegate);
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(on_listViewTag_clicked(QModelIndex)));
}

void CDairyTagListView::loadDiaryList(const QList<CDairy> &lstDairy)
{
    pDairyTagListModel->loadDiaryList(lstDairy);
}

void CDairyTagListView::on_listViewTag_clicked(const QModelIndex &index)
{
    T_DairyTagItem tDairyTagItem = qvariant_cast<T_DairyTagItem>(index.data());

    emit dairyTagListClicked(tDairyTagItem.strTagName);

}
