#ifndef GRAPHICSITEMTYPEDEF_H
#define GRAPHICSITEMTYPEDEF_H
#include <QGraphicsItem>

//namespace LxFlow {

enum E_FlowRole
{
    ER_ObjectNameRole
};

enum E_GraphicsItemUserType
{
    EG_Node = QGraphicsItem::UserType + 1,
    EG_IO,
    EG_Arrow,
    EG_NoOne
};

// 直接使用Qt定义的
//Qt::Edge
//Qt::Edges
enum E_Direction
{
    ED_Left,
    ED_Top,
    ED_Right,
    ED_Bottom
};

//}

#endif // GRAPHICSITEMTYPEDEF_H
