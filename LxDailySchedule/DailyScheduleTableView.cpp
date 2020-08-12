#include "DailyScheduleTableView.h"
#include "DailyScheduleDelegate.h"
#include "DailyScheduleModel.h"
#include <QHeaderView>
#include <QMenu>


CDailyScheduleTableView::CDailyScheduleTableView(QWidget *parent)
    : QTableView(parent)
{
    m_pDailyScheduleModel = new CDailyScheduleModel(this);
    CDailyScheduleDelegate* pDailyScheduleDelegate = new CDailyScheduleDelegate;
    setModel(m_pDailyScheduleModel);
    setItemDelegate(pDailyScheduleDelegate);
    //setTextElideMode(Qt::ElideLeft);
    // 根据内容自动调整所有行的行高
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    resizeRowsToContents();
    //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//对第0列单独设置固定宽度
    horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);//对第0列单独设置固定宽度
    setColumnWidth(0, 150);//设置固定宽度
    setColumnWidth(2, 100);//设置固定宽度

    //根据内容自动调整所有列的列宽
    //resizeColumnsToContents();
    //verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //resizeColumnToContents(1);

    m_menu = new QMenu(this);
    QAction* actOrder = new QAction("按起始时间排序", m_menu);
    connect(actOrder, SIGNAL(triggered()), this, SLOT(slotOrderByTime()));
    QAction* actFix = new QAction("按起始时间去除时间交错", m_menu);
    connect(actFix, SIGNAL(triggered()), this, SLOT(slotFixCrossItem()));
    QAction* actDelete = new QAction("删除时间项", m_menu);
    connect(actDelete, SIGNAL(triggered()), this, SLOT(slot_delete()));

    m_menu->addAction(actOrder);
    m_menu->addAction(actFix);
    m_menu->addAction(actDelete);
    //m_menu->addAction(new QAction("", m_menu));

    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection))
            , this, SLOT(slot_selectionChanged(QItemSelection,QItemSelection)));

}

void CDailyScheduleTableView::addItem()
{
    m_pDailyScheduleModel->addDefaultScheduleItem();
}

QList<T_ScheduleItem> CDailyScheduleTableView::scheduleItemList()
{
    return m_pDailyScheduleModel->scheduleItemList();
}

void CDailyScheduleTableView::clear()
{
    m_pDailyScheduleModel->clear();
}

void CDailyScheduleTableView::slotLoadDailySchedule(const T_DailySchedule & tDailySchedule)
{
    m_pDailyScheduleModel->setDailySchedule( tDailySchedule.lstScheduleItem);
}

void CDailyScheduleTableView::contextMenuEvent(QContextMenuEvent *event)
{
    //m_menu->move();
    m_menu->popup(cursor().pos());
}


void CDailyScheduleTableView::slotOrderByTime()
{
    m_pDailyScheduleModel->orderByTime();
}

void CDailyScheduleTableView::slotFixCrossItem()
{
    m_pDailyScheduleModel->fixCrossItem();
}

void CDailyScheduleTableView::slot_delete()
{
    if (selectionModel()->selectedIndexes().isEmpty())
    {
        return;
    }
    QModelIndex index = selectionModel()->selectedIndexes().at(0);
    m_pDailyScheduleModel->removeItem(index);
}

void CDailyScheduleTableView::slot_selectionChanged(const QItemSelection &selected
                                                    , const QItemSelection &deselected)
{
     //T_ScheduleItem tScheduleItem = qvariant_cast<T_ScheduleItem>(currentIndex().data());
    emit sigSelectedChanged(selectionModel()->selectedIndexes().count() > 0);
}
