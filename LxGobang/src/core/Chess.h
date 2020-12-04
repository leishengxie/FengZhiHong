#ifndef CCHESS_H
#define CCHESS_H

#define TOTAL_BLACK_CHESS   113
#define TOTAL_WHITE_CHESS   112

// piece
class CChess
{

    public:

    // 棋子类型
    enum E_ChessType
    {
        E_Empty,
        E_Black,
        E_White
    };


    CChess();
    CChess(int x, int y, E_ChessType eChessType);

    int x() const
    {
        return m_nPosX;
    }

    int y() const
    {
        return m_nPosY;
    }

    int type() const
    {
        return m_nChessType;
    }

private:
    int m_nPosX;
    int m_nPosY;
    int m_nChessType;

};

#endif // CCHESS_H
