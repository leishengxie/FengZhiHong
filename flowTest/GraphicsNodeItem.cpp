#include "GraphicsNodeItem.h"
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
//#include <QGraphicsRectItem>
#include "GraphicsIOItem.h"

CGraphicsNodeItem::CGraphicsNodeItem(const CComponent &component, QGraphicsItem *parent)
    : m_component(component)
      , QGraphicsItem(parent)
{
    m_rect.setRect(0, 0, component.sizeHint().width(), component.sizeHint().height());
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

void CGraphicsNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    for(int i = 0; i < 4; ++i)
    {
        m_pGraphicsIOItem[i]->show();
    }
}

void CGraphicsNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    for(int i = 0; i < 4; ++i)
    {
        m_pGraphicsIOItem[i]->hide();
    }
}

void CGraphicsNodeItem::updateBoundingRect()
{
    m_rectBounding = m_rect;
}

void CGraphicsNodeItem::createIOItem()
{
    m_pGraphicsIOItem[CComponent::ED_Top] = new CGraphicsIOItem(this);
    m_pGraphicsIOItem[CComponent::ED_Top]->moveBy(m_rect.width() / 2 - m_pGraphicsIOItem[CComponent::ED_Top]->boundingRect().width() / 2, 0);
    m_pGraphicsIOItem[CComponent::ED_Top]->hide();

    m_pGraphicsIOItem[CComponent::ED_Left] = new CGraphicsIOItem(this);
    m_pGraphicsIOItem[CComponent::ED_Left]->moveBy(0, m_rect.height() / 2 - m_pGraphicsIOItem[CComponent::ED_Top]->boundingRect().height() / 2);
    m_pGraphicsIOItem[CComponent::ED_Left]->hide();

    m_pGraphicsIOItem[CComponent::ED_Right] = new CGraphicsIOItem(this);
    m_pGraphicsIOItem[CComponent::ED_Right]->moveBy(m_rect.width() - m_pGraphicsIOItem[CComponent::ED_Top]->boundingRect().width()
            , m_rect.height() / 2 - m_pGraphicsIOItem[CComponent::ED_Top]->boundingRect().height() / 2);
    m_pGraphicsIOItem[CComponent::ED_Right]->hide();

    m_pGraphicsIOItem[CComponent::ED_Bottom] = new CGraphicsIOItem(this);
    m_pGraphicsIOItem[CComponent::ED_Bottom]->moveBy(m_rect.width() / 2 - m_pGraphicsIOItem[CComponent::ED_Top]->boundingRect().height() / 2
            , m_rect.height() - m_pGraphicsIOItem[CComponent::ED_Top]->boundingRect().height());
    m_pGraphicsIOItem[CComponent::ED_Bottom]->hide();
}
