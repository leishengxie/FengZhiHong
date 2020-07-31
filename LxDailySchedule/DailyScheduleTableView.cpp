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

    m_menu->addAction(actOrder);
    m_menu->addAction(actFix);
    //m_menu->addAction(new QAction("", m_menu));

}

void CDailyScheduleTableView::addItem()
{
    m_pDailyScheduleModel->addDefaultScheduleItem();
}

void CDailyScheduleTableView::slotLoadBook(const T_DailyScheduleBook &book)
{
    m_pDailyScheduleModel->setDailyScheduleList(book.lstScheduleItem);
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
