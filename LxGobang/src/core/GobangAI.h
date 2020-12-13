#ifndef CGOBANGAI_H
#define CGOBANGAI_H
/*
 * 思路
 * 1.分别对黑白棋分析所有空位置能形成的棋型并记录下来形成 棋型列表
 * 2.分析进攻还是防守
 * 1)自己棋型列表有没有成五的威胁(活四，冲四) > 对方棋型列表有没有成五的威胁(活四，冲四)
 * 2)> 自己棋型列表有没有活四的威胁(活三) > 对方棋型列表有没有活四的威胁(活三) ---(以上只要单方向存在即可)
 * 3)> 自己棋型列表有没有多方向形成(眠三，活二的任意组合) > 对方棋型列表有没有多方向形成(眠三，活二的任意组合)    --(如冲四冲四，冲四活三，双活三）
 * 4)> 自己棋型列表单个棋型多方向形成的总分 > 对方棋型列表单个棋型多方向形成的总分
 * 以上实际上可以总结为第四步 这样的话，活三的分数应大于眠三*4(4个方向)或活二*4
 * 3.得到上述的该棋型，落子
 */

/****************************************
 * 其他的一些算法
//博弈树 game tree // 让Ai考虑多步
//极大极小值搜索算法
//评估函数 evaluate function
//Alpha-Beta剪枝算法
*****************************************/

#include "ChessBoard.h"

///
/// \brief The CGobangAI class 简单的Ai，未涉及算法，仅考虑当前步
///
///
///
class CGobangAI
{
public:
    CGobangAI();

    friend class CChessBoard;

    void think();
private:
    int **m_pScoreMap;
    int m_nSelfTotalScore;
    int m_nOpponentTotalScore;  // 对手总分
};

#endif // CGOBANGAI_H
