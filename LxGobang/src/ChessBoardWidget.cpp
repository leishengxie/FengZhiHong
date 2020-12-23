#include "ChessBoardWidget.h"
#include <QPainter>

CChessBoardWidget::CChessBoardWidget(QWidget* parent) : QWidget(parent)
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

void CChessBoardWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    setFixedWidth(height());
}

void CChessBoardWidget::paintEvent(QPaintEvent* e)
{
    drawBoard();
    drawChesses();

}

void CChessBoardWidget::mouseMoveEvent(QMouseEvent* e)
{
    QWidget::mouseMoveEvent(e);
}

void CChessBoardWidget::mousePressEvent(QMouseEvent* e)
{
    QWidget::mousePressEvent(e);
}

void CChessBoardWidget::drawBoard()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    int nUnitWidth = width() / m_nWidth;
    int nUnitHeight = height() / m_nHeight;
    int nUnitSide = nUnitWidth > nUnitHeight ? nUnitHeight : nUnitWidth;

    for(int y = 0; y < m_nHeight; y++)
    {
        painter.drawLine(QPoint(0, y * nUnitSide), QPoint(width(), y * nUnitSide));
    }
    for(int x = 0; x < m_nWidth; x++)
    {
        painter.drawLine(QPoint(x * nUnitSide, 0), QPoint(x * nUnitSide, height()));
    }
}



void CChessBoardWidget::drawChesses()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    int nUnitWidth = width() / m_nWidth;
    int nUnitHeight = height() / m_nHeight;
    int nUnitSide = nUnitWidth > nUnitHeight ? nUnitHeight : nUnitWidth;
    int nChessRadius = nUnitSide / 8;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (int i = 0; i < m_nWidth; i++)
    {
        for (int j = 0; j < m_nHeight; j++)
        {
            if (m_pChessMap[i][j] == 1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(nUnitSide * j - nChessRadius, nUnitSide * i - nChessRadius
                                    , nChessRadius * 2, nChessRadius * 2);
            }
            else if (m_pChessMap[i][j] == -1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(nUnitSide * j - nChessRadius, nUnitSide * i - nChessRadius
                                    , nChessRadius * 2, nChessRadius * 2);
            }
        }
    }
}
