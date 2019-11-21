#ifndef SCREEN_H
#define SCREEN_H
#include <QWidget>
#include "myrect.h"
#include"qslabel.h"
#include"controlwidget.h"

// 四个角上的顶点矩形区域
enum E_VertexType
{
    RECT1,
    RECT2,
    RECT3,
    RECT4,
    RECT,
    NO
};


class CImageLabel;
class ControlWidget;

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget* parent = 0);
    void drawline();
    void textedit();
    void drawarrow();
    void drawround();
    void drawrectang();
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent*);

    void mouseReleaseEvent(QMouseEvent*);

    void mouseMoveEvent(QMouseEvent*);

    void setselectimagelabel(QMouseEvent* event);

    void keyPressEvent(QKeyEvent* e);
    //绘制控制选区，也就是四个小三角
    void drawControlArea(QPainter &);

    bool comparePoint(QPoint & p1, QPoint & p2);

    bool compareRect(QRectF & r1, QRectF & r2);

    E_VertexType pointInWhere(QPoint p);
    //返回截取之后的图片
    QPixmap getSelectPixmap();

    QPainterPath getPath();
    //保存截图
    void savePixmap();

    virtual ~Screen();
    void Exit();


private:
    bool   pointInRect(QPoint & p, QRectF & r);

private:
    QPixmap m_pixmapScreen;               //全屏
    QPainterPath m_painterPathScreen;      //保存全局路径

    QPoint m_ptPress;          //鼠标左键按下后的坐标
    QPoint m_ptMove;             //终点坐标


    bool         m_bFirstLeftPress;       //是不是第一次左键按下
    MyRect       m_myRect;//截取区域的长宽信息矩形
    //控制选区变化的正方形
    QRectF       rect1;           //第一象限的正方形
    QRectF       rect2;           //第二象限的正方形
    QRectF       rect3;           //第三象限的正方形
    QRectF       rect4;           //第四象限的正方形

    QRectF       rect;            //代表选区的正方形
    E_VertexType         m_eVertexType;
    QPoint       oldPoint;        //原先的坐标

    QWidget*     control;
    ControlWidget* controlUi;

    CImageLabel* m_pSLabel;

};

#endif // SCREEN_H
