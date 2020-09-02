#include "GraphicsNodeItem.h"
#include <QPainter>
#include <QWidget>
//#include <QGraphicsRectItem>

CGraphicsNodeItem::CGraphicsNodeItem(const CComponent &component, QGraphicsItem *parent)
    : CNode(component)
      , QGraphicsItem(parent)
{

}

QRectF CGraphicsNodeItem::boundingRect() const
{
    return QRectF(pos(), m_component.size());
}

QRectF CGraphicsNodeItem::rectf() const
{
    return QRectF(pos(), m_component.size());
}

void CGraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QRectF rect = rectf();
    m_component.paint(painter, rect.toRect(), widget->palette());

}
