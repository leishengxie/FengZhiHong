#include "ComponentTreeView.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QtDebug>
#include "ComponentMimeData.h"
#include "ComponentTreeModel.h"


///
/// \brief CComponentTreeView::CComponentTreeView
/// \param parent
///
CComponentTreeView::CComponentTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setAcceptDrops(true);
    m_pComponentTreeModel = new CComponentTreeModel(this);
    setModel(m_pComponentTreeModel);
}

void CComponentTreeView::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        m_ptPress = event->pos();
    }
}

void CComponentTreeView::mouseMoveEvent(QMouseEvent *event)
{
    QTreeView::mouseMoveEvent(event);
    QPoint pt = event->pos();
    if (event->buttons() & Qt::LeftButton) // 这里不能用if (event->button() == Qt::LeftButton)
    {
        int distance = (pt - m_ptPress).manhattanLength();
        if (distance >= QApplication::startDragDistance())
        {
            performDrag(pt);
        }
    }
}

void CComponentTreeView::performDrag(const QPoint &pt)
{
    QModelIndex index = indexAt(m_ptPress);
    if(!index.isValid())
    {
        return;
    }

    if (m_pComponentTreeModel->isContainer(index))
    {
        return;
    }

    CComponent component = m_pComponentTreeModel->component(index);

    CComponentMimeData* mimeData = new CComponentMimeData;
    mimeData->setComponent(component);

    QPoint ptHotspot(cursor().hotSpot().x() + component.size().width() / 2
                     , cursor().hotSpot().y() + component.size().height() / 2);

    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(component.renderPixmap());
    drag->setHotSpot(ptHotspot);
    drag->exec(Qt::MoveAction);
}


