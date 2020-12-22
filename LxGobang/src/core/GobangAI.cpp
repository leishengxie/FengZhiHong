#include "GobangAI.h"



CGobangAI::CGobangAI(CPlayer* pPlayer)
{

}

/*
 * 思路
 * 1.分别对黑白棋分析所有空位置能形成的棋型并记录下来形成 棋型列表
 * 2.分析进攻还是防守
 * 1)自己棋型列表有没有成五的威胁(活四，冲四) > 对方棋型列表有没有成五的威胁(活四，冲四) //己方冲四的分数应大于对方活四的分数*4
 * 2)> 自己棋型列表有没有活四的威胁(活三) > 对方棋型列表有没有活四的威胁(活三) ---(以上只要单方向存在即可)
 * 3)> 自己棋型列表有没有多方向形成(眠三，活二的任意组合) > 对方棋型列表有没有多方向形成(眠三，活二的任意组合)    --(如冲四冲四，冲四活三，双活三）
 * 4)> 自己棋型列表单个棋型多方向形成的总分 > 对方棋型列表单个棋型多方向形成的总分
 * 以上实际上可以总结为第四步 这样的话，活三的分数应大于眠三*4(4个方向)或活二*4
 * 3.得到上述的棋型填充到分数map中，得到最大分数的pos落子
 */
void CGobangAI::think(const CChessBoard *pChessBoard)
{
    for (int x = 0; x < pChessBoard->chessBoardWidth(); ++x)
    {
        for (int y = 0; y < pChessBoard->chessBoardHeight(); ++y)
        {
            if (pChessBoard->chessTypeAt(x, y) != CChess::E_Empty)
            {
                continue;
            }

            CEmptyPosComplexChessGroup complexGroupsForBlack(CPoint(x, y), CChess::E_Black);
            complexGroupsForBlack.analyse(pChessBoard);
            m_vecChessGroupBlack.push_back(complexGroupsForBlack);

            CEmptyPosComplexChessGroup complexGroupsForWhite(CPoint(x, y), CChess::E_White);
            complexGroupsForWhite.analyse(pChessBoard);
            m_vecChessGroupWhite.push_back(complexGroupsForWhite);
        }
    }

    int nMaxScoreBlack = 0;
    int nMaxScoreWhite = 0;
}
