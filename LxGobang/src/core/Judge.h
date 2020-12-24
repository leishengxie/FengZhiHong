#ifndef CJUDGE_H
#define CJUDGE_H

class CPlayer;
class CGobangGame;
class CChessBoard;

///
/// \brief The CJudge class 裁判类，协调玩家的行为, 控制游戏进度等
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

    CPlayer* preWinner() const
    {
        return m_pPreWinner;
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

    // 判断是否已经有玩家可以胜出
    CPlayer* judgeHasAlreadyAbleWon();

    void notifyGameOver();

private:
    CJudge();
    static CJudge* s_pJydge;

private:

    CPlayer* m_pPlayer1;    //p1
    CPlayer* m_pPlayer2;    //p2
    CGobangGame* m_pGobangGame;
    CChessBoard* m_pChessBoard;

    CPlayer* m_pPreWinner;  //上一局赢的玩家
    // 当前等待执行落子的玩家，〖轮走方〗即“行棋方”,即本轮活动玩家current round active player
    CPlayer* m_pActivePlayer;
};

#endif // CJUDGE_H
