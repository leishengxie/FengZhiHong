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
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:

};

#endif // CCHESSBOARDWIDGET_H
