#include "ComponentMimeData.h"

static inline QString applicationComponentLiteral() { return QStringLiteral("application/component"); }
static inline QString applicationHotspotLiteral() { return QStringLiteral("application/hotspot"); }


CComponent CComponentMimeData::component() const
{
    CComponent component;
    QByteArray byteArrayTemp = data(applicationComponentLiteral());
    QDataStream in(&byteArrayTemp, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    in >> component;
    return component;
}

void CComponentMimeData::setComponent(const CComponent &component)
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << component;
    setData(applicationComponentLiteral(), byteArray);
}

bool CComponentMimeData::hasComponent() const
{
    return hasFormat(applicationComponentLiteral());
}

QPoint CComponentMimeData::hotspot() const
{
    QPoint pt;
    QByteArray byteArrayTemp = data(applicationHotspotLiteral());
    QDataStream in(&byteArrayTemp, QIODevice::ReadOnly);
    in >> pt;
    return pt;
}

void CComponentMimeData::setHotspot(const QPoint &pt)
{

    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
    dataStream << pt;
    setData(applicationHotspotLiteral(), byteArray);
}

bool CComponentMimeData::hasHotspot() const
{
    return hasFormat(applicationHotspotLiteral());
}

//QVariant CNodeMimeData::retrieveData(const QString &mimetype, QVariant::Type preferredType) const
//{

//}
