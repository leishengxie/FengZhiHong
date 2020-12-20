#include "Judge.h"

#include "Player.h"

CJudge::CJudge()
    : m_pPreWinner(nullptr)
{

}

void CJudge::switchActivePlayer()
{
    if (m_pActivePlayer == m_pPlayer1)
    {
        m_pActivePlayer = m_pPlayer2;
    }
    else
    {
        m_pActivePlayer = m_pPlayer1;
    }
}

CPlayer *CJudge::judgeOnTheOffensive()
{
    CPlayer* pOnTheOffensive;
    CPlayer* pSecond;
    // 如果是第一局默认玩家先手
    if (m_pPreWinner == nullptr)
    {
        if(m_pPlayer1->isRobot())
        {
            pOnTheOffensive = m_pPlayer2;
            pSecond = m_pPlayer1;
        }
        else
        {
            pOnTheOffensive = m_pPlayer1;
            pSecond = m_pPlayer2;
        }
    }
    else
    {
        if(m_pPreWinner == m_pPlayer1)
        {
            pOnTheOffensive = m_pPlayer1;
            pSecond = m_pPlayer2;
        }
        else
        {
            pOnTheOffensive = m_pPlayer2;
            pSecond = m_pPlayer1;
        }
    }
    pOnTheOffensive->setChoosedChessType(CChess::E_Black);
    pSecond->setChoosedChessType(CChess::E_White);
    return pOnTheOffensive;
}
