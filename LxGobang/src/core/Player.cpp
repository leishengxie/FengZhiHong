#include "Player.h"

#include "ChessBoard.h"

CPlayer::CPlayer()
{

}

void CPlayer::init()
{
    m_nChoosedChessType = CChess::E_Empty;
    m_nSurplusChessNum = 0;
}

void CPlayer::chooseChessType(int nChoosedChessType)
{
    m_nChoosedChessType = nChoosedChessType;
    if (m_nChoosedChessType == CChess::E_Black)
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
    CChess chess(x, y, CChess::E_ChessType(m_nChoosedChessType));
    m_pChessBoard->setChess(chess);
}

void CPlayer::reqTakeBackChess()
{

}

void CPlayer::reset()
{
    init();
}

CChess CRobotPlayer::think()
{

}
