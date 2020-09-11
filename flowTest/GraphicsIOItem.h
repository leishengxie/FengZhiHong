#ifndef CGRAPHICSIOITEM_H
#define CGRAPHICSIOITEM_H

#include "Component.h"
#include <QGraphicsItem>
class CGraphicsArrowItem;

///
/// \brief The CGraphicsIOItem class
/// 输入输出桩
///
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

    E_Direction direction() const
    {
        return m_eDirection;
    }

    void setDirection(E_Direction eDirection)
    {
        m_eDirection = eDirection;
    }

    int type() const override;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QRectF m_rect;

    E_Direction m_eDirection;

    CComponentIO m_tComponentIO;

    // 多对多 箭头连线列表
    QList<CGraphicsArrowItem*> m_lstArrow;
};

#endif // CGRAPHICSIOITEM_H
