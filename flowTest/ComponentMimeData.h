#ifndef CNODEMIMEDATA_H
#define CNODEMIMEDATA_H

#include "Component.h"
#include <QMimeData>

class CComponentMimeData : public QMimeData
{
    Q_OBJECT
public:
    //enum {ComponentType = QMetaType::User + 1}; // Qt定义的私有类在cpp中，不可用

    CComponent component() const;
    void setComponent(const CComponent &component);
    bool hasComponent() const;

//protected:
//    virtual QVariant retrieveData(const QString &mimetype,
//                                      QVariant::Type preferredType) const;

//private:
//    CComponent m_component;

};

#endif // CNODEMIMEDATA_H
