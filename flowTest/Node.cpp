#include "Node.h"


CNode::CNode(const CComponent &component)
    : m_component(component)
    , nNodeId(-1)
    , strText(component.name())
{

}

CNode::~CNode()
{

}
