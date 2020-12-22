#ifndef CCHESSBOARD_H
#define CCHESSBOARD_H

#include "Chess.h"
#include "ChessGroup.h"

#include <stack>
#include <vector>

#define DEFUALT_SIDE    15

using namespace std;


class CChessBoard
{
public:
    CChessBoard(int nWidth = 15, int nHeight = 15);

    // 初始化
    void init();

    // 落子
    void setChess(const CChess & chess);

    // 悔棋
    void takeBackChess(int nStep = 2);

    int chessBoardWidth() const
    {
        return m_nWidth;
    }

    int chessBoardHeight() const
    {
        return m_nHeight;
    }

    CChess::E_ChessType chessTypeAt(int x, int y) const;
    CChess::E_ChessType chessTypeAt(const CPoint & pos) const;

    void reset();

    // 判断位置是否无效
    bool isInvaildAt(const CPoint & pos) const;
    bool isInvaildAt(int x, int y) const;
    bool isEmptyAt(const CPoint & pos) const;
    bool isEmptyAt(int x, int y) const;

    // 棋型判定
    bool hasBecome_5(CChess::E_ChessType eChessType);
    bool hasBecome_5(CChess::E_ChessType eChessType, int x, int y);
    bool hasBecome_5(CChess::E_ChessType eChessType, const CPoint & pos);

    // 在某方向向量上 包含某位置且 起止点相距距离(默认颗数5)范围内 出现某颜色的棋子的最多的棋型
    CChessGroup getBestGroup(const CPoint & pos, const CChess::E_ChessType & eChessType
                             , const CPlaneVector & planeVector, int nStartEndDistance = 5) const;



    // 在某方向向量上 包含某棋子且 起止点相距距离(默认颗数5)范围内 出现与该棋同色的最多有多少颗
    int getSameChessMaxNum(const CChess & chess, const CPlaneVector & planeVector, int nStartEndDistance = 5);

    // 在某方向向量上 包含某位置且 起止点相距距离(默认颗数5)范围内 出现某颜色的棋子的最多有多少颗
    int getSameChessMaxNum(const CPoint & pos, const CChess::E_ChessType & eChessType
                        , const CPlaneVector & planeVector, int nStartEndDistance = 5);

    // 在某方向向量上 以某位置为起止，到终点相距距离(默认颗数5)范围内 出现某颜色的棋子的有多少颗
    //, bIgnoreOpponent是否忽略对手的堵棋，即死四，死三，死二
    int getSameChessNum(const CPoint & posStart, const CChess::E_ChessType & eChessType
                        , const CPlaneVector & planeVector
                        , int nStartEndDistance = 5, bool bIgnoreOpponent = false) const;




private:
    // 棋盘大小
    int m_nWidth;
    int m_nHeight;

    // 棋子分布
    int **m_pChessMap;

    // 落子顺序记录
    stack<CChess> m_stackChessRecord;



};

#endif // CCHESSBOARD_H
