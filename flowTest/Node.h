#ifndef CNODEDATA_H
#define CNODEDATA_H

#include "Component.h"

///
/// \brief The T_NodeIO struct
/// 定义节点的流向
///
struct T_NodeIO
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

    T_NodeIO()
        : eIOType(EI_Out)
        , nDestNodeId(-1)
        , bEnbale(false)
    {

    }

};

///
/// \brief The CNode class
///
class CNode
{
public:
    CNode(const CComponent & component);
    ~CNode();


protected:
    // 节点要显示的组件信息
    CComponent m_component;

    // 节点属性
    int nNodeId;
    QString strText;

    // 关联的其他节点
    T_NodeIO tIOTop;
    T_NodeIO tIOLeft;
    T_NodeIO tIORight;
    T_NodeIO tIOBottom;
};



#endif // CNODEDATA_H
