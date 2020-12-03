#ifndef CCHESSBOARD_H
#define CCHESSBOARD_H

#include "Chess.h"
#include <stack>

using namespace std;

class CChessBoard
{
public:
    CChessBoard(int nWidth = 15, int nHeight = 15);

    // 落子
    void setChess(const CChess & chess);

    // 悔棋
    void takeBackChess(int nStep = 2);

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
