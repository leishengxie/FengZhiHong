#include "ComponentMimeData.h"

static inline QString applicationComponentLiteral() { return QStringLiteral("application/component"); }



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

//QVariant CNodeMimeData::retrieveData(const QString &mimetype, QVariant::Type preferredType) const
//{

//}
