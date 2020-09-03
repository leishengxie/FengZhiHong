#include "GraphicsNodeItem.h"
#include <QPainter>
#include <QWidget>
//#include <QGraphicsRectItem>

CGraphicsNodeItem::CGraphicsNodeItem(const CComponent &component, QGraphicsItem *parent)
    : CNode(component)
      , QGraphicsItem(parent)
{
    m_rect.setRect(0, 0, component.sizeHint().width(), component.sizeHint().height());
    updateBoundingRect();
}



QRectF CGraphicsNodeItem::boundingRect() const
{
    return m_rectBounding;
}

void CGraphicsNodeItem::setRect(const QRectF &rect)
{
    if (m_rect == rect)
    {
        return;
    }
    prepareGeometryChange();
    m_rect = rect;
    updateBoundingRect();
    update();
}

QRectF CGraphicsNodeItem::rect() const
{
    return m_rect;
}

void CGraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    m_component.paint(painter, m_rect.toRect(), widget->palette());

}

void CGraphicsNodeItem::updateBoundingRect()
{
    m_rectBounding = m_rect;
}

void CGraphicsNodeItem::createIOItem()
{

}
