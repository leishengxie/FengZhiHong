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

private:
    void updateBoundingRect();
    void createIOItem();

private:
    // 注意:此rect的x, y 并非代表在父对象的x,y 坐标
    QRectF m_rect;

    mutable QRectF m_rectBounding;

    CComponent m_component;

    // 四个位置的输入输出桩
    CGraphicsIOItem* m_pGraphicsIOItem[4];



};

#endif // CGRAPHICSNODEITEM_H
