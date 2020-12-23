#include "Player.h"

#include "ChessBoard.h"

CPlayer::CPlayer()
{

}

void CPlayer::init()
{
    m_eChessTypeChoosed = CChess::E_Empty;
    m_nSurplusChessNum = 0;
}

void CPlayer::setChoosedChessType(const CChess::E_ChessType &eChessType)
{
    m_eChessTypeChoosed = eChessType;
    if (m_eChessTypeChoosed == CChess::E_Black)
    {
        m_nSurplusChessNum = TOTAL_BLACK_CHESS;
    }
    else
    {
        m_nSurplusChessNum = TOTAL_WHITE_CHESS;
    }
}

void CPlayer::moveInChess(int x, int y)
{
    CChess chess(x, y, m_eChessTypeChoosed);
    m_pChessBoard->setChess(chess);
}

void CPlayer::moveInChess(const CPoint &pos)
{
    moveInChess(pos.x(), pos.y());
}

void CPlayer::reqTakeBackChess()
{

}

void CPlayer::reset()
{
    init();
}

CPoint CRobotPlayer::think()
{

}
