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




    void start();
    void playing(); // 加入游戏调度
    void over();
    bool isPlaying();
    bool isGameOver();




    // 游戏定时器调用函数，具体如何调度，需要派生类自己去实现
    void onTimeout();
    void setSpeed(int ms);

protected:
    // 派生类实现接口
    virtual void drawBoard() = 0;
    virtual void drawChesses() = 0;

private:
    E_GameStatus m_eGameStatus;

    CChessBoard* m_pChessBoard;
    CJudge* m_pJudge;
    CPlayer* m_pPlayer1;    //p1
    CPlayer* m_pPlayer2;    //p2
};

#endif // CGOBANGGAME_H
