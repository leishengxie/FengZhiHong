#include "ListViewEx.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStringListModel>
#include <QtDebug>

static const char s_strEmptyTip[] = "你还没有归纳本文章哦！";

CListViewEx::CListViewEx(QWidget* parent)
    : QListView(parent)
{
//    QStringListModel *model = new QStringListModel(this);
//    setModel(model);
}

void CListViewEx::paintEvent(QPaintEvent* event)
{
    if (model() && model()->rowCount() > 0)
    {
        return QListView::paintEvent(event);
    }
    QPainter painter(viewport());   // 注意时viewport()而不是this
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);

     QFontMetrics fontMetrics(painter.font());
    int nWidthTip = fontMetrics.width(s_strEmptyTip);
    int nSpace = 10;
    int nWidthAddBook = 50;
    int nWidthTotal = nWidthTip + nSpace + nWidthAddBook;
    int nStartX = width() * 0.5 - nWidthTotal * 0.5;
    int nY = height() * 0.5 - fontMetrics.height() * 0.5;

    QRect rectEmptyTip(nStartX, nY, nWidthTip, fontMetrics.height());
    m_rectAdd = QRect(nStartX + nWidthTip + nSpace, nY, nWidthAddBook, fontMetrics.height());
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);
    painter.drawText(rectEmptyTip, s_strEmptyTip, textOption);
    painter.drawRect(m_rectAdd);
    painter.drawText(m_rectAdd, "+", textOption);
}

void CListViewEx::mousePressEvent(QMouseEvent *event)
{
    if (model() && model()->rowCount() > 0)
    {
        return QListView::mousePressEvent(event);
    }
    QPoint pt = event->pos();
    if (m_rectAdd.contains(pt))
    {
        emit btnAddClicked();
        qDebug() << "btnAddClicked";
    }
}
