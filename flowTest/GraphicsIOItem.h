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
    enum E_StretchStatus
    {
        ES_Expand,
        ES_Shrink
    };

    explicit CGraphicsIOItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRect(const QRectF & rect)
    {
        m_rect = rect;

    }

    QPointF sceneCenterPos()
    {
        return scenePos() + m_rect.center();
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

    void addArrow(CGraphicsArrowItem* pGraphicsArrowItem);

    void showFacade(CComponentIO::E_IOStatus eIOStatus);

    bool canConnectIO(CGraphicsIOItem* other);
    void shrink(); // int nDecrease = 4

    void expand(); // int nIncrement = 4

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QRectF m_rect;

    E_Direction m_eDirection;

    E_StretchStatus m_eStretchStatus;

    CComponentIO m_componentIO;

    // 多对多 箭头连线列表
    QList<CGraphicsArrowItem*> m_lstArrow;
};

#endif // CGRAPHICSIOITEM_H
