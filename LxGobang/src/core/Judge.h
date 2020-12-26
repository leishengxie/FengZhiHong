#ifndef CJUDGE_H
#define CJUDGE_H

class CPlayer;
class CGobangGame;
class CChessBoard;

///
/// \brief The CJudge class 裁判类，协调玩家的行为, 控制游戏进度等control
///
class CJudge
{
public:
    static CJudge* getInstance();

    void setPlayers(CPlayer* p1, CPlayer* p2);
    void setGame(CGobangGame* pGobangGame)
    {
        m_pGobangGame = pGobangGame;
    }
    void setChessBoard(CChessBoard* pChessBoard)
    {
        m_pChessBoard = pChessBoard;
    }

    // 如果没有选手被认为还没有开始
    bool isHavenotBegunYet();

    CPlayer* winner() const
    {
        return m_pWinner;
    }

    void setActivePlayer(CPlayer* player)
    {
        m_pActivePlayer = player;
    }

    CPlayer* activePlayer() const
    {
        return m_pActivePlayer;
    }

    void switchActivePlayer();

    // 判断先手
    CPlayer* judgeOnTheOffensive();

    void onEventGameStart();
    void onEventInOnesTurn();
    void onEventSetChessDone();
    void onEventGameOver();
    void onEventGameRestart();

private:
    CJudge();
    static CJudge* s_pJydge;

private:

    CPlayer* m_pPlayer1;    //p1
    CPlayer* m_pPlayer2;    //p2
    CGobangGame* m_pGobangGame;
    CChessBoard* m_pChessBoard;

    CPlayer* m_pWinner;  //赢的玩家
    // 当前等待执行落子的玩家，〖轮走方〗即“行棋方”,即本轮活动玩家current round active player
    CPlayer* m_pActivePlayer;
};

#endif // CJUDGE_H
