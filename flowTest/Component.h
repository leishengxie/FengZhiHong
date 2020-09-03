#ifndef CCOMPONENT_H
#define CCOMPONENT_H
#include <QObject>
#include <QIcon>

// 组件io
struct T_ComponentIO
{
    enum E_IOType
    {
        EI_In,
        EI_Out
    };

    E_IOType eIOType;

    bool bEnbale;

    // 目标节点id
    int nDestNodeId;

    T_ComponentIO()
        : eIOType(EI_Out)
        , nDestNodeId(-1)
        , bEnbale(false)
    {

    }

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
        return QSize(200, 40);
    }

    //int nId;

    // 组件名称
    QString strName;

    // 组件图标
    QIcon m_icon;



    E_ComponentShape eNodeShape;
    E_ComponentType eComponentType;
    E_ComponentBoxClass eComponentClass;
    E_ComponentStatus eNodeStatus;

    T_ComponentIO tIOTop;
    T_ComponentIO tIOLeft;
    T_ComponentIO tIORight;
    T_ComponentIO tIOBottom;

};

#endif // CCOMPONENT_H
