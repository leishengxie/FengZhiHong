#include "ChessBoard.h"

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
