#include "DairyDateTreeView.h"
#include <QtDebug>
#include "DairyDateTreeModel.h"
#include "DairyDateDelegate.h"

CDairyDateTreeView::CDairyDateTreeView(QWidget* parent)
    : QTreeView(parent)
{
    // 初始化pDairyDateTreeModel
    pDairyDateTreeModel = new CDairyDateTreeModel(this);
    CDairyDateDelegate* pDairyDateDelegate = new CDairyDateDelegate;
    setModel(pDairyDateTreeModel);
    setItemDelegate(pDairyDateDelegate);
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(on_treeDairy_clicked(QModelIndex)));

    connect(pDairyDateTreeModel, SIGNAL(loadTodayDairyFinished(CDairy)), this, SIGNAL(requreOpenDairy(CDairy)));
    connect(pDairyDateTreeModel, SIGNAL(requireExpand(QModelIndex)), this, SLOT(onRequireExpand(QModelIndex)));

    connect(pDairyDateTreeModel, SIGNAL(sortDairyByTagFinished(QString, QList<CDairy>)),
            this, SIGNAL(sortDairyByTagFinished(QString, QList<CDairy>)));
}

void CDairyDateTreeView::loadDairyList(const QList<CDairy> & lstDairy)
{
    pDairyDateTreeModel->loadDairyList(lstDairy);
}

void CDairyDateTreeView::sortDairyByTag(const QString & strTagName)
{
    pDairyDateTreeModel->sortDairyByTag(strTagName);
}

void CDairyDateTreeView::onOpenDairyClicked(const CDairy & dairy)
{
    pDairyDateTreeModel->expandDairy(dairy.getDid());
}

void CDairyDateTreeView::onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved)
{
    pDairyDateTreeModel->dairyModify(dairySaveBefore, dairySaved);
}

void CDairyDateTreeView::on_treeDairy_clicked(const QModelIndex & index)
{
    qDebug() << "tree click " << "row=" << index.row() << " column=" << index.column();
    T_DairyDateItem* tDairyTagItem = qvariant_cast<T_DairyDateItem*>(index.data());
    QList<CDairy> lstDairy = pDairyDateTreeModel->dairyList();
    QList<CDairy> lstDairySortByDate;
    switch (tDairyTagItem->eDairyDateNodeType)
    {
        case ED_Year:
            {
                //ui->stackedWidget->setCurrentIndex(1);
                //ui->page_dairy_statistics->showStatisticsByDate(tDairyTagItem->strYear, "");
                foreach (CDairy dairy, lstDairy)
                {
                    if (dairy.getDateTime().left(4) == tDairyTagItem->strYear)
                    {
                        lstDairySortByDate.append(dairy);
                    }
                }
                emit sortDairyByDateFinished(tDairyTagItem->strYear, "", lstDairySortByDate);
                break;
            }
        case ED_Month:
            {

//                ui->stackedWidget->setCurrentIndex(1);
//                ui->page_dairy_statistics->showStatisticsByDate(tDairyTagItem->strYear, tDairyTagItem->strMonth);
                foreach (CDairy dairy, lstDairy)
                {
                    if (dairy.getDateTime().left(4) == tDairyTagItem->strYear && dairy.getDateTime().mid(5, 2) == tDairyTagItem->strMonth)
                    {
                        lstDairySortByDate.append(dairy);
                    }
                }
                emit sortDairyByDateFinished(tDairyTagItem->strYear, tDairyTagItem->strMonth, lstDairySortByDate);
                break;

            }
        case ED_Day:
            {
                //ui->stackedWidget->setCurrentIndex(0);
//                CDairy dairy;
//                dairy.setDid(tDairyTagItem->did);
//                ui->page_dairy->slot_displayDairy(dairy);
                foreach (CDairy dairy, lstDairy)
                {
                    if (dairy.getDid() == tDairyTagItem->did)
                    {
                        emit requreOpenDairy(dairy);
                        break;
                    }
                }
                break;
            }
        default:
            break;
    }


}

void CDairyDateTreeView::onRequireExpand(const QModelIndex & index)
{
    expand(index);
    QList<QModelIndex> lstIndex;
    QModelIndex indexParent = index.parent();
    while (indexParent.isValid())
    {
        lstIndex.push_front(indexParent);
        indexParent = indexParent.parent();
    }
    for(QModelIndex index : lstIndex)
    {
        expand(index);
    }
    on_treeDairy_clicked(index);
}
