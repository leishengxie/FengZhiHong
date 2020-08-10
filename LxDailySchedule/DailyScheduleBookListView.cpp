#include "DailyScheduleBookListView.h"
#include <QPainter>
#include <QMessageBox>
#include <QMenu>
#include "DailyScheduleSqlOperate.h"


CDailyScheduleBookListView::CDailyScheduleBookListView(QWidget *parent)
    : QListView(parent)
{
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    //setFlow(QListView::LeftToRight);
    //setWrapping(false);
    //setSpacing(5);

    m_menu = new QMenu(this);
    QAction* actEdit = new QAction("编辑", m_menu);
    connect(actEdit, SIGNAL(triggered()), this, SLOT(slot_edit()));
    m_menu->addAction(actEdit);
    QAction* actDelete = new QAction("删除", m_menu);
    connect(actDelete, SIGNAL(triggered()), this, SLOT(slot_delete()));
    m_menu->addAction(actDelete);


    m_pDailyScheduleBookModel = new CDailyScheduleBookModel(this);
    setModel(m_pDailyScheduleBookModel);
    //QListView
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onListViewClicked(QModelIndex)));

    m_pDailyScheduleBookModel->setDailyScheduleList(CDailyScheduleSqlOperate::getInstance()->getDailyScheduleList());
}

// 如果有后台应该向后台请求保存数据
void CDailyScheduleBookListView::slotReqSaveDailySchedule(const T_DailySchedule &tDailySchedule)
{
    saveDailySchedule(tDailySchedule);
}

void CDailyScheduleBookListView::saveDailySchedule(const T_DailySchedule &tDailySchedule)
{
    QString strErr;
    bool ok = CDailyScheduleSqlOperate::getInstance()->saveDailySchedule(tDailySchedule, strErr);
    if (!ok)
    {
        QMessageBox::warning(this, "error", strErr);
    }
    // 刷新列表
    m_pDailyScheduleBookModel->setDailyScheduleList(CDailyScheduleSqlOperate::getInstance()->getDailyScheduleList());
}

void CDailyScheduleBookListView::contextMenuEvent(QContextMenuEvent *event)
{
    m_menu->popup(cursor().pos());
}

void CDailyScheduleBookListView::paintEvent(QPaintEvent *e)
{
    int row = m_pDailyScheduleBookModel->rowCount();
    if (row > 0)
    {
        return QListView::paintEvent(e);
    }

    QPainter painter(viewport());
    QTextOption textOption(Qt::AlignLeft | Qt::AlignVCenter);
    textOption.setWrapMode(QTextOption::WordWrap);//设置换行,在单独的QWidget能实现,这里没有生效，估计是不让修改
    painter.save();
    painter.setPen(QColor(0, 160, 230));
    painter.drawText(rect(), "请创建日作息时间表", textOption);
    painter.restore();
}

void CDailyScheduleBookListView::onListViewClicked(const QModelIndex &index)
{
    emit sigDailyScheduleClicked(m_pDailyScheduleBookModel->dailyScheduleData(index));
}

void CDailyScheduleBookListView::slot_edit()
{
    emit sigDailyScheduleEdit(m_pDailyScheduleBookModel->dailyScheduleData(currentIndex()));
}

void CDailyScheduleBookListView::slot_delete()
{

}

