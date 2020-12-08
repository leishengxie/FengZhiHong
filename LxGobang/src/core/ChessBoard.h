#ifndef CCHESSBOARD_H
#define CCHESSBOARD_H

#include "Chess.h"
#include <stack>

#define DEFUALT_SIDE    15

using namespace std;

// 定义平面向量
class CPlaneVector
{
    CPlaneVector(int x, int y)
        : m_nX(x)
        , m_nY(y)
    {

    }

    int x() const
    {
        return m_nX;
    }

    int y() const
    {
        return m_nY;
    }

private:
    int m_nX;
    int m_nY;
};

class CChessBoard
{
public:
    CChessBoard(int nWidth = 15, int nHeight = 15);

    // 初始化
    void init();

    // 落子
    void setChess(int x, int y, CChess::E_ChessType eChessType);
    void setChess(const CChess & chess);

    // 悔棋
    void takeBackChess(int nStep = 2);

    int chessBoardWidth() const
    {
        return m_nWidth;
    }

    int chessBoardHeight() const
    {
        return m_nHeight;
    }

    CChess::E_ChessType chessType(int x, int y);

    void reset();


    // 棋型判定
    bool hasBecome_5(CChess::E_ChessType eChessType);
    bool hasBecome_5(CChess::E_ChessType eChessType, int x, int y);

private:
    // 棋盘大小
    int m_nWidth;
    int m_nHeight;

    // 棋子分布
    int **m_pChessMap;

    // 落子顺序记录
    stack<CChess> m_stackChessRecord;


};

#endif // CCHESSBOARD_H
