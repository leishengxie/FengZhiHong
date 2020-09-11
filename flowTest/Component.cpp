#include "Component.h"
#include <QApplication>
#include <QStyle>
#include <QPainter>

CComponentIO::CComponentIO()
    : eIOType(EI_InOut)
    //, nDestNodeId(-1)
    , bEnabled(true)
{
    rect.setRect(0, 0, 16, 16);
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

void CComponent::paint(QPainter *painter, const QRect &rect, const QPalette &palette) const
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

QPoint CComponent::ioPos(E_Direction eDirection) const
{
    CComponentIO io = arrIO[eDirection];
    QPoint arrPos[4];
    arrPos[ED_Top] = QPoint(width() / 2 - io.width() / 2, 0);
    arrPos[ED_Left] = QPoint(0, height() / 2 - io.height() / 2);
    arrPos[ED_Right] = QPoint(width() - io.width(), height() / 2 - io.height() / 2);
    arrPos[ED_Bottom] = QPoint(width() / 2 - io.height() / 2, height() - io.height());
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

