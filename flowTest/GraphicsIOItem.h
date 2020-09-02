#ifndef CGRAPHICSIOITEM_H
#define CGRAPHICSIOITEM_H

#include <QGraphicsItem>

class CGraphicsIOItem : public QAbstractGraphicsShapeItem
{

public:
    explicit CGraphicsIOItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRect(const QRectF & rect)
    {
        m_rect = rect;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QRectF m_rect;

};

#endif // CGRAPHICSIOITEM_H
