#ifndef CPLAYER_H
#define CPLAYER_H

#include "Chess.h"
class CChessBoard;
class CGobangAI;

class CPlayer
{
public:
    CPlayer();

    void init();

    // 选棋子类型
    void setChoosedChessType(const CChess::E_ChessType &eChessType);
    CChess::E_ChessType choosedChessType()
    {
        return m_eChessTypeChoosed;
    }

    // 下棋落子
    void moveInChess(int x, int y);
    void moveInChess(const CPoint & pos);

    // 请求悔棋
    void reqTakeBackChess();

    void reset();

public:
    virtual bool isRobot() = 0;
    virtual CPoint think(){return CPoint();}

protected:
    // 选择的棋子类型(黑棋或白棋)
    CChess::E_ChessType m_eChessTypeChoosed;

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
    CRobotPlayer();
    ~CRobotPlayer();
    bool isRobot() override{return true;}
    CPoint think() override;

private:
    CGobangAI* m_pAI;
};

#endif // CPLAYER_H
