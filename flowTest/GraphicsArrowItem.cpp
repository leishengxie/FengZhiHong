#include "GraphicsArrowItem.h"
#include "GraphicsNodeItem.h"
#include "GraphicsIOItem.h"
#include "GlobalDef.h"
#include "GraphicsFlowScene.h"
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QtDebug>
#include <QStyleOptionGraphicsItem>
#include <math.h>

const qreal Pi = 3.14;

///
/// \brief CGraphicsArrowItem::CGraphicsArrowItem
/// \param parent
/// 思路分析：连接线是一个寻径路线，不能与节点碰撞，且距离最短
/// 当鼠标连接到目标节点的io端点时，计算该io端点到起始节点的四个io端点（必须是输出端点）的距离，采用最近的一个io端点连线
/// 选择折线最少的
///
CGraphicsArrowItem::CGraphicsArrowItem(CGraphicsIOItem *pIOStart, CGraphicsIOItem *pIOEnd
                                       , QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
    , m_pIOStart(pIOStart)
    , m_pIOEnd(pIOEnd)
{
    //    //这是一个重载函数。 通过(c1X, c1Y)和(c2X, c2Y)指定的控制点，在当前位置和结束点(endPointX, endPointY)之间添加
    //一条三次贝塞尔曲线。
    //    QPainterPath pathCubic;
    //    pathCubic.cubicTo();
    //    //使用由(cx, cy)指定的控制点在当前点和端点(endPointX, endPointY)之间添加二次贝塞尔曲线。
    //    pathCubic.quadTo();
    setFlags(QGraphicsItem::ItemIsSelectable);

    setPen(QPen(Qt::darkGray, 2));

    // 注意QGraphicsPathItem不要设置setBrush
//    setBrush(QBrush(Qt::darkGray));

    m_painterPathStroker.setCapStyle(Qt::FlatCap);  // 端点风格
    m_painterPathStroker.setJoinStyle(Qt::SvgMiterJoin); // 连接样式
    m_painterPathStroker.setDashPattern(Qt::SolidLine);
    m_painterPathStroker.setWidth(7);


}

int CGraphicsArrowItem::type() const
{
    return EG_Arrow;
}

QPainterPath CGraphicsArrowItem::shape() const
{
    return m_pathStroker;
}

// 覆盖父类
void CGraphicsArrowItem::setPath(const QPainterPath &path)
{
    QGraphicsPathItem::setPath(path);
    m_pathStroker = m_painterPathStroker.createStroke(path);
    updateArrowHead();
}

void CGraphicsArrowItem::updatePosition()
{
    updateArrowLine();
    updateArrowHead();
}

void CGraphicsArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem op;
    op.initFrom(widget);

    // 判断选中时，设置状态为 State_None -- 去掉选中时难看的虚线框
    if (option->state & QStyle::State_Selected)
    {
        op.state = QStyle::State_None;
    }
    QGraphicsPathItem::paint(painter, &op, widget);

    painter->setRenderHint(QPainter::Antialiasing, true);
    if (option->state & QStyle::State_Selected)
    {
        painter->fillPath(m_pathStroker, QColor(77, 77, 77, 40));
    }
    painter->setBrush(pen().brush());
    painter->drawPolygon(m_polygonArrowHead);
}

void CGraphicsArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPathItem::mousePressEvent(event);
}

void CGraphicsArrowItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPathItem::mouseMoveEvent(event);
}

void CGraphicsArrowItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPathItem::mouseReleaseEvent(event);
}

QVariant CGraphicsArrowItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedChange && scene())
    {
    }
    return QGraphicsItem::itemChange(change, value);
}



void CGraphicsArrowItem::updateArrowLine()
{

}

void CGraphicsArrowItem::updateArrowHead()
{

    // 获取折线最后一段
    QPainterPath painterPath = path();
    int nElementCount = painterPath.elementCount();
    if (nElementCount < 2)
    {
        return;
    }
    QPointF ptEnd = painterPath.elementAt(nElementCount - 1);
    QPointF ptEndPre = painterPath.elementAt(nElementCount - 2);
    QLineF lineSegment(ptEnd, ptEndPre);

    // 通过直线画箭头
    qreal arrowSize = 8;
    QLineF line = lineSegment;
    line.setLength(8);
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
    {
        angle = (Pi * 2) - angle;
    }
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                    cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                    cos(angle + Pi - Pi / 3) * arrowSize);

    m_polygonArrowHead.clear();
    m_polygonArrowHead << line.p1() << arrowP1 << arrowP2;
}



////
/// \brief CGraphicsArrowConnectItem::CGraphicsArrowConnectItem
/// \param parent
///
CGraphicsArrowConnectItem::CGraphicsArrowConnectItem(QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
    , m_pIOStart(nullptr)
    , m_pIOEnd(nullptr)
    , m_pNodeStart(nullptr)
    , m_pNodeEnd(nullptr)
{

    m_rectNear.setRect(0, 0, 5, 5);
    setZValue(1);
    setPen(QPen(QPen(QColor("#808080"), 1, Qt::DotLine)));
}

void CGraphicsArrowConnectItem::handleSceneMousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem* pGraphicsItem = scene()->itemAt(mouseEvent->scenePos(), scene()->views().at(0)->transform());
    Q_ASSERT(pGraphicsItem);
    CGraphicsIOItem* ioItem = qgraphicsitem_cast<CGraphicsIOItem*>(pGraphicsItem);
    Q_ASSERT(ioItem);
    CGraphicsNodeItem* nodeItem = qgraphicsitem_cast<CGraphicsNodeItem*>(ioItem->parentItem());
    Q_ASSERT(nodeItem);
    m_pIOStart = ioItem;
    m_pNodeStart = nodeItem;
    setPos(mouseEvent->scenePos());
    show();
    showAllConnectUsableIO();
}

void CGraphicsArrowConnectItem::handleSceneMouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem* pGraphicsItem = scene()->itemAt(mouseEvent->scenePos(), scene()->views().at(0)->transform());
    CGraphicsIOItem* ioItem = nullptr;
    if(pGraphicsItem && pGraphicsItem->type() == EG_IO)
    {
        ioItem = qgraphicsitem_cast<CGraphicsIOItem*>(pGraphicsItem);
    }

    if (m_pIOStart == ioItem)
    {
        return;
    }

    if (ioItem == nullptr)
    {
        m_ptEnd = mouseEvent->scenePos();
        setIoToPointPath();
    }
    else
    {
        m_pIOEnd = ioItem;
        setIoToIoPath();
        qDebug() << "IO";

    }
    showNearConnectUsableIO();

}

void CGraphicsArrowConnectItem::handleSceneMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    // 检测是否可连接
    if (m_pIOEnd != nullptr)
    {
        CGraphicsArrowItem* pArrowItem = new CGraphicsArrowItem(m_pIOStart, m_pIOEnd);
        m_pIOStart->addArrow(pArrowItem);
        m_pIOEnd->addArrow(pArrowItem);
        pArrowItem->setPath(path());
        pArrowItem->setPos(scenePos());
        scene()->addItem(pArrowItem);
    }

    hideAllConnectUsableIO();
    setPath(QPainterPath());
    m_pIOStart = nullptr;
    m_pIOEnd = nullptr;
    m_pNodeStart = nullptr;
    m_pNodeEnd = nullptr;
    hide();
}

QPointF CGraphicsArrowConnectItem::getNearIOPoint(const QPointF &ptIO, const E_Direction &eDirectionIo
                                                  , int polylineLength)
{
    QPointF ptResult = ptIO;
    switch (eDirectionIo)
    {
    case ED_Left:
        ptResult.setX(ptIO.x() - polylineLength);
        break;
    case ED_Top:
        ptResult.setY(ptIO.y() - polylineLength);
        break;
    case ED_Right:
        ptResult.setX(ptIO.x() + polylineLength);
        break;
    case ED_Bottom:
        ptResult.setY(ptIO.y() + polylineLength);
        break;
    }
    return ptResult;
}

void CGraphicsArrowConnectItem::showAllConnectUsableIO()
{
    m_lstConnectUsableIO.clear();
    QList<QGraphicsItem *> lstGraphicsItem = scene()->items();
    foreach (QGraphicsItem* pGraphicsItem, lstGraphicsItem)
    {
        if(pGraphicsItem->type() != E_GraphicsItemUserType::EG_IO)
        {
            continue;
        }
        CGraphicsIOItem* pIOItemEnd = qgraphicsitem_cast<CGraphicsIOItem*>(pGraphicsItem);
        if(m_pIOStart->canConnectIO(pIOItemEnd))
        {
            pIOItemEnd->showFacade(CComponentIO::EI_ConnectUsable);
            m_lstConnectUsableIO.append(pIOItemEnd);
        }
    }
}

void CGraphicsArrowConnectItem::showNearConnectUsableIO()
{
    m_rectNear.moveCenter(m_ptEnd);
    foreach (CGraphicsIOItem* pIOItemNear, m_lstIONear)
    {
        pIOItemNear->showFacade(CComponentIO::EI_ConnectUsable);
    }

    m_lstIONear.clear();
    QList<QGraphicsItem *> lstGraphicsItem = scene()->items(m_rectNear);
    foreach (QGraphicsItem* pGraphicsItem, lstGraphicsItem)
    {
        if(pGraphicsItem->type() != E_GraphicsItemUserType::EG_IO)
        {
            continue;
        }
        CGraphicsIOItem* pIOItemEnd = qgraphicsitem_cast<CGraphicsIOItem*>(pGraphicsItem);
        if (m_lstConnectUsableIO.contains(pIOItemEnd))
        {
            m_lstIONear.append(pIOItemEnd);
        }
    }
    foreach (CGraphicsIOItem* pIOItemNear, m_lstIONear)
    {
        pIOItemNear->showFacade(CComponentIO::EI_ConnectUsableNear);
    }
}

void CGraphicsArrowConnectItem::hideAllConnectUsableIO()
{
    foreach (CGraphicsIOItem* pIOItem, m_lstConnectUsableIO)
    {
        pIOItem->showFacade(CComponentIO::EI_Normal);
        pIOItem->hide();
    }
}

void CGraphicsArrowConnectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                      QWidget *widget)
{
    QGraphicsPathItem::paint(painter, option, widget);
}


// IO -- IO
void CGraphicsArrowConnectItem::setIoToIoPath()
{
    if (m_pIOStart == nullptr)
    {
        return;
    }

    QPainterPath painterPath = getPolylinePath(m_pIOStart->sceneCenterPos()
                                               , m_pIOStart->direction()
                                               , m_pIOEnd->sceneCenterPos()
                                               , m_pIOEnd->direction());

    setPath(painterPath);
}


// IO -- Point
void CGraphicsArrowConnectItem::setIoToPointPath()
{
    if (m_pIOStart == nullptr)
    {
        return;
    }

    // 起点应矫正为io的中心
    QPointF ptStart = m_pIOStart->sceneCenterPos();
    E_Direction eDirectionIoStart = m_pIOStart->direction();
    QPointF ptEnd = m_ptEnd;

    QPointF ptNode = m_pNodeStart->scenePos();
    QRectF rectNodeScene = QRectF(ptNode, m_pNodeStart->size());

    // 先排除ptEnd在m_pNodeStart内部的情况
    if (rectNodeScene.contains(ptEnd))
    {
        return;
    }



}


///
/// \brief CGraphicsArrowConnectItem::getPolylinePath
/// \param rectSceneStart 起始节点(组件)的在场景的Rect区域
/// \param eDirectionIoStart io在起始节点(组件)的位置
/// \param rectSceneEnd 终止节点(组件)的在场景的Rect区域
/// \param eDirectionIoEnd io在终止节点(组件)的位置
/// \return
///
QPainterPath CGraphicsArrowConnectItem::getPolylinePath(const QRectF &rectSceneStart, const E_Direction &eDirectionIoStart
                                                        , const QRectF &rectSceneEnd, const E_Direction &eDirectionIoEnd)
{
    QPointF arrPos[MAX_POLYLINE_POINT];
    // 用户点击io边缘时，是想连接该IO，所以把点击的点重新更到io的中心,用sceneCenterPos替代scenePos
    getPolylinePointArray(arrPos, rectSceneStart, eDirectionIoStart, rectSceneEnd, eDirectionIoEnd);
    QPainterPath painterPath = convertArrayScenePosToPath(arrPos);
    return painterPath;
}

QPainterPath CGraphicsArrowConnectItem::getPolylinePath(const QRectF &rectSceneStart, const E_Direction &eDirectionIoStart
                                                        , const QPointF &ptEnd)
{
    E_Direction eDirectionEnd;
    int nLineSegmentCountMin = MAX_POLYLINE_POINT - 1;
    // 如果目标io的Direction与起始io形成折线线段数最少，取该方向Direction
    for( int i = 0; i < 4; ++i)
    {
        int nLineSegmentCount = polylineLineSegmentCount(rectSceneStart, eDirectionIoStart, ptEnd, E_Direction(i));
        if (nLineSegmentCount < nLineSegmentCountMin)
        {
            eDirectionEnd = E_Direction(i);
            nLineSegmentCountMin = nLineSegmentCount;
        }
    }

    return getPolylinePath(rectSceneStart, eDirectionIoStart, ptEnd, eDirectionEnd);
}

QPainterPath CGraphicsArrowConnectItem::convertArrayScenePosToPath(QPointF arrPos[])
{
    // 场景坐标数组转换为自身的path,即减去自身所在的位置
    prepareGeometryChange();
    for(int i = 0; i < MAX_POLYLINE_POINT; ++i)
    {
        if(arrPos[i].isNull())
        {
            break;
        }
        arrPos[i] = arrPos[i] - pos();
    }

    QPainterPath painterPath;
    painterPath.moveTo(arrPos[0]);
    for(int i = 1; i < MAX_POLYLINE_POINT; ++i)
    {
        if(arrPos[i].isNull())
        {
            break;
        }
        painterPath.lineTo(arrPos[i]);
    }
    return painterPath;
}

void CGraphicsArrowConnectItem::getPolylinePointArray(QPointF arrPos[]
                                                      , const QPointF &ptStart, const E_Direction &eDirectionIoStart
                                                      , const QPointF &ptEnd, const E_Direction &eDirectionIoEnd)
{
    bool bSameX = (ptStart.x() == ptEnd.x());
    bool bSameY = (ptStart.y() == ptEnd.y());

    // io端点同为水平或同为垂直方向 左-左 左-右 右-左，上-下 等
    if (eDirectionIoStart % 2 == eDirectionIoEnd % 2)
    {
        // io端点同一方向
        if(eDirectionIoStart == eDirectionIoEnd)
        {
            polylineConnetPoint_6(arrPos, ptStart, eDirectionIoStart, ptEnd, eDirectionIoEnd);
        }
        else //io端点反向
        {
            // io端点水平反向
            if(eDirectionIoStart % 2 == 0)
            {
                // 内侧相接
                if((eDirectionIoStart == ED_Right && ptStart.x() < ptEnd.x())
                        || (eDirectionIoStart == ED_Left && ptStart.x() > ptEnd.x()))
                {
                    if (bSameY)
                    {
                        polylineConnetPoint_2(arrPos, ptStart, ptEnd);
                    }
                    else
                    {
                        polylineConnetPoint_4(arrPos, ptStart, eDirectionIoStart, ptEnd, eDirectionIoEnd);
                    }
                }
                else // 外侧
                {
                    polylineConnetPoint_6(arrPos, ptStart, eDirectionIoStart, ptEnd, eDirectionIoEnd);
                }
            }
            else // io端点垂直反向
            {
                // 内侧相接
                if((eDirectionIoStart == ED_Bottom && ptStart.y() < ptEnd.y())
                        || (eDirectionIoStart == ED_Top && ptStart.y() > ptEnd.y()))
                {
                    if (bSameX)
                    {
                        polylineConnetPoint_2(arrPos, ptStart, ptEnd);
                    }
                    else
                    {
                        polylineConnetPoint_4(arrPos, ptStart, eDirectionIoStart, ptEnd, eDirectionIoEnd);
                    }
                }
                else // 外侧
                {
                    polylineConnetPoint_6(arrPos, ptStart, eDirectionIoStart, ptEnd, eDirectionIoEnd);
                }
            }
        }
    }
    else //io端点一个是垂直方向，一个水平方向
    {
        polylineConnetPoint_5(arrPos, ptStart, eDirectionIoStart, ptEnd, eDirectionIoEnd);
    }
}

///
/// \brief CGraphicsArrowConnectItem::polylineConnetPoint_2 连接点为2，直接形成线段
/// \param arrPos
/// \param ptStart
/// \param ptEnd
///
void CGraphicsArrowConnectItem::polylineConnetPoint_2(QPointF arrPos[]
                                                      , const QPointF &ptStart, const QPointF &ptEnd)
{
    arrPos[0] = ptStart;
    arrPos[1] = ptEnd;
}

void CGraphicsArrowConnectItem::polylineConnetPoint_3(QPointF arrPos[]
                                                      , const QPointF &ptStart, const E_Direction &eDirectionIoStart
                                                      , const QPointF &ptEnd)
{
    arrPos[0] = ptStart;
    arrPos[1] = getNearIOPoint(ptStart, eDirectionIoStart);
    arrPos[2] = ptEnd;
}

void CGraphicsArrowConnectItem::polylineConnetPoint_4(QPointF arrPos[],
                                                      const QPointF &ptStart, const E_Direction &eDirectionIoStart
                                                      , const QPointF &ptEnd, const E_Direction &eDirectionIoEnd)
{
    arrPos[0] = ptStart;
    arrPos[1] = getNearIOPoint(ptStart, eDirectionIoStart);
    arrPos[2] = arrPos[1];
    if(eDirectionIoStart % 2 == 0)
    {
        arrPos[2].setY(ptEnd.y());
    }
    else
    {
        arrPos[2].setX(ptEnd.x());
    }
    arrPos[3] = ptEnd;
}

void CGraphicsArrowConnectItem::polylineConnetPoint_5(QPointF arrPos[]
                                                      , const QPointF &ptStart, const E_Direction &eDirectionIoStart
                                                      , const QPointF &ptEnd, const E_Direction &eDirectionIoEnd)
{
    arrPos[0] = ptStart;
    arrPos[1] = getNearIOPoint(ptStart, eDirectionIoStart);
    arrPos[3] = getNearIOPoint(ptEnd, eDirectionIoEnd);
    arrPos[4] = ptEnd;

    // 水平
    if (eDirectionIoStart % 2 == 0)
    {
        arrPos[2].setX(arrPos[1].x());
        arrPos[2].setY(arrPos[3].y());
    }
    else
    {
        arrPos[2].setY(arrPos[1].y());
        arrPos[2].setX(arrPos[3].x());
    }
}

// QSizeF sizeNodeEnd = (m_pNodeEnd == nullptr ? QSizeF(200, 40) : m_pNodeEnd->size());
void CGraphicsArrowConnectItem::polylineConnetPoint_6(QPointF arrPos[]
                                                      , const QPointF &ptStart, const E_Direction &eDirectionIoStart
                                                      , const QPointF &ptEnd, const E_Direction &eDirectionIoEnd
                                                      , , QSizeF sizeNodeEnd)
{
    arrPos[0] = ptStart;
    arrPos[1] = getNearIOPoint(ptStart, eDirectionIoStart);
    arrPos[4] = getNearIOPoint(ptEnd, eDirectionIoEnd);
    arrPos[5] = ptEnd;
    if(eDirectionIoStart % 2 == 0)
    {
        // 通过平移端点4可用确定端点3
        QPointF ptOffset(0, sizeNodeEnd.height() / 2 + DEFAULT_POLYLINE_LENGTH);
        if(ptStart.y() < ptEnd.y())
        {
            arrPos[3] = arrPos[4] - ptOffset;
        }
        else
        {
            arrPos[3] = arrPos[4] + ptOffset;
        }
        arrPos[2] = arrPos[1];
        arrPos[2].setY(arrPos[3].y());
    }
    else
    {
        QPointF ptOffset(sizeNodeEnd.width() / 2 + DEFAULT_POLYLINE_LENGTH, 0);
        if(ptStart.x() < ptEnd.x())
        {
            arrPos[3] = arrPos[4] - ptOffset;
        }
        else
        {
            arrPos[3] = arrPos[4] + ptOffset;
        }
        arrPos[2] = arrPos[1];
        arrPos[2].setX(arrPos[3].x());
    }
}


///
/// \brief CGraphicsArrowConnectItem::polylineLineSegmentCount
/// \param ptStart
/// \param eDirectionIoStart
/// \param ptEnd
/// \param eDirectionIoEnd
/// \return 返回折线数线段数
///
quint32 CGraphicsArrowConnectItem::polylineLineSegmentCount(const QPointF &ptStart, const E_Direction &eDirectionIoStart
                                                            , const QPointF &ptEnd, const E_Direction &eDirectionIoEnd)
{
    int nLineSegmentCount = 1;
    bool bSameX = (ptStart.x() == ptEnd.x());
    bool bSameY = (ptStart.y() == ptEnd.y());

    // io端点同为水平或同为垂直方向 左-左 左-右 右-左，上-下 等
    if (eDirectionIoStart % 2 == eDirectionIoEnd % 2)
    {
        // io端点同一方向
        if(eDirectionIoStart == eDirectionIoEnd)
        {
            nLineSegmentCount = 5;
        }
        else //io端点反向
        {
            // io端点水平反向
            if(eDirectionIoStart % 2 == 0)
            {
                // 内侧相接
                if((eDirectionIoStart == ED_Right && ptStart.x() < ptEnd.x())
                        || (eDirectionIoStart == ED_Left && ptStart.x() > ptEnd.x()))
                {
                    nLineSegmentCount = bSameY ? 1 : 2;
                }
                else // 外侧
                {
                    nLineSegmentCount = 5;
                }
            }
            else // io端点垂直反向
            {
                // 内侧相接
                if((eDirectionIoStart == ED_Bottom && ptStart.y() < ptEnd.y())
                        || (eDirectionIoStart == ED_Top && ptStart.y() > ptEnd.y()))
                {
                    nLineSegmentCount = bSameX ? 1 : 2;
                }
                else // 外侧
                {
                    nLineSegmentCount = 5;
                }
            }
        }
    }
    else //io端点一个是垂直方向，一个水平方向
    {
        nLineSegmentCount = 4;
    }

    return nLineSegmentCount;
}
