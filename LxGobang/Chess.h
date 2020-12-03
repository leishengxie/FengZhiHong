#ifndef CCHESS_H
#define CCHESS_H

// piece
class CChess
{

    public:

    // 棋子类型
    enum
    {
        E_Empty,
        E_Black,
        E_White
    };


    CChess();

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
    int m_nChessType;
    int m_nPosX;
    int m_nPosY;

};

#endif // CCHESS_H
