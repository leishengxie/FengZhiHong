#ifndef CCHESSBOARDWIDGET_H
#define CCHESSBOARDWIDGET_H

#include "core/ChessBoard.h"
#include <QWidget>

class CChessBoardWidget : public QWidget, public CChessBoard
{
    Q_OBJECT
public:
    explicit CChessBoardWidget(QWidget *parent = nullptr);

    int heightForWidth(int w) const override;
    bool hasHeightForWidth() const override;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *e) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;

    // 实际落子
    void mouseReleaseEvent(QMouseEvent *event) override;

    // 派生类实现接口
    void drawBoard() override;
    void drawChesses() override;


private:
    void drawHoverPos();

private:
    int m_nUnitSide;
    CPoint m_posHover;

};

#endif // CCHESSBOARDWIDGET_H
