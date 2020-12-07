#ifndef CJUDGE_H
#define CJUDGE_H

class CPlayer;

///
/// \brief The CJudge class 裁判类，协调玩家的行为
///
class CJudge
{
public:
    CJudge();

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

private:

    CPlayer* m_pPlayer1;    //p1
    CPlayer* m_pPlayer2;    //p2

    CPlayer* m_pPreWinner;  //上一局赢的玩家
    // 当前等待执行落子的玩家，〖轮走方〗即“行棋方”,即本轮活动玩家current round active player
    CPlayer* m_pActivePlayer;
};

#endif // CJUDGE_H
