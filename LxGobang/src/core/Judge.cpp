#include "Judge.h"

#include "Player.h"
#include "GobangGame.h"
#include"ChessBoard.h"

CJudge *CJudge::s_pJydge = nullptr;
CJudge *CJudge::getInstance()
{
    if(s_pJydge == nullptr)
    {
        s_pJydge = new CJudge;
    }
    return s_pJydge;
}

void CJudge::setPlayers(CPlayer *p1, CPlayer *p2)
{
    m_pPlayer1 = p1;
    m_pPlayer2 = p2;
    m_pActivePlayer = judgeOnTheOffensive();

}

bool CJudge::isHavenotBegunYet()
{
    return !m_pGobangGame->isPlaying();
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



void CJudge::onEventGameStart()
{
    m_pGobangGame->onGameStart();
}

void CJudge::onEventInOnesTurn()
{
    m_pGobangGame->onGameInOnesTurn();
}

void CJudge::onEventSetChessDone()
{
    bool bHasBecome5 = m_pChessBoard->hasBecome5Mothod_2(m_pActivePlayer->choosedChessType());
    if (bHasBecome5)
    {
        onEventGameOver();
        return;
    }
    switchActivePlayer();
}

void CJudge::onEventGameOver()
{
    m_pGobangGame->onGameOver();
}

CJudge::CJudge()
    : m_pPlayer1(nullptr)
    , m_pPlayer2(nullptr)
    , m_pPreWinner(nullptr)
    , m_pActivePlayer(nullptr)
{

}
