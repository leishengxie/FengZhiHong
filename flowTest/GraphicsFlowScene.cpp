#include "GraphicsFlowScene.h"
#include "GraphicsNodeItem.h"
#include "ComponentMimeData.h"
#include "GlobalDef.h"
#include "GraphicsArrowItem.h"
#include "GraphicsIOItem.h"
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>
#include <QtDebug>
#include <QGraphicsRectItem>

CGraphicsFlowScene::CGraphicsFlowScene(QObject *parent)
    : QGraphicsScene(parent)
{
    m_pArrowConnectItem = new CGraphicsArrowConnectItem();
    m_pArrowConnectItem->hide();
    addItem(m_pArrowConnectItem);
    m_nPressType = EG_NoOne;
}

void CGraphicsFlowScene::addNode(const QPointF &ptScene, const CComponent &component)
{
    CGraphicsNodeItem* node = new CGraphicsNodeItem(component);
    node->setPos(ptScene);
    addItem(node);

    //QPointF pt = node->mapFromScene(ptScene);
    //qDebug() << ptScene << pt;

//    QGraphicsRectItem* item = new QGraphicsRectItem();
//    item->setRect(ptScene.x(), ptScene.y(), 200, 40);
//    addItem(item);

}




/// GraphicsView框架会将拖拽事件翻译为QGraphicsSceneDragDropEvent事件,再发送到场景，场景接管事件
/// ，再把事件发送到光标下接受拖拽的第一个图元。为了开启图元拖拽，创建一个QDrag对象
/// ，传递启动拖拽的QWidget的指针。图元可以同时被多个视图观察，但只有一个视图可以拖拽图元。
///
void CGraphicsFlowScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    //QGraphicsScene::dragEnterEvent(event);
    qDebug() << __LINE__ << __FUNCTION__;
    const CComponentMimeData *pComponentMimeData= qobject_cast<const CComponentMimeData *>(event->mimeData());
    if (pComponentMimeData->hasComponent())
    {
        qDebug() << "accept 2--";
        event->acceptProposedAction();
        return;
    }
}



void CGraphicsFlowScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void CGraphicsFlowScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const CComponentMimeData *pComponentMimeData= qobject_cast<const CComponentMimeData *>(event->mimeData());
    addNode(event->scenePos() - pComponentMimeData->hotspot(), pComponentMimeData->component());
}

// 事件先传递给scene，再传给QGraphicsItem
///
/// \brief CGraphicsFlowScene::mousePressEvent
/// \param mouseEvent
/// 在QT的QGraphicsView架构中鼠标事件首先由QGraphicsView处理，若未处理传递给QGraphicsScene，
/// 然后再传递给对应位置的QGraphicsItem。QGraphicsView的mousePressEvent方法中除了进行自己关心的处理外，
/// 其它情况应让事件继续传递下去。
///
void CGraphicsFlowScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // get press whitch
    qDebug() << __FILE__ << __FUNCTION__;

    //get topmost visible item
    QGraphicsItem* pGraphicsItem = itemAt(mouseEvent->scenePos(), views().at(0)->transform());
    if (pGraphicsItem == nullptr)
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
        return;
    }

    m_ptPressPos = mouseEvent->scenePos();
    m_nPressType = pGraphicsItem->type();



    if (m_nPressType == EG_IO)
    {
        m_pArrowConnectItem->handleSceneMousePressEvent(mouseEvent);
    }

    // 传递mousePressEvent给QGraphicsItem
    QGraphicsScene::mousePressEvent(mouseEvent);

    qDebug() << __FILE__ << __FUNCTION__ << "-----2";

}

void CGraphicsFlowScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    if (m_nPressType == EG_IO)
    {
        m_pArrowConnectItem->handleSceneMouseMoveEvent(mouseEvent);
    }

}

void CGraphicsFlowScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    if (m_nPressType == EG_IO)
    {
        m_pArrowConnectItem->handleSceneMouseReleaseEvent(mouseEvent);
    }
    m_nPressType = EG_NoOne;

}


