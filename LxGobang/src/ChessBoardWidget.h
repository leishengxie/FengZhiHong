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
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

    // 派生类实现接口
    void drawBoard() override;
    void drawChesses() override;

};

#endif // CCHESSBOARDWIDGET_H
