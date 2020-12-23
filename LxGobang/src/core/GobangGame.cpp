#include "GobangGame.h"

#include "ChessBoard.h"
#include "Player.h"
#include "Judge.h"

CGobangGame::CGobangGame(CChessBoard *pChessBoard, CPlayer *p1, CPlayer *p2)
    : m_pChessBoard(pChessBoard)
    , m_pPlayer1(p1)
    , m_pPlayer2(p2)
{
    //m_pJudge = new
}

void CGobangGame::start()
{
    m_pChessBoard->reset();
    m_pPlayer1->reset();
    m_pPlayer2->reset();

    CPlayer *player = m_pJudge->judgeOnTheOffensive();
    m_pJudge->setActivePlayer(player);

    m_eGameStatus = EG_Playing;

}

void CGobangGame::playing()
{
    CPlayer *player = m_pJudge->activePlayer();
    if(player->isRobot())
    {
        CPoint pos = player->think();
        player->moveInChess(pos);
        m_pJudge->switchActivePlayer();
    }
}

void CGobangGame::over()
{
    m_eGameStatus = EG_Over;
}

bool CGobangGame::isPlaying()
{
    return m_eGameStatus == EG_Playing;
}

bool CGobangGame::isGameOver()
{
    return m_eGameStatus == EG_Over;
}
