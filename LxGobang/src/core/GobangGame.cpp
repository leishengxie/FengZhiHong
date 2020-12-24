#include "GobangGame.h"

#include "ChessBoard.h"
#include "Player.h"
#include "Judge.h"

CGobangGame::CGobangGame(CChessBoard *pChessBoard, CPlayer *p1, CPlayer *p2)
    : m_pChessBoard(pChessBoard)
    , m_pPlayer1(p1)
    , m_pPlayer2(p2)
{

}

void CGobangGame::start()
{
    m_pChessBoard->reset();
    m_pPlayer1->reset();
    m_pPlayer2->reset();
    m_pPlayer1->setChessBoard(m_pChessBoard);
    m_pPlayer2->setChessBoard(m_pChessBoard);
    m_eGameStatus = EG_Playing;
    CJudge::getInstance()->setPlayers(m_pPlayer1, m_pPlayer2);
    CJudge::getInstance()->setChessBoard(m_pChessBoard)
    CJudge::getInstance()->setGame(this);
}

void CGobangGame::playing()
{
    CPlayer *player = CJudge::getInstance()->activePlayer();
    if(player->isRobot())
    {
        CPoint pos = player->think();
        player->moveInChess(pos);
        CJudge::getInstance()->switchActivePlayer();
    }
}

void CGobangGame::played()
{

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
