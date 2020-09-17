#include "GraphicsNodeItem.h"
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QtDebug>
//#include <QGraphicsRectItem>
#include "GraphicsIOItem.h"
#include "GraphicsArrowItem.h"
#include "GlobalDef.h"

CGraphicsNodeItem::CGraphicsNodeItem(const CComponent &component, QGraphicsItem *parent)
    : m_component(component)
      , QGraphicsItem(parent)
{

    for (int i = 0; i < 4; ++i)
    {
        m_pGraphicsIOItem[i] = nullptr;
    }
    updateBoundingRect();
    createIOItem();
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

}



QRectF CGraphicsNodeItem::boundingRect() const
{
    return m_component.rect;
}

void CGraphicsNodeItem::setRect(const QRectF &rect)
{
    if (m_component.rect == rect)
    {
        return;
    }
    prepareGeometryChange();
    m_component.rect = rect;
    updateBoundingRect();
    update();
}

QRectF CGraphicsNodeItem::rect() const
{
    return m_component.rect;
}

QSizeF CGraphicsNodeItem::size() const
{
    return m_component.rect.size();
}

void CGraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QColor colorBg = Qt::white;
    if(m_component.eStatus == CComponent::EC_Failed)
    {
        colorBg = Qt::red;
    }
    else if(option->state & QStyle::State_Selected)
    {
        colorBg = QColor(220, 228, 244);
    }
    painter->setBrush(colorBg);

    m_component.paint(painter, m_component.rect, widget->palette());

}

int CGraphicsNodeItem::type() const
{
    return EG_Node;
}

void CGraphicsNodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << __FILE__ << __FUNCTION__;
    QGraphicsItem::mousePressEvent(event);
}

void CGraphicsNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    for(int i = 0; i < 4; ++i)
    {
        if (m_pGraphicsIOItem[i] == nullptr)
        {
            continue;
        }
        m_pGraphicsIOItem[i]->show();
    }
}

void CGraphicsNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    for(int i = 0; i < 4; ++i)
    {
        if (m_pGraphicsIOItem[i] == nullptr)
        {
            continue;
        }
        m_pGraphicsIOItem[i]->hide();
    }
}

//QVariant CGraphicsNodeItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//    if (change == ItemPositionHasChanged && scene())
//    {
////        for (int i = 0; i < 4; ++i)
////        {
////                m_pGraphicsIOItem[i] = new CGraphicsIOItem(this);
////        }
//        qDebug() << __FILE__ << __FUNCTION__ << "ItemPositionHasChanged";

//    }
//    return QGraphicsItem::itemChange(change, value);
//}

void CGraphicsNodeItem::updateBoundingRect()
{

}

void CGraphicsNodeItem::createIOItem()
{
    for (int i = 0; i < 4; ++i)
    {
        E_Direction eDirection = E_Direction(i);
        if(m_component.io(eDirection).isEnabled())
        {
            m_pGraphicsIOItem[i] = new CGraphicsIOItem(m_component.arrIO[i], this);
            m_pGraphicsIOItem[i]->setPos(m_component.ioPos(eDirection));
            m_pGraphicsIOItem[i]->hide();
        }
    }

}
