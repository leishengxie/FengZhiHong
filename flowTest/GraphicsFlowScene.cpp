#include "GraphicsFlowScene.h"
#include "GraphicsNodeItem.h"
#include "ComponentMimeData.h"
#include <QGraphicsSceneDragDropEvent>
#include <QtDebug>

CGraphicsFlowScene::CGraphicsFlowScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void CGraphicsFlowScene::addNode(const QPointF &ptScene, const CComponent &component)
{
    CGraphicsNodeItem* node = new CGraphicsNodeItem(component);
    node->setPos(ptScene);
    addItem(node);
    //QPointF pt = node->mapFromScene(ptScene);
    //qDebug() << ptScene << pt;

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
    //QPointF ptScene = mapToScene(event->pos());
    addNode(event->scenePos(), pComponentMimeData->component());
}


