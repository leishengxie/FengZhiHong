#ifndef CGOBANGGAME_H
#define CGOBANGGAME_H

#include "Chess.h"

class CChessBoard;
class CJudge;
class CPlayer;


////////////////////////////////////////////////////////////////////
//   评分标准：
//             成5：                  100000
//             活4、双死4、死4活3：   10000
//             双活3、活3双活2：      5000
//             活3死3：               1000
//             死4：                  500
//             单活3：                200
//             双活2：                100
//             双死3：                50
//             单活2：                10
//             单死3：                 5
////////////////////////////////////////////////////////////////////

//class CGameStep
//{
//    CChess chess;
//};


///
/// \brief The CGobangGame class 游戏类，包含游戏所有玩家和道具
///
class CGobangGame
{
public:
    enum E_GameStatus
    {
        EG_Ready,
        EG_Playing,
        EG_Over
    };

    CGobangGame(CChessBoard* pChessBoard, CPlayer* p1, CPlayer* p2);


    virtual void onGameStart();

    // in one's turn 轮到某人下棋了
    virtual void onGameInOnesTurn();

    virtual void played();
    virtual void onGameOver();
    virtual void onGameRestart();

    bool isReading();
    bool isPlaying();
    bool isGameOver();




    // 游戏定时器调用函数，具体如何调度，需要派生类自己去实现
    void onTimeout();
    void setSpeed(int ms);



protected:
    E_GameStatus m_eGameStatus;

    CChessBoard* m_pChessBoard;

    CPlayer* m_pPlayer1;    //p1
    CPlayer* m_pPlayer2;    //p2
};

#endif // CGOBANGGAME_H
