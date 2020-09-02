#include "GraphicsIOItem.h"
#include <QPainter>

CGraphicsIOItem::CGraphicsIOItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
{
    m_rect.setRect(0, 0, 20, 20);
    setBrush(QColor(150, 150, 150));
    setAcceptHoverEvents(true);
}

QRectF CGraphicsIOItem::boundingRect() const
{
    qreal halfpw = pen().style() == Qt::NoPen ? qreal(0) : pen().widthF() / 2;
    if (halfpw > 0.0)
    {
        return m_rect.adjusted(-halfpw, -halfpw, halfpw, halfpw);
    }
    return m_rect;
}

void CGraphicsIOItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush());
    painter->drawEllipse(m_rect);
}

void CGraphicsIOItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void CGraphicsIOItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void CGraphicsIOItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void CGraphicsIOItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QColor(158, 179, 207));
    QAbstractGraphicsShapeItem::hoverEnterEvent(event);
}

void CGraphicsIOItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QColor(150, 150, 150));
    QAbstractGraphicsShapeItem::hoverLeaveEvent(event);
}
