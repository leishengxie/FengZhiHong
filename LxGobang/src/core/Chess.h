#ifndef CCHESS_H
#define CCHESS_H

#define TOTAL_BLACK_CHESS   113
#define TOTAL_WHITE_CHESS   112



enum E_VectorDirection
{
    EV_Horizontal,  // 阳线
    EV_Vertical,  // 阳线
    EV_Backlas, // \----backlas反斜杠方向,阴线
    EV_Slash,    // /----slash 正斜线,阴线
    EV_VectorDirectionMax
};


// 定义平面向量
class CPlaneVector
{
public:
    CPlaneVector()
        : m_nX(0)
        , m_nY(0)
    {

    }
    CPlaneVector(int x, int y)
        : m_nX(x)
        , m_nY(y)
    {

    }

    int x() const
    {
        return m_nX;
    }

    int y() const
    {
        return m_nY;
    }

    friend inline const CPlaneVector operator*(const CPlaneVector &, int);
    friend inline const CPlaneVector operator*(int, const CPlaneVector &);

    static CPlaneVector getUnitVector(E_VectorDirection eVectorDirection);

    // 横向x轴正方向的单位向量
    static CPlaneVector hUintVector()
    {
        static CPlaneVector uintVector(1, 0);
        return uintVector;
    }

    static CPlaneVector vUintVector()
    {
        static CPlaneVector uintVector(0, 1);
        return uintVector;
    }

    // \----backlas反斜杠方向
    static CPlaneVector bUintVector()
    {
        static CPlaneVector uintVector(1, 1);
        return uintVector;
    }

    // /----slash 正斜线
    static CPlaneVector sUintVector()
    {
        static CPlaneVector uintVector(-1, 1);
        return uintVector;
    }

private:
    int m_nX;
    int m_nY;
};

inline const CPlaneVector operator*(const CPlaneVector &p, int factor)
{ return CPlaneVector(p.m_nX*factor, p.m_nY*factor); }


inline const CPlaneVector operator*(int factor, const CPlaneVector &p)
{ return CPlaneVector(p.m_nX*factor, p.m_nY*factor); }



class CPoint
{
public:
    CPoint(int nX = -1, int nY = -1)
        : m_nX(nX)
        , m_nY(nY)
    {

    }

    int x() const
    {
        return m_nX;
    }

    int y() const
    {
        return m_nY;
    }

    void setX(int nX)
    {
        m_nX = nX;
    }

    void setY(int nY)
    {
        m_nY = nY;
    }

    friend inline const CPoint operator+(const CPoint &, const CPoint &);
    friend inline const CPoint operator-(const CPoint &, const CPoint &);
    friend inline const CPoint operator*(const CPoint &, int);
    friend inline const CPoint operator*(int, const CPoint &);

    CPoint operator+(const CPlaneVector & planeVector) const
    {
        return CPoint(x() + planeVector.x(), y() + planeVector.y());
    }
    CPoint operator-(const CPlaneVector & planeVector) const
    {
        return CPoint(x() - planeVector.x(), y() - planeVector.y());
    }

private:
    int m_nX;
    int m_nY;
};

inline const CPoint operator+(const CPoint &p1, const CPoint &p2)
{ return CPoint(p1.x()+p2.x(), p1.y()+p2.y()); }

inline const CPoint operator-(const CPoint &p1, const CPoint &p2)
{ return CPoint(p1.x()-p2.x(), p1.y()-p2.y()); }

inline const CPoint operator*(const CPoint &p, int factor)
{ return CPoint(p.m_nX*factor, p.m_nY*factor); }


inline const CPoint operator*(int factor, const CPoint &p)
{ return CPoint(p.m_nX*factor, p.m_nY*factor); }




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
    CChess(int x, int y, const E_ChessType & eChessType);

    int x() const
    {
        return m_pos.x();
    }

    int y() const
    {
        return m_pos.y();
    }

    CPoint pos()const
    {
        return m_pos;
    }

    E_ChessType type() const
    {
        return m_eChessType;
    }

private:
    CPoint m_pos;
    E_ChessType m_eChessType;

};



#endif // CCHESS_H
