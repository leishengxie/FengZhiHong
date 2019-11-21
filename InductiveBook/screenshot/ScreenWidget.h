#ifndef CSCREENWIDGET_H
#define CSCREENWIDGET_H

#include <QWidget>
namespace Ui
{
    class CScreenWidget;
}

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


class CScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CScreenWidget(QWidget* parent = 0);

    QPixmap getSelectPixmap();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

private slots:
    void on_btnFinish_clicked();

    void on_btnSave_clicked();

private:
    void setSelectImageLabel();

    void drawOutSideSlelectArea(QPainter & painter);
    void drawRectTip(QPainter & painter);
    void drawControlArea(QPainter & painter);

private:
    Ui::CScreenWidget* ui;

    QPixmap m_pixmapScreen;               //全屏
    QPainterPath m_painterPathScreen;      //保存全局路径

    QPoint m_ptPress;          //鼠标左键按下后的坐标
    QPoint m_ptMove;             //终点坐标

    // 选区
    QRectF m_rectf;            //代表选区的正方形

    // 选区大小提示
    QRectF m_rectfTip;
    QString m_strTip;

    // 选区四角
//    QRectF m_rectfTopLeft;
//    QRectF m_rectfTopRight;
//    QRectF m_rectfBottomRight;
//    QRectF m_rectfBottomLeft;
    QRectF       rect1;           //第一象限的正方形
    QRectF       rect2;           //第二象限的正方形
    QRectF       rect3;           //第三象限的正方形
    QRectF       rect4;           //第四象限的正方形
    E_VertexType m_eVertexType;

    QPoint       oldPoint;        //原先的坐标

};

#endif // CSCREENWIDGET_H
