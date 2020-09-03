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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



signals:

private:
    void updateBoundingRect();
    void createIOItem();

private:
    // 注意:此rect的x, y 并非代表在父对象的x,y 坐标
    QRectF m_rect;

    mutable QRectF m_rectBounding;

    CGraphicsIOItem* m_pGraphicsIOItem[4];

    CComponent m_component;

};

#endif // CGRAPHICSNODEITEM_H
