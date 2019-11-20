#ifndef CSCREENWIDGET_H
#define CSCREENWIDGET_H

#include <QWidget>

class CScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CScreenWidget(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
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
    QRectF m_rectfTopLeft;
    QRectF m_rectfTopRight;
    QRectF m_rectfBottomRight;
    QRectF m_rectfBottomLeft;



};

#endif // CSCREENWIDGET_H
