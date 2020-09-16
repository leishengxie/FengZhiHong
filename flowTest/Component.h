#ifndef CCOMPONENT_H
#define CCOMPONENT_H
#include <QObject>
#include <QIcon>
#include "GlobalDef.h"

// 组件io
class CComponentIO
{
public:
    enum E_IOType
    {
        EI_In,
        EI_Out,
        EI_InOut
    };

    enum E_IOShape
    {
        EI_Ellipse
    };

    enum E_IOStatus
    {
        EI_Normal,
        EI_ConnectUsable,
        EI_ConnectUsableNear,
        EI_ConnectUnusable
    };

    CComponentIO();

    int height()
    {
        return rect.height();
    }

    int width()
    {
        return rect.width();
    }

    bool isEnabled() const
    {
        return bEnabled;
    }

    friend QDataStream & operator>>(QDataStream & in, CComponentIO & data);
    friend QDataStream & operator<<(QDataStream & out, const CComponentIO & data);


    E_IOType eIOType;
    E_IOStatus eIOStatus;

    //Disabled：关闭 Enabled：启用
    bool bEnabled;

    // 目标节点id
    //int nDestNodeId;

    QRect rect;



};

///
/// \brief The CComponent class
///
class CComponent
{
public:
    CComponent();
    CComponent(const QString & strName);
    void init();

    // 组件分类，功能大致相同的组件划分分类
    enum E_ComponentBoxClass
    {
        EB_GeneralModule,
        EB_Dialog,
        EB_UserModule
    };

    // 组件类型，用于决定组件的属性，形状，具体功能
    enum E_ComponentType
    {
        EC_Login,
        EC_Judge
    };


    // 组件的形状
    enum E_ComponentShape
    {
        EC_Rectangle,  // 矩形
        EC_RoundRect,  // 圆角矩形
        EC_Rhombus,    // 菱形-多边形
    };

    enum E_ComponentStatus
    {
        EC_Normal,
        EC_Running,
        EC_Failed,
        EC_Successed,
    };



    QColor statusColor() const;

    bool operator ==(const CComponent &component) const
    {
       return strName == component.strName;
    }

    friend QDataStream & operator>>(QDataStream & in, CComponent & data);
    friend QDataStream & operator<<(QDataStream & out, const CComponent & data);

    // 组件的绘制方法
    void paint(QPainter *painter, const QRect &rect, const QPalette &palette) const;
    QPixmap renderPixmap();

    QIcon icon() const
    {
        return m_icon;
    }

    QString name() const
    {
        return strName;
    }

    // 区域大小
    QSize sizeHint() const
    {
        return rect.size();
    }
    int width() const
    {
        return rect.width();
    }
    int height() const
    {
        return rect.height();
    }

    // IO的位置
    CComponentIO io(E_Direction eDirection) const
    {
        return arrIO[eDirection];
    }
    QPoint ioPos(E_Direction eDirection) const;


    //QPainterPath shape() const;

    //int nId;

    // 组件名称
    QString strName;

    // 组件图标
    QIcon m_icon;

    QRect rect;


    E_ComponentShape eNodeShape;
    E_ComponentType eComponentType;
    E_ComponentBoxClass eComponentClass;
    E_ComponentStatus eStatus;

    CComponentIO arrIO[4];

};

#endif // CCOMPONENT_H
