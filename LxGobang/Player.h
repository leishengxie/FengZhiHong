#ifndef CPLAYER_H
#define CPLAYER_H

class CChessBoard;

class CPlayer
{
public:
    CPlayer();

    // 选棋子类型
    void chooseChessType(int nChoosedChessType)
    {
        m_nChoosedChessType = nChoosedChessType;
    }

    // 请求悔棋
    void reqTakeBackChess();


private:
    // 选择的棋子类型(黑棋或白棋)
    int m_nChoosedChessType;

    int m_nSurplusChessNum;



    // 棋盘指针
    CChessBoard* m_pChessBoard;


};

class CHumanPlayer : public CPlayer
{

};


class CRobotPlayer : public CPlayer
{

};

#endif // CPLAYER_H
