#ifndef CCHESS_H
#define CCHESS_H

#define TOTAL_BLACK_CHESS   113
#define TOTAL_WHITE_CHESS   112

#include <QPoint>
QPoint p;

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


private:
    int m_nX;
    int m_nY;
};



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
        return m_pos.x();
    }

    int y() const
    {
        return m_pos.y();
    }

    int type() const
    {
        return m_nChessType;
    }

private:
    CPoint m_pos;
    int m_nChessType;

};

/// 0-空位 1-己方 2-边缘或对方
// 五连，五枚同色棋子在一条线上邻接连串。11111
// 长连,五枚以上同色棋子在一条线上邻接成串 111111
// 成五,五连和长连的统称
//〖威胁〗下一手可以成五或者活四的点。

//〖四〗五连去掉1子的棋型。 //在一条阳线或阴线上连续相邻的5个点上只有四枚同色棋子的棋型。
// 活四, two head, 有两个威胁的四    011110
// 冲四, one head, middle,只有一个威胁的四    011112  10111 11011
// 死四, 不能成五的四   211112

//〖三〗可以形成四再形成五的三枚同色棋子组成的棋型。 //在一条阳线或阴线上连续相邻的5个点上只有三枚同色棋子的棋型。
// 〖活三〗再走一着可以形成活四的三
//〖连活三〗（同色棋子在一条阳线或阴线上相邻成一排的活三）。简称“连三”。    0011100(2个威胁) 0011102(1个威胁)
//〖跳活三〗中间夹有一个威胁的活三。简称“跳三”。  010110

// 眠三,再走一着可以形成冲四的三  211100  210110 201110
// 死三, 不能成五的三

//〖二〗可以形成三、四直至五的两枚同色棋子组成的棋型。 //在一条阳线或阴线上连续相邻的5个点上只有两枚同色棋子的棋型。
//〖活二〗再走一着可以形成活三的二。
//〖连活二〗连的活二。简称“连二”。 011000  001100
//〖跳活二〗中间隔有一个空点的活二。简称“跳二”。  010100
//〖大跳活二〗中间隔有两个空点的活二。简称“大跳二”。010010
//〖眠二〗再走一着可以形成眠三的二。 211000 201100  200110...
//〖死二〗不能成五的二。

// 单向组合棋型
enum E_ChessGroupType
{
    EC_B5,  // 成五
    EC_L4,  // 活四
    EC_S4,  // 冲四
    EC_L3,  // 活三
    EC_S3,  // 呡三
    EC_L2,
    EC_S2
};

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

// Q:词义辨析：menace和threat都做名词时的区别
// A:按字典中的解释，menace主要指“（有威胁的）人或事物，包括态度、腔调、气氛、语言及行为”；threat主要指“（有威胁的）状态”
///
/// \brief The CChessGroup class    对空位所形成的多向组合棋型
///
class CChessGroups
{
    CChessGroups(){}
    CChessGroups(const CPoint & pos)
        : m_posEmpty(pos)
    {

    }
private:
    CPoint m_posEmpty;  // 需要分析的空位
    E_ChessGroupType arrChessGroupType[EV_VectorDirectionMax];  //  空位在四个方向形成的棋型
    //int arrMenace[EV_VectorDirectionMax];   // 空位在四个方向形成的威胁；对于活四有2个威胁，冲四只有一个，活三的话有可能有1个也有可能有2个。其他情况不形成威胁。
};

#endif // CCHESS_H
