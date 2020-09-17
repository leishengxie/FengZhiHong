#include "Component.h"
#include <QApplication>
#include <QStyle>
#include <QPainter>

#define STRETCH_FACTOR 4

CComponentIO::CComponentIO()
    : eIOType(EI_InOut)
    //, nDestNodeId(-1)
    , bEnabled(true)
    , m_eStretchStatus(ES_Shrink)
{
    rect.setRect(0, 0, 16, 16);
}

void CComponentIO::shrink()
{
    if (m_eStretchStatus == ES_Shrink)
    {
        return;
    }
    m_eStretchStatus = ES_Shrink;
    rect.adjust(STRETCH_FACTOR, STRETCH_FACTOR, -STRETCH_FACTOR, -STRETCH_FACTOR);
}

void CComponentIO::expand()
{
    if (m_eStretchStatus == ES_Expand)
    {
        return;
    }
    m_eStretchStatus = ES_Expand;
    rect.adjust(-STRETCH_FACTOR, -STRETCH_FACTOR, STRETCH_FACTOR, STRETCH_FACTOR);
}

void CComponentIO::paint(QPainter *painter, const QPen &pen, const QBrush &brush) const
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);
    painter->setBrush(brush);
    if (m_eStretchStatus == ES_Expand)
    {
        QPainterPath pathOutside;
        pathOutside.addEllipse(rect);
        painter->fillPath(pathOutside, QColor(0x1D, 0x78, 0xFE, 100));
        QPainterPath pathInside;
        pathInside.addEllipse(rect.adjusted(STRETCH_FACTOR, STRETCH_FACTOR, -STRETCH_FACTOR, -STRETCH_FACTOR));
        painter->fillPath(pathInside, QColor("#3092EF"));
    }
    else
    {
        painter->drawEllipse(rect);
    }
}

QDataStream &operator>>(QDataStream &in, CComponentIO &data)
{
    in >> data.eIOType >> data.bEnabled >> data.rect;
    return in;
}

QDataStream &operator<<(QDataStream &out, const CComponentIO &data)
{
    out << data.eIOType << data.bEnabled << data.rect;
    return out;
}



///
/// \brief CComponent::CComponent
///
CComponent::CComponent()
{
    init();
}

CComponent::CComponent(const QString &strName)
    : strName(strName)
{
    init();
}

void CComponent::init()
{
    m_icon = QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    eNodeShape = EC_RoundRect;
    rect.setRect(0, 0, 200, 40);
    for (int i = 0; i < 4; ++i)
    {
        E_Direction eDirection = E_Direction(i);
        if(arrIO[i].isEnabled())
        {
            arrIO[i].setDirection(eDirection);
        }
    }
}

QColor CComponent::statusColor() const
{
    switch (eStatus) {
    case EC_Failed:
        return Qt::red;
    default:
        break;
    }
    return Qt::white;
}

void CComponent::paint(QPainter *painter, const QRectF &rect, const QPalette &palette) const
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::gray);

    if (eNodeShape == EC_Rectangle)
    {
        painter->drawRect(rect);
    }
    else if (eNodeShape == EC_RoundRect)
    {
        painter->drawRoundRect(rect, rect.height() / 2, rect.height() / 2);
    }
    else if (eNodeShape == EC_Rhombus)
    {
        QPolygon polygon;
        polygon << QPoint(0, rect.height() / 2)
                << QPoint(rect.width() / 2, 0)
                << QPoint(rect.width(), rect.height() / 2)
                << QPoint(rect.width() / 2, rect.height());
        painter->drawPolygon(polygon);
    }
    painter->drawText(rect, strName);

    painter->restore();
}

QPixmap CComponent::renderPixmap()
{
    QPixmap pixmap(sizeHint());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    paint(&painter, pixmap.rect(), QPalette());
    return pixmap;
}

QPointF CComponent::ioPos(E_Direction eDirection) const
{
    CComponentIO io = arrIO[eDirection];
    QPointF arrPos[4];
    arrPos[ED_Top] = QPointF(width() / 2 - io.width() / 2, 0);
    arrPos[ED_Left] = QPointF(0, height() / 2 - io.height() / 2);
    arrPos[ED_Right] = QPointF(width() - io.width(), height() / 2 - io.height() / 2);
    arrPos[ED_Bottom] = QPointF(width() / 2 - io.height() / 2, height() - io.height());
    return arrPos[eDirection];
}


QDataStream &operator>>(QDataStream &in, CComponent &data)
{
    in >> data.strName >> data.m_icon >> data.rect >> data.eNodeShape >> data.eComponentType
            >> data.eComponentClass >> data.eStatus;
    for (int i = 0; i < 4; ++i)
    {
        in >> data.arrIO[i];
    }
    return in;
}

QDataStream &operator<<(QDataStream &out, const CComponent &data)
{
    out << data.strName << data.m_icon << data.rect << data.eNodeShape << data.eComponentType
        << data.eComponentClass << data.eStatus;
    for (int i = 0; i < 4; ++i)
    {
        out << data.arrIO[i];
    }
    return out;
}

