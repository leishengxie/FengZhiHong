#ifndef CCHESSGROUP_H
#define CCHESSGROUP_H

#include "Chess.h"
#include <map>

//#include <QPoint>
//#include <QVector>
//#include <QRect>
//QPoint p;
//QRect r;
//QVector<int> v;



// 棋型类型
enum E_ChessGroupType
{
    EC_B5,  // 成五
    EC_L4,  // 活四
    EC_S4,  // 冲四
    EC_L3,  // 活三
    EC_S3,  // 呡三
    EC_L2,
    EC_S2,
    EC_Single,
    EC_Empty
};


class CChessBoard;

///
/// \brief The CChessGroup class 棋型类
///
class CChessGroup
{
public:
    CChessGroup();
    CChessGroup(const CPoint & pos, const CPlaneVector & planeVector, const CChess::E_ChessType & eChessType);

    void setHeadPoint(const CPoint & pos)
    {
        m_posHead = pos;
    }
    CPoint headPos() const
    {
        return m_posHead;
    }

    void setPlaneVector(const CPlaneVector & planeVector)
    {
        m_planeVector = planeVector;
    }
    CPlaneVector planeVector() const
    {
        return m_planeVector;
    }

    void setChessType(const CChess::E_ChessType & eChessType)
    {
        m_eChessType = eChessType;
    }
    CChess::E_ChessType chessType() const
    {
        return m_eChessType;
    }

    void analyse(const CChessBoard* pChessBoard);

    // 判断时候是活x
    bool isLiveGroup(const CChessBoard* pChessBoard);

    int score(const CChess::E_ChessType & eChessType);
    static int score(E_ChessGroupType eChessGroupType, bool bSelf);

    //E_ChessGroupType chessGroupType();

private:
    /// 属性成员
    // 棋型的开头位置，可以是空位
    CPoint m_posHead;

    // 棋型的方向向量
    CPlaneVector m_planeVector;

    // 正在观察的棋型颜色
    CChess::E_ChessType m_eChessType;

    //
    //std::map<int, >

    /// 分析结果
    E_ChessGroupType m_eChessGroupType;

    // 组成棋型的有效数目
    //int m_nNum;
};



// Q:词义辨析：menace和threat都做名词时的区别
// A:按字典中的解释，menace主要指“（有威胁的）人或事物，包括态度、腔调、气氛、语言及行为”；threat主要指“（有威胁的）状态”
///
/// \brief The CEmptyPosComplexChessGroup class 空位复合棋型
///
class CEmptyPosComplexChessGroup
{
public:
    CEmptyPosComplexChessGroup();
    CEmptyPosComplexChessGroup(const CPoint & pos, const CChess::E_ChessType & eChessType);

    CPoint pos() const
    {
        return m_posEmpty;
    }

    bool isInvaild(const CChessBoard* pChessBoard) const;
//    void setGroup(const E_VectorDirection & eVectorDirection, const CChessGroup & chessGroup)
//    {
//        arrChessGroup[eVectorDirection] = chessGroup;
//    }

    void analyse(const CChessBoard* pChessBoard);

    int score(const CChess::E_ChessType & eChessType);

private:
    CPoint m_posEmpty;  // 需要分析的空位

    CChess::E_ChessType m_eChessType;    // 需要分析的棋子类别watch type

    /// 分析的结果
    CChessGroup m_arrChessGroup[EV_VectorDirectionMax];  //  空位在四个方向形成的最佳棋型
    //int arrMenace[EV_VectorDirectionMax];   // 空位在四个方向形成的威胁；对于活四有2个威胁，冲四只有一个，活三的话有可能有1个也有可能有2个。其他情况不形成威胁。
};

#endif // CCHESSGROUP_H
