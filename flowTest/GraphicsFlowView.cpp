#include "GraphicsFlowView.h"
#include "QDragEnterEvent"
#include "ComponentMimeData.h"
#include "GraphicsNodeItem.h"
#include "GraphicsFlowScene.h"
#include <QtDebug>

CGraphicsFlowView::CGraphicsFlowView(QWidget *parent)
    : QGraphicsView(parent)
{
    m_pGraphicsFlowScene = new CGraphicsFlowScene;
    m_pGraphicsFlowScene->setSceneRect(0, 0, 800, 600);
    setScene(m_pGraphicsFlowScene);
    setAcceptDrops(true);

}

/// GraphicsView框架会将拖拽事件翻译为QGraphicsSceneDragDropEvent事件,再发送到场景，场景接管事件
/// ，再把事件发送到光标下接受拖拽的第一个图元。为了开启图元拖拽，创建一个QDrag对象
/// ，传递启动拖拽的QWidget的指针。图元可以同时被多个视图观察，但只有一个视图可以拖拽图元。
///
//void CGraphicsFlowView::dragEnterEvent(QDragEnterEvent *event)
//{
//    QGraphicsView::dragEnterEvent(event);
////    qDebug() << __FUNCTION__;
////    const CComponentMimeData *pComponentMimeData= qobject_cast<const CComponentMimeData *>(event->mimeData());
////    if (pComponentMimeData->hasComponent())
////    {
////        qDebug() << "accept";
////        event->acceptProposedAction();
////        return;
////    }
//}


//void CGraphicsFlowView::dropEvent(QDropEvent *event)
//{
//    //CGraphicsFlowView::dropEvent(event);

//}

//void CGraphicsFlowView::dragMoveEvent(QDragMoveEvent *event)
//{
//    //QGraphicsView::dragMoveEvent(event);
//}

//void CGraphicsFlowView::dragLeaveEvent(QDragLeaveEvent *event)
//{
//    //QGraphicsView::dragLeaveEvent(event);
//}

void CGraphicsFlowView::wheelEvent(QWheelEvent *event)
{

}

void CGraphicsFlowView::resizeEvent(QResizeEvent *event)
{

}
