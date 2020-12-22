#include "ChessBoard.h"

//#include <vector>

//using namespace std;


CChessBoard::CChessBoard(int nWidth, int nHeight)
    : m_nWidth(nWidth)
    , m_nHeight(nHeight)
{
    // 定义二重指针指向指针数组
    m_pChessMap = new int*[m_nWidth];

    // 数组的元素都是指针，指向一个新的数组
    for (int x = 0; x < m_nWidth; ++x)
    {
        m_pChessMap[x] = new int[m_nHeight];
    }

    init();
}

void CChessBoard::init()
{
    // 给各元素赋值
    for (int x = 0; x < m_nWidth; ++x)
    {
        for (int j = 0; j < m_nHeight; ++j)
        {
            m_pChessMap[x][j] = CChess::E_Empty;
        }
    }
}

\
void CChessBoard::setChess(const CChess &chess)
{
    m_pChessMap[chess.x()][chess.y()] = chess.type();
    m_stackChessRecord.push(chess);
}

void CChessBoard::takeBackChess(int nStep)
{
    while (nStep-- > 0)
    {
        if (m_stackChessRecord.empty())
        {
            break;
        }
        CChess chess = m_stackChessRecord.top();
        m_pChessMap[chess.x()][chess.y()] = CChess::E_Empty;
        m_stackChessRecord.pop();
    }

}

CChess::E_ChessType CChessBoard::chessTypeAt(int x, int y) const
{

    return CChess::E_ChessType(m_pChessMap[x][y]);
}

CChess::E_ChessType CChessBoard::chessTypeAt(const CPoint &pos) const
{
    return chessTypeAt(pos.x(), pos.y());
}

void CChessBoard::reset()
{
    init();
}

bool CChessBoard::isInvaildAt(const CPoint &pos) const
{
    return isInvaildAt(pos.x(), pos.y());
}

bool CChessBoard::isInvaildAt(int x, int y) const
{
    if (x < 0 || y < 0 || x >= chessBoardWidth() || y >= chessBoardHeight())
    {
        return true;
    }
    return false;
}

bool CChessBoard::isEmptyAt(const CPoint &pos) const
{
    return chessTypeAt(pos) == CChess::E_Empty;
}

bool CChessBoard::isEmptyAt(int x, int y) const
{
    return chessTypeAt(x, y) == CChess::E_Empty;
}

// 阳线：棋盘上可见的纵线top-bottom, 和横线left-right
// 阴线：棋盘对角线及与对角线平行的隐形斜线 反斜杠topleft-bottomright, 斜杠topright-bottomleft
///
/// \brief CChessBoard::hasBecome_5 成五判断
/// \param eChessType
/// \return
///
bool CChessBoard::hasBecome_5(CChess::E_ChessType eChessType)
{
    //bool bHasBecome5 = false;
    /// top-bottom
    for (int x = 0; x < m_nWidth; ++x)
    {
        int nCountContinuous = 0;   // 连续的颗数
        for (int y = 0; y < m_nHeight; ++y)
        {
            if(m_pChessMap[x][y] == eChessType)
            {
                nCountContinuous++;
                if(y == m_nHeight - 1)
                {
                    if(nCountContinuous > 4)
                    {
                        //bHasBecome5 = true;
                        return true;
                    }
                }
            }
            else
            {
                if(nCountContinuous > 4)
                {
                    //bHasBecome5 = true;
                    //break;
                    return true;
                }
                nCountContinuous = 0;
            }
        }
    }

    /// left-right
    for (int y = 0; y < m_nHeight; ++y)
    {
        int nCountContinuous = 0;
        for (int x = 0; x < m_nWidth; ++x)
        {
            if(m_pChessMap[x][y] == eChessType)
            {
                nCountContinuous++;
                if(x == m_nWidth - 1)
                {
                    if(nCountContinuous > 4)
                    {
                        return true;
                    }
                }
            }
            else
            {
                if(nCountContinuous > 4)
                {
                    return true;
                }
                nCountContinuous = 0;
            }
        }
    }

    /// topleft-bottomright part1
    for (int y = 0; y < m_nHeight; ++y)
    {
        int nCountContinuous = 0;
        int y1 = y;
        for (int x = 0; y1 < m_nHeight; ++x, ++y1)
        {
            if(m_pChessMap[x][y1] == eChessType)
            {
                nCountContinuous++;
                if(y1 == m_nHeight - 1)
                {
                    if(nCountContinuous > 4)
                    {
                        return true;
                    }
                }
            }
            else
            {
                if(nCountContinuous > 4)
                {
                    return true;
                }
                nCountContinuous = 0;
            }
        }
    }

    /// topleft-bottomright part2
    for (int x = 0; x < m_nWidth; ++x)
    {
        int nCountContinuous = 0;
        int x1 = x;
        for (int y = 0; x1 < m_nWidth; ++x, ++y)
        {
            if(m_pChessMap[x1][y] == eChessType)
            {
                nCountContinuous++;
                if(x1 == m_nWidth - 1)
                {
                    if(nCountContinuous > 4)
                    {
                        return true;
                    }
                }
            }
            else
            {
                if(nCountContinuous > 4)
                {
                    return true;
                }
                nCountContinuous = 0;
            }
        }
    }
}

bool CChessBoard::hasBecome_5(CChess::E_ChessType eChessType, int x, int y)
{
    return false;
}

bool CChessBoard::hasBecome_5(CChess::E_ChessType eChessType, const CPoint &pos)
{
    return hasBecome_5(eChessType, pos.x(), pos.y());
}




CChessGroup CChessBoard::getBestGroup(const CPoint &pos, const CChess::E_ChessType &eChessType
                                      , const CPlaneVector &planeVector, int nStartEndDistance) const
{
    int nMaxNum = 0;
    CPoint posHeadBest;

    for (int i = nStartEndDistance - 1; i > -1; --i)
    {
        CPoint posHead = pos - planeVector * i;
        if (isInvaildAt(posHead))
        {
            continue;
        }
        int nNum = getSameChessNum(posHead, eChessType, planeVector, nStartEndDistance);
        if (nNum > nMaxNum)
        {
            nMaxNum = nNum;
            posHeadBest = posHead;
        }
    }
    return CChessGroup(posHeadBest, planeVector, eChessType);
}



int CChessBoard::getSameChessMaxNum(const CChess &chess, const CPlaneVector &planeVector, int nStartEndDistance)
{
    return getSameChessMaxNum(chess.pos(), chess.type(), planeVector, nStartEndDistance);
}

int CChessBoard::getSameChessMaxNum(const CPoint &pos, const CChess::E_ChessType &eChessType
                                 , const CPlaneVector &planeVector, int nStartEndDistance)
{
    int nMaxNum = 0;
    CPoint posHead;

    for (int i = nStartEndDistance - 1; i > -1; --i)
    {
        posHead = pos - planeVector * i;
        if (isInvaildAt(posHead))
        {
            continue;
        }
        int nNum = getSameChessNum(posHead, eChessType, planeVector, nStartEndDistance);
        if (nNum > nMaxNum)
        {
            nMaxNum = nNum;
        }
    }
    return nMaxNum;
}

int CChessBoard::getSameChessNum(const CPoint &posHead, const CChess::E_ChessType &eChessType
                                 , const CPlaneVector &planeVector
                                 , int nStartEndDistance, bool bIgnoreOpponent) const
{
    int nNum = 0;
    CPoint pos = posHead;
    for (int i = 0; i < nStartEndDistance; ++i)
    {
        pos = pos + planeVector;
        if (isInvaildAt(pos))
        {
            return 0;
        }
        if (chessTypeAt(pos) == CChess::E_Empty)
        {
            continue;
        }
        if (chessTypeAt(pos) != eChessType)
        {
            if (bIgnoreOpponent)
            {
                continue;
            }
            else
            {
                return 0;
            }
        }
        ++nNum;
    }
    return nNum;
}
