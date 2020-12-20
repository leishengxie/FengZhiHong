#ifndef CGOBANGAI_H
#define CGOBANGAI_H


/****************************************
 * 其他的一些算法
//博弈树 game tree // 让Ai考虑多步
//极大极小值搜索算法
//评估函数 evaluate function
//Alpha-Beta剪枝算法
*****************************************/

#include "ChessBoard.h"
class CPlayer;

///
/// \brief The CGobangAI class 简单的Ai，未涉及算法，仅考虑当前步
///
///
///
class CGobangAI
{
public:
    CGobangAI(CPlayer* pPlayer);


    void think();
private:
    CPlayer* m_pPlayer;
    vector<CEmptyPosChessGroups> m_vecChessGroupBlack;
    vector<CEmptyPosChessGroups> m_vecChessGroupWhite;
    int **m_pScoreMap;
};

#endif // CGOBANGAI_H
