#ifndef CGRAPHICSNODEITEM_H
#define CGRAPHICSNODEITEM_H

#include "Node.h"
#include <QGraphicsItem>

class CGraphicsNodeItem : public QGraphicsItem, public CNode
{

public:
    explicit CGraphicsNodeItem(const CComponent & component, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    QRectF rectf() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



signals:

private:


};

#endif // CGRAPHICSNODEITEM_H
