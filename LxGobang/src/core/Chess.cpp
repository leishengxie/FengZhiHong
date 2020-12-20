#include "Chess.h"


CChess::CChess()
    : m_eChessType(E_Empty)
{

}

CChess::CChess(int x, int y, const E_ChessType &eChessType)
    : m_eChessType(eChessType)
{

}




CPlaneVector CPlaneVector::getUnitVector(E_VectorDirection eVectorDirection)
{
    switch (eVectorDirection)
    {
    case EV_Horizontal:
            return CPlaneVector::hUintVector();
    case EV_Vertical:
            return CPlaneVector::vUintVector();
    case EV_Backlas:
            return CPlaneVector::bUintVector();
    case EV_Slash:
            return CPlaneVector::sUintVector();
    default:
        break;
    }
    return CPlaneVector();
}
