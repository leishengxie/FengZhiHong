#ifndef CGOBANGGAME_H
#define CGOBANGGAME_H
#include "Chess.h"


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

class CGobangGame
{
public:
    enum E_GameStatus
    {
        EG_Ready,
        EG_Playing,
        EG_Over
    };

    CGobangGame();




    void start();
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
};

#endif // CGOBANGGAME_H
