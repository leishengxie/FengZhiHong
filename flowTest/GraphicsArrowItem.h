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
    explicit CGraphicsArrowItem(QGraphicsItem *parent = nullptr);

    int type() const override;

    void updateLine(const QPointF & ptStart, const E_Direction & eDirectionIoStart
                    , const QPointF & ptEnd, const E_Direction & eDirectionIoEnd);





signals:


private:
    CGraphicsNodeItem* m_pNodeStart;
    E_Direction m_eDirectionIoStart;

    CGraphicsNodeItem* m_pNodeEnd;
    E_Direction m_eDirectionIoEnd;


};



class CGraphicsArrowConnectItem : public QGraphicsPathItem
{

public:
    explicit CGraphicsArrowConnectItem(QGraphicsItem *parent = nullptr);
//CGraphicsIOItem * pIOStart
    void handleSceneMousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //CGraphicsIOItem * pIOEnd, const QPointF & ptScene
    void handleSceneMouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //const QPointF & ptScenePress
    void handleSceneMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    // 获取连接到IO端点线段另一端的端点
    QPointF getNearIOPoint(const QPointF & ptIO, const E_Direction & eDirectionIo,
                           int polylineLength = DEFAULT_POLYLINE_LENGTH);

signals:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void updateIoToIoPath();
    void updateIoToPointPath();

    void getPolylinePointArray(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QPointF & ptStart, const E_Direction & eDirectionIoStart
                               , const QPointF & ptEnd, const E_Direction & eDirectionIoEnd);

    // 下面为总结的连接方法
    void polylineConnetPoint_2(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QPointF & ptStart, const QPointF & ptEnd);

    void polylineConnetPoint_3(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QPointF & ptStart, const E_Direction & eDirectionIoStart
                               , const QPointF & ptEnd);

    void polylineConnetPoint_4(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QPointF & ptStart, const E_Direction & eDirectionIoStart
                               , const QPointF & ptEnd, const E_Direction & eDirectionIoEnd);

    void polylineConnetPoint_5(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QPointF & ptStart, const E_Direction & eDirectionIoStart
                               , const QPointF & ptEnd, const E_Direction & eDirectionIoEnd);

    void polylineConnetPoint_6(QPointF arrPos[MAX_POLYLINE_POINT]
                               , const QPointF & ptStart, const E_Direction & eDirectionIoStart
                               , const QPointF & ptEnd, const E_Direction & eDirectionIoEnd);

    quint32 polylineLineSegmentCount(const QPointF & ptStart, const E_Direction & eDirectionIoStart
                          , const QPointF & ptEnd, const E_Direction & eDirectionIoEnd);


private:
    CGraphicsIOItem * m_pIOStart;
    CGraphicsIOItem * m_pIOEnd;
    CGraphicsNodeItem* m_pNodeStart;
    CGraphicsNodeItem* m_pNodeEnd;

    QPointF m_ptEnd;

//    E_Direction m_eDirectionIoStart;
//    E_Direction m_eDirectionIoEnd;




};

#endif // CGRAPHICSARROWITEM_H
