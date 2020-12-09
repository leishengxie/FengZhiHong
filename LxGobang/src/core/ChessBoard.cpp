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

void CChessBoard::setChess(int x, int y, CChess::E_ChessType eChessType)
{
    setChess(CChess(x, y, eChessType));
}

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

CChess::E_ChessType CChessBoard::chessType(int x, int y)
{

    return CChess::E_ChessType(m_pChessMap[x][y]);
}

void CChessBoard::reset()
{
    init();
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
