#ifndef CPLAYER_H
#define CPLAYER_H

#include "Chess.h"
class CChessBoard;

class CPlayer
{
public:
    CPlayer();

    void init();

    // 选棋子类型
    void chooseChessType(int nChoosedChessType);

    // 下棋落子
    void moveInChess(int x, int y);

    // 请求悔棋
    void reqTakeBackChess();

    void reset();

public:
    virtual bool isRobot() = 0;
    virtual CChess think(){return CChess();}

protected:
    // 选择的棋子类型(黑棋或白棋)
    int m_nChoosedChessType;

    int m_nSurplusChessNum;



    // 棋盘指针
    CChessBoard* m_pChessBoard;


};

class CHumanPlayer : public CPlayer
{

public:
    bool isRobot() override{return false;}
};


class CRobotPlayer : public CPlayer
{
public:
    bool isRobot() override{return true;}
    CChess think() override;
};

#endif // CPLAYER_H
