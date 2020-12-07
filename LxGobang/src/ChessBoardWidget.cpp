#include "ChessBoardWidget.h"

CChessBoardWidget::CChessBoardWidget(QWidget *parent) : QWidget(parent)
{
//    QSizePolicy policy = sizePolicy();
//    policy.setHeightForWidth(true);
//    setSizePolicy(policy);
}

int CChessBoardWidget::heightForWidth(int w) const
{
    return w;
}

bool CChessBoardWidget::hasHeightForWidth() const
{
    return true;
}

void CChessBoardWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    setFixedWidth(height());
}

void CChessBoardWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
}

void CChessBoardWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
}

void CChessBoardWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}
