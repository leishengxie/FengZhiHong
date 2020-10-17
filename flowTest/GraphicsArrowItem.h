#ifndef CGRAPHICSARROWITEM_H
#define CGRAPHICSARROWITEM_H

#include "GlobalDef.h"
#include <QGraphicsPathItem>

#define DEFAULT_POLYLINE_LENGTH 20  // 默认折线长度
#define MAX_POLYLINE_POINT 6  // 最大折线转折端点数，== 线段+1

class CGraphicsNodeItem;
class CGraphicsIOItem;

///
/// \brief The CGraphicsArrowItem class
/// 分为线和箭头
/// 线可分为：
/// 1. 曲线 可用QPainterPath自带的cubicTo()，quadTo
/// 2. 直线
/// 3. 折线 需要自己定义折线点
/// 本类采用折线连接
///
class CGraphicsArrowItem : public QGraphicsPathItem
{

public:
    explicit CGraphicsArrowItem(CGraphicsIOItem* pIOStart, CGraphicsIOItem* pIOEnd
                                , QGraphicsItem *parent = nullptr);

    int type() const override;

    QPainterPath shape() const;
    void setPath(const QPainterPath &path);

    void updatePosition();


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    void updateArrowLine();
    void updateArrowHead();

private:
    CGraphicsIOItem* m_pIOStart;
    CGraphicsIOItem* m_pIOEnd;

    QPolygonF m_polygonArrowHead;

    // 空间换取时间
    QPainterPathStroker m_painterPathStroker;
    QPainterPath m_pathStroker;


};



///
/// \brief The CGraphicsArrowConnectItem class 辅助线连接器,包含连接方法
///
class CGraphicsArrowConnectItem : public QGraphicsPathItem
{

public:
    // 通用方法 io -- io, 考虑连接线与rectSceneStart，rectSceneEnd不能碰撞，对于其他未加入连接的节点是否碰撞暂时不加以考虑
    static QPainterPath getPolylinePath(const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                        , const QRectF & rectSceneEnd, const E_Direction & eDirectionIoEnd
                                        , const QPointF ptArrowScenePos);
    // io -- Point
    static QPainterPath getPolylinePath(const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                        , const QPointF & ptEnd, const QPointF ptArrowScenePos);

private:
    // 获取连接到IO端点线段另一端的端点
    static QPointF getIOPoint(const QRectF & rectScene, const E_Direction & eDirection);

    // 获取出IO端点 线段另一端的端点
    static QPointF getNearIOPoint(const QRectF & rectScene, const E_Direction & eDirection,
                           int polylineLength = DEFAULT_POLYLINE_LENGTH);

    static QPainterPath convertArrayScenePosToPath(const QPointF arrPos[MAX_POLYLINE_POINT], const QPointF ptArrowScenePos);

    static quint32 getPolylineConnetPointCount(const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                               , const QRectF & rectSceneEnd, const E_Direction & eDirectionIoEnd);

    // 下面为总结的连接方法, 数字下标表示右多少个点
    static void polylineConnetPoint_2(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                      , const QRectF & rectSceneEnd, const E_Direction & eDirectionIoEnd);

    static void polylineConnetPoint_3(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                      , const QRectF & rectSceneEnd, const E_Direction & eDirectionIoEnd);

    static void polylineConnetPoint_4(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                      , const QRectF & rectSceneEnd, const E_Direction & eDirectionIoEnd);

    static void polylineConnetPoint_5(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                      , const QRectF & rectSceneEnd, const E_Direction & eDirectionIoEnd);

    static void polylineConnetPoint_6(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QRectF & rectSceneStart, const E_Direction & eDirectionIoStart
                                      , const QRectF & rectSceneEnd, const E_Direction & eDirectionIoEnd);





public:
    explicit CGraphicsArrowConnectItem(QGraphicsItem *parent = nullptr);

    void handleSceneMousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void handleSceneMouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void handleSceneMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void setIoToIoPath();
    void setIoToPointPath();

    void showAllConnectUsableIO();
    void showNearConnectUsableIO();
    void hideAllConnectUsableIO();


private:
    CGraphicsIOItem * m_pIOStart;
    CGraphicsIOItem * m_pIOEnd;
    CGraphicsNodeItem* m_pNodeStart;
    CGraphicsNodeItem* m_pNodeEnd;

    QPointF m_ptEnd;

    QRectF m_rectNear;
    QList<CGraphicsIOItem *> m_lstIONear;

    QList<CGraphicsIOItem *> m_lstConnectUsableIO;
//    E_Direction m_eDirectionIoStart;
//    E_Direction m_eDirectionIoEnd;




};

#endif // CGRAPHICSARROWITEM_H
