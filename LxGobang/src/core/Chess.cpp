#include "Chess.h"

CChess::CChess()
    : m_nPosX(-1)
    , m_nPosY(-1)
    , m_nChessType(E_Black)
{

}

CChess::CChess(int x, int y, CChess::E_ChessType eChessType)
    : m_nPosX(x)
    , m_nPosY(y)
    , m_nChessType(eChessType)
{

}
