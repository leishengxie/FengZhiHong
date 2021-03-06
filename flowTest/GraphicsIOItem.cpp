#include "GraphicsIOItem.h"
#include "GlobalDef.h"
#include <QPainter>
#include <QtDebug>
#include <QCursor>
#include "GraphicsArrowItem.h"



CGraphicsIOItem::CGraphicsIOItem(const CComponentIO &componentIO, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_componentIO(componentIO)
{

    setBrush(QColor(150, 150, 150));
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable);
    // 因为相对于父类对象的Geometry是不会改变的
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    //    setData();
    //    data()
}

QRectF CGraphicsIOItem::boundingRect() const
{
    qreal halfpw = pen().style() == Qt::NoPen ? qreal(0) : pen().widthF() / 2;
    if (halfpw > 0.0)
    {
        return m_componentIO.rect.adjusted(-halfpw, -halfpw, halfpw, halfpw);
    }
    return m_componentIO.rect;
}

void CGraphicsIOItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    m_componentIO.paint(painter, pen(), brush());
}

int CGraphicsIOItem::type() const
{
    return EG_IO;
}

void CGraphicsIOItem::addArrow(CGraphicsArrowItem *pGraphicsArrowItem)
{
    if (pGraphicsArrowItem == nullptr)
    {
        return;
    }
    if (m_lstArrow.contains(pGraphicsArrowItem))
    {
        return;
    }
    m_lstArrow.append(pGraphicsArrowItem);
}

void CGraphicsIOItem::showFacade(CComponentIO::E_IOStatus eIOStatus)
{
    m_componentIO.eIOStatus = eIOStatus;
    setBrush(QBrush(QColor("#ffffff"), Qt::SolidPattern));
    switch (eIOStatus)
    {
    case CComponentIO::EI_Normal:
    {
        setPen(QPen(QPen(QColor("#808080"), 1)));
        shrink();
        break;
    }
    case CComponentIO::EI_ConnectUsable:
    {
        setPen(QPen(QPen(QColor("#3092FF"), 2)));
        shrink();
        break;
    }
    case CComponentIO::EI_ConnectUsableNear:
    {
        setPen(QPen(QPen(Qt::black, 1)));
        expand();
        break;
    }
    case CComponentIO::EI_ConnectUnusable:
    {
        setPen(QPen(QPen(Qt::red, 2)));
        shrink();
        break;
    }
    default:
        break;
    }
    show();
}

bool CGraphicsIOItem::canConnectIO(CGraphicsIOItem *other)
{
    if(this == other || !other)
    {
        return false;
    }

    if(parentItem() == other->parentItem())
    {
        return false;
    }
    return true;
}

void CGraphicsIOItem::shrink()
{
    if (m_componentIO.isShrink())
    {
        return;
    }
    prepareGeometryChange();
    m_componentIO.shrink();
}

void CGraphicsIOItem::expand()
{
    if (m_componentIO.isExpand())
    {
        return;
    }
    prepareGeometryChange();
    m_componentIO.expand();
}

void CGraphicsIOItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(true);
    //qDebug() << __FILE__ << __FUNCTION__;
    QAbstractGraphicsShapeItem::mousePressEvent(event);
}

void CGraphicsIOItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << __FILE__ << __FUNCTION__;
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

void CGraphicsIOItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     setSelected(false);
     QAbstractGraphicsShapeItem::mouseReleaseEvent(event);
}

void CGraphicsIOItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QColor(158, 179, 207));
    setCursor(QCursor(Qt::CrossCursor));
    QAbstractGraphicsShapeItem::hoverEnterEvent(event);
}

void CGraphicsIOItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QColor(150, 150, 150));
    QAbstractGraphicsShapeItem::hoverLeaveEvent(event);
}

QVariant CGraphicsIOItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged && scene())
    {
       // qDebug() << __FILE__ << __FUNCTION__ << "ItemScenePositionHasChanged";
        foreach (CGraphicsArrowItem* pArrow, m_lstArrow)
        {
            pArrow->updatePosition();
        }

    }
    return QAbstractGraphicsShapeItem::itemChange(change, value);
}
