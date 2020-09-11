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
    m_rect.setRect(0, 0, component.sizeHint().width(), component.sizeHint().height());
    for (int i = 0; i < 4; ++i)
    {
        m_pGraphicsIOItem[i] = nullptr;
    }
    updateBoundingRect();
    createIOItem();
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}



QRectF CGraphicsNodeItem::boundingRect() const
{
    return m_rectBounding;
}

void CGraphicsNodeItem::setRect(const QRectF &rect)
{
    if (m_rect == rect)
    {
        return;
    }
    prepareGeometryChange();
    m_rect = rect;
    updateBoundingRect();
    update();
}

QRectF CGraphicsNodeItem::rect() const
{
    return m_rect;
}

QSizeF CGraphicsNodeItem::size() const
{
    return m_rect.size();
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

    m_component.paint(painter, m_rect.toRect(), widget->palette());

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

void CGraphicsNodeItem::updateBoundingRect()
{
    m_rectBounding = m_rect;
}

void CGraphicsNodeItem::createIOItem()
{
    for (int i = 0; i < 4; ++i)
    {
        E_Direction eDirection = E_Direction(i);
        if(m_component.io(eDirection).isEnabled())
        {
            m_pGraphicsIOItem[i] = new CGraphicsIOItem(this);
            m_pGraphicsIOItem[i]->setPos(m_component.ioPos(eDirection));
            m_pGraphicsIOItem[i]->setDirection(eDirection);
            m_pGraphicsIOItem[i]->hide();
        }
    }

}
