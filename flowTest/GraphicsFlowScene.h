#ifndef CGRAPHICSFLOWSCENE_H
#define CGRAPHICSFLOWSCENE_H

#include <QGraphicsScene>
#include "Component.h"

class CGraphicsArrowConnectItem;

//template<class T>
//T* firstItem(QGraphicsScene *scene, QPointF pos)
//{
//    foreach (QGraphicsItem* item, scene->items(pos))
//    {
//        T* base = dynamic_cast<T*>(item);
//        if (base)
//        {
//            return base;
//        }
//    }
//    return nullptr;
//}

///
/// \brief The CGraphicsFlowScene class
/// 本身不可见，是一个存储图元的容器，必须通过与之相连的QGraphicsView视图来显示及与外界进行交互，
/// 主要提供图元的操作接口、传递事件和管理各个图元状态，提供无变换的绘制功能（如打印）
///
class CGraphicsFlowScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CGraphicsFlowScene(QObject *parent = nullptr);

    void addNode(const QPointF &ptScene, const CComponent & component);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

signals:

private:
    QPointF m_ptPressPos;
    int m_nPressType;

    CGraphicsArrowConnectItem* m_pArrowConnectItem;

};

#endif // CGRAPHICSFLOWSCENE_H
