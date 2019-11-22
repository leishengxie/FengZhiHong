#include "ImageLabel.h"

#include <QPalette>
#include <QTextEdit>
#include <QMouseEvent>
#include <QPainter>

using namespace Qt;

CImageLabel::CImageLabel(QWidget* parent)
    : QLabel(parent)
    , m_bPressed(false)
    , m_eDrawType(ED_None)
{
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    m_plaintextedit = new QTextEdit(this);
    m_plaintextedit->hide();
    m_plaintextedit->resize(60, 40);
    QPalette p1 = m_plaintextedit->palette();
    p1.setBrush(QPalette::Base, QBrush(QColor(255, 0, 0, 0)));
    m_plaintextedit->setPalette(p1);
    connect(m_plaintextedit, SIGNAL(textChanged()), this, SLOT(ontextchanged()));
    m_plaintextedit->setStyleSheet("QTextEdit{ border: 1px solid #dadada; }"
                                   "QTextEdit{font-family:'Microsoft YaHei'; font-size:14px;color:#ff0000;}");
}

void CImageLabel::ontextchanged()
{
    if(m_plaintextedit->toPlainText().size() < 10)
    {
        m_plaintextedit->resize(m_plaintextedit->toPlainText().size() * 10 + 50, 40);
    }
    else
    {
        m_plaintextedit->resize(m_plaintextedit->toPlainText().size() * 15 + 20
                                , m_plaintextedit->document()->size().rheight() + 10);
    }
}

void CImageLabel::mouseMoveEvent(QMouseEvent* event)
{
    if(m_eDrawType != ED_None)
    {

        setCursor(CrossCursor);
    }

    if(m_bPressed)
    {
        if(m_eDrawType == ED_Line)
        {
            m_PtEnd = event->pos();
            m_vecDarwData.append(T_DarwData(m_eDrawType, m_ptStart, m_PtEnd));
            m_ptStart = m_PtEnd;
        }
        else if(m_eDrawType == ED_Rectangle || m_eDrawType == ED_Round || m_eDrawType == ED_Arrow)
        {
            m_PtEnd = event->pos();
        }
        update();
    }
}

void CImageLabel::mousePressEvent(QMouseEvent* event)
{
    m_ptStart = event->pos();
    m_PtEnd = event->pos();
    m_bPressed = true;
    if(m_eDrawType == ED_Text)
    {
        if(m_plaintextedit->toPlainText().size())
        {
            T_DarwData tDarwData(ED_Text
                                 , m_plaintextedit->rect().topLeft(), m_plaintextedit->rect().bottomRight()
                                 , m_plaintextedit->toPlainText());
            m_vecDarwData.append(tDarwData);
            update();
        }
        m_plaintextedit->move(m_ptStart);
        m_plaintextedit->show();
        m_plaintextedit->clear();
    }
}

void CImageLabel::mouseReleaseEvent(QMouseEvent* event)
{
    //setCursor(ArrowCursor);
    m_bPressed = false;

    switch (m_eDrawType)
    {
        case ED_Arrow:
        case ED_Rectangle:
        case ED_Round:
            {
                m_vecDarwData.append(T_DarwData(m_eDrawType, m_ptStart, m_PtEnd));
                update();
                break;
            }
        default:
            break;
    }


}


void CImageLabel::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_imageSelect); //表示是在selectimage上面做编辑
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(red);
    pen.setWidth(2);
    painter.setPen(pen);
    int x = 0;
    int y = 0;
    foreach (T_DarwData tDarwData, m_vecDarwData)
    {
        x = tDarwData.ptStart.x() < tDarwData.ptEnd.x() ? tDarwData.ptStart.x() : tDarwData.ptEnd.x();
        y = tDarwData.ptStart.y() < tDarwData.ptEnd.y() ? tDarwData.ptStart.y() : tDarwData.ptEnd.y();
        switch (tDarwData.eDrawType)
        {
            case ED_Line:
                painter.drawLine(tDarwData.ptStart, tDarwData.ptEnd);
                break;
            case ED_Rectangle:
                painter.drawRect(x, y, abs(tDarwData.ptEnd.x() - tDarwData.ptStart.x())
                                 , abs(tDarwData.ptEnd.y() - tDarwData.ptStart.y()));
                break;
            case ED_Round:
                painter.drawEllipse(x, y, abs(tDarwData.ptEnd.x() - tDarwData.ptStart.x())
                                    , abs(tDarwData.ptEnd.y() - tDarwData.ptStart.y()));
                break;
            case ED_Arrow:
                drawArrow(tDarwData.ptStart, tDarwData.ptEnd, painter);
                break;
            case ED_Text:
                painter.drawText(QRect(tDarwData.ptStart, tDarwData.ptEnd), Qt::TextWrapAnywhere, tDarwData.strText);
                break;
            default:
                break;
        }

    }

    int xx = m_ptStart.x() < m_PtEnd.x() ? m_ptStart.x() : m_PtEnd.x();
    int yy = m_ptStart.y() < m_PtEnd.y() ? m_ptStart.y() : m_PtEnd.y();
    switch (m_eDrawType)
    {
        case ED_Rectangle:
            painter.drawRect(xx, yy, abs(m_PtEnd.x() - m_ptStart.x()), abs(m_PtEnd.y() - m_ptStart.y()));
            break;
        case ED_Round:
            painter.drawEllipse(xx, yy, abs(m_PtEnd.x() - m_ptStart.x()), abs(m_PtEnd.y() - m_ptStart.y()));
            break;
        case ED_Arrow:
            drawArrow(m_ptStart, m_PtEnd, painter);
            break;
        default:
            break;
    }
}

void CImageLabel::drawArrow(QPoint startpoint, QPoint endpoint, QPainter & p)
{
    double par = 15.0;
    double slopy = atan2((endpoint.y() - startpoint.y()), (endpoint.x() - startpoint.x()));
    double cosy = cos(slopy);
    double siny = sin(slopy);
    QPoint point1 = QPoint(endpoint.x() + int(-par * cosy - (par / 2.0 * siny))
                           , endpoint.y() + int(-par * siny + (par / 2.0 * cosy)));
    QPoint point2 = QPoint(endpoint.x() + int(-par * cosy + (par / 2.0 * siny))
                           , endpoint.y() - int(par / 2.0 * cosy + par * siny));
    QPoint points[3] = {endpoint, point1, point2};
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen drawtrianglepen;
    drawtrianglepen.setColor(Qt::red);
    drawtrianglepen.setWidth(1);
    p.setPen(drawtrianglepen);
    p.drawPolygon(points, 3);
    int offsetx = int(par * siny / 3);
    int offsety = int(par * cosy / 3);
    QPoint point3, point4;
    point3 = QPoint(endpoint.x() + int(-par * cosy - (par / 2.0 * siny)) + offsetx
                    , endpoint.y() + int(-par * siny + (par / 2.0 * cosy)) - offsety);
    point4 = QPoint(endpoint.x() + int(-par * cosy + (par / 2.0 * siny) - offsetx)
                    , endpoint.y() - int(par / 2.0 * cosy + par * siny) + offsety);
    QPoint arrbodypoints[3] = {startpoint, point3, point4};
    p.drawPolygon(arrbodypoints, 3);

}

void CImageLabel::setDrawType(E_DrawType eDrawType)
{
    m_eDrawType = eDrawType;

    setTextEditToVector();
    m_plaintextedit->hide();
}

void CImageLabel::setImageToLabel(const QImage & image)
{
    m_imageSelect = image;

    m_PtEnd = QPoint(0, 0);
    m_ptStart = QPoint(0, 0);
}



void CImageLabel::setTextEditToVector()
{
    if (m_eDrawType == ED_Text && m_plaintextedit->toPlainText().size())
    {
        T_DarwData tDarwData(ED_Text
                             , m_plaintextedit->rect().topLeft(), m_plaintextedit->rect().bottomRight()
                             , m_plaintextedit->toPlainText());
        m_vecDarwData.append(tDarwData);
        update();
    }
}

QImage CImageLabel::resultImage()
{
    return QImage(QPixmap::grabWidget(this).toImage());

}
