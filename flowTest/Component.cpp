#include "Component.h"
#include <QApplication>
#include <QStyle>
#include <QPainter>

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


QDataStream &operator>>(QDataStream &in, CComponent &data)
{
    in >> data.strName >> data.m_icon >> data.eNodeShape >> data.eComponentType
            >> data.eComponentClass >> data.eNodeStatus;
    return in;
}

QDataStream &operator<<(QDataStream &out, const CComponent &data)
{
    out << data.strName << data.m_icon << data.eNodeShape << data.eComponentType
        << data.eComponentClass << data.eNodeStatus;
    return out;
}
