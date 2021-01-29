

#include <QtWidgets>
#include <cmath>

#include "StarEditor.h"


static const qreal s_nPaintingScaleFactor = 20.0;
static const int s_nMaxStarCount = 5;

CStarEditor::CStarEditor(QWidget* parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    m_dRating = 0;
    m_nMaxStarCount = s_nMaxStarCount;
    m_bReadOnly = false;
    bLeftMousePress = false;
    bDelegateEedit = false;

}

void CStarEditor::drawFiveStarRating(QPainter *painter, const QRect &rect, const QPalette & palette
                                     , qreal dRating, bool bReadOnly)
{
    // 五星路径 单元(半径0.5)
    QPolygonF polygonStar;
    polygonStar << QPointF(1.0, 0.5);
    for (int i = 1; i < 5; ++i)
    {
        polygonStar << QPointF(0.5 + 0.5 * std::cos(0.8 * i * 3.14), 0.5 + 0.5 * std::sin(0.8 * i * 3.14));
    }

    // 砖石路径 单元
    QPolygonF polygonDiamond;
    polygonDiamond << QPointF(0.4, 0.5) << QPointF(0.5, 0.4) << QPointF(0.6, 0.5) << QPointF(0.5, 0.6) << QPointF(0.4, 0.5);


    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    if (bReadOnly)
    {
        painter->setBrush(palette.foreground());
    }
    else
    {
        painter->setBrush(palette.highlight());
    }

    int yOffset = (rect.height() - s_nPaintingScaleFactor) / 2;

    painter->translate(rect.x(), rect.y() + yOffset);

    // 放大坐标系
    painter->scale(s_nPaintingScaleFactor, s_nPaintingScaleFactor);

    // 整数部分
    int nRating = (int) dRating;
    // 余数部分
    qreal dMOD = dRating - nRating;

    int nRatingAdd1 = nRating + 1;
    for (int i = 0; i < s_nMaxStarCount; ++i)
    {
        if (i < nRating)
        {
            painter->drawPolygon(polygonStar, Qt::WindingFill);
        }
        else if (i < nRatingAdd1)
        {
            QPolygonF polygonRectMod;
            polygonRectMod << QPointF(0.0, 0.0) << QPointF(dMOD, 0.0) << QPointF(dMOD, 1.0) << QPointF(0.0, 1.0);

//            QPainterPath painterPath;
//            painterPath.addPolygon(polygonStar);

//            QRectF rectMOD(0, 0, dMOD, 1.0);
//            QPainterPath painterPathMod;
//            painterPathMod.addRect(rectMOD);

//            QPainterPath pathIntersected = painterPath.intersected(painterPathMod);
//            painter->drawPath(pathIntersected);

            QPolygonF polygonIntersected = polygonStar.intersected(polygonRectMod);
            painter->drawPolygon(polygonIntersected, Qt::WindingFill);

        }
        else if (!bReadOnly)
        {
            painter->drawPolygon(polygonDiamond, Qt::WindingFill);
        }
        // 不断平移坐标系
        painter->translate(1.0, 0.0);
    }

    painter->restore();

}


QSize CStarEditor::sizeHint() const
{
    // s_nPaintingScaleFactor右边距
    return s_nPaintingScaleFactor * QSize(m_nMaxStarCount, 1) + QSize(s_nPaintingScaleFactor,0);
}


void CStarEditor::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    drawFiveStarRating(&painter, rect(), this->palette(), m_dRating, m_bReadOnly);
}

void CStarEditor::mousePressEvent(QMouseEvent *event)
{
    bLeftMousePress = true;
}

void CStarEditor::mouseMoveEvent(QMouseEvent* event)
{
    if (bDelegateEedit)
    {
        qreal dRating = event->x() / s_nPaintingScaleFactor;

        if (dRating < 0)
        {
            dRating = 0;
        }
        if ( dRating > m_nMaxStarCount)
        {
            dRating = m_nMaxStarCount;
        }

        m_dRating = dRating;
        update();
    }

}

void CStarEditor::mouseReleaseEvent(QMouseEvent* event)
{
    bLeftMousePress = false;
    if (!bDelegateEedit)
    {
        qreal dRating = event->x() / s_nPaintingScaleFactor;

        if (dRating < 0)
        {
            dRating = 0;
        }
        if ( dRating > m_nMaxStarCount)
        {
            dRating = m_nMaxStarCount;
        }

        m_dRating = dRating;
        update();
    }
    emit editingFinished();
    emit editingFinished(m_dRating);
}


