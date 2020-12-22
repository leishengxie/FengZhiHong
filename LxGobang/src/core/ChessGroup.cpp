#include "ChessGroup.h"

#include "ChessBoard.h"

/// 0-空位 1-己方 2-边缘或对方
// 五连，五枚同色棋子在一条线上邻接连串。11111
// 长连,五枚以上同色棋子在一条线上邻接成串 111111
// 成五,五连和长连的统称
//〖威胁〗下一手可以成五或者活四的点。

//〖四〗五连去掉1子的棋型。 //在一条阳线或阴线上连续相邻的5个点上只有四枚同色棋子的棋型。
// 活四, two head, 有两个威胁的四    011110  (6子去两头)
// 冲四, one head, middle,只有一个威胁的四    01111 11110(活四的一头空位去掉),  10111 11011 11101  (五子去一颗，即5-1)
// 死四, 不能成五的四   211112

//〖三〗可以形成四再形成五的三枚同色棋子组成的棋型。 //在一条阳线或阴线上连续相邻的5个点上只有三枚同色棋子的棋型。
// 〖活三〗再走一着可以形成活四的三 (6子去两头再去一颗)
//〖连活三〗（同色棋子在一条阳线或阴线上相邻成一排的活三）。简称“连三”。    0011100(2个威胁) 001110(1个威胁) 011100
//〖跳活三〗中间夹有一个威胁的活三。简称“跳三”。  010110 011010

// 眠三,再走一着可以形成冲四的三  11100 01110  00111 01011 10110 11010 01101(5-2)
// 死三, 不能成五的三

//〖二〗可以形成三、四直至五的两枚同色棋子组成的棋型。 //在一条阳线或阴线上连续相邻的5个点上只有两枚同色棋子的棋型。
//〖活二〗再走一着可以形成活三的二。(6子去两头再去2颗)
//〖连活二〗连的活二。简称“连二”。 011000  001100
//〖跳活二〗中间隔有一个空点的活二。简称“跳二”。  010100
//〖大跳活二〗中间隔有两个空点的活二。简称“大跳二”。010010
//〖眠二〗再走一着可以形成眠三的二。 (5-3)11000 01100  00110...
//〖死二〗不能成五的二。

#define SCORE_LINE_5      10000
#define SCORE_LINE_LONG   10000
#define SCORE_BECOME_5    10000

#define SCORE_LIVE_4      1000
#define SCORE_SINGLE_4    600
#define SCORE_DEAD_4      0

#define SCORE_LIVE_3      100
#define SCORE_SLEEP_3     60
#define SCORE_DEAD_3      0

#define SCORE_LIVE_2      10
#define SCORE_SLEEP_2     6
#define SCORE_DEAD_2      0

#define SCORE_SELF_4    4000
#define SCORE_SELF_3    400
#define SCORE_SELF_2    40

CChessGroup::CChessGroup()
{

}

CChessGroup::CChessGroup(const CPoint &pos, const CPlaneVector &planeVector, const CChess::E_ChessType &eChessType)
    : m_posHead(pos)
    , m_planeVector(planeVector)
    , m_eChessType(eChessType)
{

}
void CChessGroup::analyse(const CChessBoard *pChessBoard)
{
    int nNum = pChessBoard->getSameChessNum(m_posHead, m_eChessType, m_planeVector);
    if (nNum < 1)
    {
        m_eChessGroupType = EC_Empty;
        return;
    }

    bool bLiveGroup = isLiveGroup(pChessBoard);
    if (nNum == 5)
    {
        m_eChessGroupType = EC_B5;
    }
    else if (nNum == 4)
    {
        m_eChessGroupType = EC_S4;

        // 判断活四
        if(bLiveGroup)
        {
            m_eChessGroupType = EC_L4;
        }
    }
    else if (nNum == 3)
    {
        m_eChessGroupType = EC_S3;

        // 判断活四
        if(bLiveGroup)
        {
            m_eChessGroupType = EC_L3;
        }
    }
    else if (nNum == 2)
    {
        m_eChessGroupType = EC_S2;

        // 判断活四
        if(bLiveGroup)
        {
            m_eChessGroupType = EC_L2;
        }
    }
    else if (nNum == 1)
    {
        m_eChessGroupType = EC_Single;
    }

}

bool CChessGroup::isLiveGroup(const CChessBoard *pChessBoard)
{
    if (!pChessBoard->isInvaildAt(m_posHead - m_planeVector))
    {
        if(pChessBoard->isEmptyAt(m_posHead - m_planeVector)
           && pChessBoard->isEmptyAt(m_posHead + m_planeVector * 4))
        {
            return true;
        }
    }
    if(!pChessBoard->isInvaildAt(m_posHead + m_planeVector * 5))
    {
        if(pChessBoard->isEmptyAt(m_posHead)
           && pChessBoard->isEmptyAt(m_posHead + m_planeVector * 5))
        {
            return true;
        }
    }
    return false;
}

int CChessGroup::score(const CChess::E_ChessType &eChessType)
{
    return score(m_eChessGroupType, eChessType == m_eChessType);
}

int CChessGroup::score(E_ChessGroupType eChessGroupType, bool bSelf)
{
    int nScore = 0;
    int nExtraScore = 0;
	switch (eChessGroupType)
	{
	case EC_B5:
        nScore = SCORE_BECOME_5;
		break;
	case EC_L4:
        nScore = SCORE_LIVE_4;
        nExtraScore = bSelf ? SCORE_SELF_4 : 0;
		break;
	case EC_S4:
        nScore = SCORE_SINGLE_4;
        nExtraScore = bSelf ? SCORE_SELF_4 : 0;
		break;
	case EC_L3:
        nScore = SCORE_LIVE_3;
        nExtraScore = bSelf ? SCORE_SELF_3 : 0;
		break;
	case EC_S3:
        nScore = SCORE_SLEEP_3;
        nExtraScore = bSelf ? SCORE_SELF_3 : 0;
		break;
	case EC_L2:
        nScore = SCORE_LIVE_2;
        nExtraScore = bSelf ? SCORE_SELF_2 : 0;
		break;
	case EC_S2:
        nScore = SCORE_SLEEP_2;
        nExtraScore = bSelf ? SCORE_SELF_2 : 0;
		break;
	default:
		break;
	}
    return nScore + nExtraScore;
}



///
/// \brief CEmptyPosComplexChessGroup::analyse
/// \param pChessBoard
///
void CEmptyPosComplexChessGroup::analyse(const CChessBoard *pChessBoard)
{
    for (int i = 0; i < EV_VectorDirectionMax; ++i)
    {
        E_VectorDirection eVectorDirection = E_VectorDirection(i);
        CChessGroup group = pChessBoard->getBestGroup(m_posEmpty, m_eChessType
                                                      , CPlaneVector::getUnitVector(eVectorDirection));
        //setGroup(eVectorDirection, group);
        group.analyse(pChessBoard);
        m_arrChessGroup[eVectorDirection] = group;
    }
}

int CEmptyPosComplexChessGroup::score(const CChess::E_ChessType &eChessType)
{
    int nScore = 0;
    for (int i = 0; i < EV_VectorDirectionMax; ++i)
    {
        E_VectorDirection eVectorDirection = E_VectorDirection(i);
        nScore += m_arrChessGroup[eVectorDirection].score(eChessType);
    }
    return nScore;
}
