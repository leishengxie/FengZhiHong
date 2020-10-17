#ifndef CGRAPHICSNODEITEM_H
#define CGRAPHICSNODEITEM_H

#include "Component.h"
#include <QGraphicsItem>

class CGraphicsIOItem;


class CGraphicsNodeItem : public QGraphicsItem
{

public:
    explicit CGraphicsNodeItem(const CComponent & component, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void setRect(const QRectF &rect);
    QRectF rect() const;
    QRectF sceneRect() const;
    QSizeF size() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int type() const override;

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    void updateBoundingRect();
    void createIOItem();

private:
    // 组件信息
    CComponent m_component;

    // 四个位置的输入输出桩指针
    CGraphicsIOItem* m_pGraphicsIOItem[4];

};

#endif // CGRAPHICSNODEITEM_H
