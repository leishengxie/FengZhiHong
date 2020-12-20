#include "GobangAI.h"

#define SCORE_LINE_5      10000
#define SCORE_LINE_LONG   10000
#define SCORE_BECOME_5    10000

#define SCORE_LIVE_4      1000
#define SCORE_SINGLE_4    600
#define SCORE_DEAD_4      0

#define SCORE_LIVE_3      100
#define SCORE_SLEEP_3     60
#define SCORE_DEAD_3      0

#define SCORE_LIVE_2      10
#define SCORE_SLEEP_2     6
#define SCORE_DEAD_2      0

#define SCORE_SELF_4    4000
#define SCORE_SELF_3    400
#define SCORE_SELF_2    40

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
void CGobangAI::think()
{

}
