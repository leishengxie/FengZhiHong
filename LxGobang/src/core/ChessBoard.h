#ifndef CCHESSBOARD_H
#define CCHESSBOARD_H

#include "Chess.h"
#include <stack>

#define DEFUALT_SIDE    15

using namespace std;


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

    // 棋型分析
    //bool

    // 获取棋子在某方向上连续出现同色有多少颗
    int getChessNum(const CChess & chess, const CPlaneVector & planeVector);

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