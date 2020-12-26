#include "GobangGame.h"

#include "ChessBoard.h"
#include "Player.h"
#include "Judge.h"

CGobangGame::CGobangGame(CChessBoard *pChessBoard, CPlayer *p1, CPlayer *p2)
    : m_eGameStatus(EG_Ready)
    , m_pChessBoard(pChessBoard)
    , m_pPlayer1(p1)
    , m_pPlayer2(p2)
{
    m_pPlayer1->setChessBoard(m_pChessBoard);
    m_pPlayer2->setChessBoard(m_pChessBoard);
    CJudge::getInstance()->setPlayers(m_pPlayer1, m_pPlayer2);
    CJudge::getInstance()->setChessBoard(m_pChessBoard);
    CJudge::getInstance()->setGame(this);
}

void CGobangGame::onGameStart()
{
    m_eGameStatus = EG_Playing;

}

void CGobangGame::onGameInOnesTurn()
{
    CPlayer *player = CJudge::getInstance()->activePlayer();
    if(player->isRobot())
    {
        CPoint pos = player->think();
        player->moveInChess(pos);
        CJudge::getInstance()->onEventSetChessDone();
    }
}

void CGobangGame::played()
{

}

void CGobangGame::onGameOver()
{
    m_eGameStatus = EG_Over;
}

void CGobangGame::onGameRestart()
{

}

bool CGobangGame::isReading()
{
    return m_eGameStatus == EG_Ready;
}

bool CGobangGame::isPlaying()
{
    return m_eGameStatus == EG_Playing;
}

bool CGobangGame::isGameOver()
{
    return m_eGameStatus == EG_Over;
}
