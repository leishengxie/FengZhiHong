#include "ChessBoardWidget.h"

#include "core/Judge.h"
#include "core/Player.h"

#include <math.h>
#include <QPainter>
#include <QMouseEvent>

CChessBoardWidget::CChessBoardWidget(QWidget* parent)
    : QWidget(parent)
    , CChessBoard()
{
//    QSizePolicy policy = sizePolicy();
//    policy.setHeightForWidth(true);
//    setSizePolicy(policy);
    setMouseTracking(true);
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

    int nUnitWidth = width() / m_nWidth;
    int nUnitHeight = height() / m_nHeight;
    m_nUnitSide = nUnitWidth > nUnitHeight ? nUnitHeight : nUnitWidth;
}

void CChessBoardWidget::paintEvent(QPaintEvent* e)
{
    drawHoverPos();

    drawBoard();
    drawChesses();

}

void CChessBoardWidget::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);

    if(CJudge::getInstance()->isHavenotBegunYet())
    {
        return;
    }
    if(CJudge::getInstance()->activePlayer()->isRobot())
    {
        return;
    }

    // 四舍五入
    int nMargin = m_nUnitSide / 2;
    int x = std::round((double)(event->x() - nMargin) / (double)m_nUnitSide);
    int y = std::round((double)(event->y() - nMargin) / (double)m_nUnitSide);
    if(isInvaildAt(x, y))
    {
        return;
    }
    if(!isEmptyAt(x, y))
    {
        return;
    }

    if(m_posHover.x() == x && m_posHover.y() == y)
    {
        return;
    }

    m_posHover.setX(x);
    m_posHover.setY(y);

    // 存了坐标后也要重绘
    update();
}

void CChessBoardWidget::mousePressEvent(QMouseEvent* e)
{
    QWidget::mousePressEvent(e);
}

void CChessBoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(CJudge::getInstance()->isHavenotBegunYet())
    {
        return;
    }
    if(CJudge::getInstance()->activePlayer()->isRobot())
    {
        return;
    }

    // 四舍五入
    int nMargin = m_nUnitSide / 2;
    int x = std::round((double)(event->x() - nMargin) / (double)m_nUnitSide);
    int y = std::round((double)(event->y() - nMargin) / (double)m_nUnitSide);
    if(isInvaildAt(x, y))
    {
        return;
    }
    if(!isEmptyAt(x, y))
    {
        return;
    }


    setChess(x, y, CJudge::getInstance()->activePlayer()->choosedChessType());
    update();
    CJudge::getInstance()->onEventSetChessDone();

}

void CChessBoardWidget::drawBoard()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    int nMargin = m_nUnitSide / 2;
    for(int y = 0; y < m_nHeight; y++)
    {
        painter.drawLine(QPoint(nMargin, nMargin + y * m_nUnitSide)
                         , QPoint(width() - nMargin, nMargin + y * m_nUnitSide));
    }
    for(int x = 0; x < m_nWidth; x++)
    {
        painter.drawLine(QPoint(nMargin + x * m_nUnitSide, nMargin)
                         , QPoint(nMargin + x * m_nUnitSide, height() - nMargin));
    }
}



void CChessBoardWidget::drawChesses()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    int nChessRadius = m_nUnitSide / 4;
    int nMargin = m_nUnitSide / 2;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (int x = 0; x < m_nWidth; x++)
    {
        for (int y = 0; y < m_nHeight; y++)
        {
            if (m_pChessMap[x][y] == CChess::E_White)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(nMargin + m_nUnitSide * x - nChessRadius
                                    , nMargin + m_nUnitSide * y - nChessRadius
                                    , nChessRadius * 2, nChessRadius * 2);
            }
            else if (m_pChessMap[x][y] == CChess::E_Black)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(nMargin + m_nUnitSide * x - nChessRadius
                                    , nMargin + m_nUnitSide * y - nChessRadius
                                    , nChessRadius * 2, nChessRadius * 2);
            }
        }
    }
}

void CChessBoardWidget::drawHoverPos()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    int nRadius = m_nUnitSide / 8;
    int nMargin = m_nUnitSide / 2;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(nMargin + m_nUnitSide * m_posHover.x() - nRadius
                     , nMargin + m_nUnitSide * m_posHover.y() - nRadius
                     , nRadius * 2, nRadius * 2);

}
