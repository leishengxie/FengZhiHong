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

    connect(pDairyDateTreeModel, SIGNAL(loadTodayDairyFinished(T_Dairy)), this, SIGNAL(requreOpenDairy(T_Dairy)));
    connect(pDairyDateTreeModel, SIGNAL(requireExpand(QModelIndex)), this, SLOT(onRequireExpand(QModelIndex)));

    connect(pDairyDateTreeModel, SIGNAL(sortDairyByTagFinished(QString, QList<T_Dairy>)),
            this, SIGNAL(sortDairyByTagFinished(QString, QList<T_Dairy>)));
}

void CDairyDateTreeView::loadDairyList(const QList<T_Dairy> & lstDairy)
{
    pDairyDateTreeModel->loadDairyList(lstDairy);
}

void CDairyDateTreeView::sortDairyByTag(const QString & strTagName)
{
    pDairyDateTreeModel->sortDairyByTag(strTagName);
}

void CDairyDateTreeView::onOpenDairyClicked(const T_Dairy & dairy)
{
    pDairyDateTreeModel->expandDairy(dairy.did);
}

void CDairyDateTreeView::onSaveDairyfinished(const T_Dairy & dairySaveBefore, const T_Dairy & dairySaved)
{
    pDairyDateTreeModel->dairyModify(dairySaveBefore, dairySaved);
}

void CDairyDateTreeView::on_treeDairy_clicked(const QModelIndex & index)
{
    qDebug() << "tree click " << "row=" << index.row() << " column=" << index.column();
    T_DairyDateItem* tDairyTagItem = qvariant_cast<T_DairyDateItem*>(index.data());
    QList<T_Dairy> lstDairy = pDairyDateTreeModel->dairyList();
    QList<T_Dairy> lstDairySortByDate;
    switch (tDairyTagItem->eDairyDateNodeType)
    {
        case ED_Year:
            {
                //ui->stackedWidget->setCurrentIndex(1);
                //ui->page_dairy_statistics->showStatisticsByDate(tDairyTagItem->strYear, "");
                foreach (T_Dairy dairy, lstDairy)
                {
                    if (dairy.strDateTime.left(4) == tDairyTagItem->strYear)
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
                foreach (T_Dairy dairy, lstDairy)
                {
                    if (dairy.strDateTime.left(4) == tDairyTagItem->strYear && dairy.strDateTime.mid(5, 2) == tDairyTagItem->strMonth)
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
                foreach (T_Dairy dairy, lstDairy)
                {
                    if (dairy.did == tDairyTagItem->did)
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
