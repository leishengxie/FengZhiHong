#include "GobangGame.h"

CGobangGame::CGobangGame()
{

}

void CGobangGame::start()
{
    m_eGameStatus = EG_Playing;
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
