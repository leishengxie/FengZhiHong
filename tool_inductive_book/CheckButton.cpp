#include "CheckButton.h"
#include <QPainter>

CCheckButton::CCheckButton(QWidget* parent)
    : QWidget(parent)
{
    init();
}

CCheckButton::CCheckButton(const QString & text, QWidget* parent)
    : QWidget(parent)
    , m_strText(text)
{
    init();
}

void CCheckButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font = painter.font();
    font.setBold(m_bCkecked);
    painter.setFont(font);
    if (m_bCkecked)
    {
        painter.setPen(QColor(100, 184, 255));
    }
    else
    {
        painter.setPen(Qt::gray);
    }
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);
    painter.drawRoundedRect(rect(), 5, 5);
    painter.drawText(rect(), m_strText, textOption);
}

void CCheckButton::mousePressEvent(QMouseEvent* event)
{
    m_bMousePress = true;
    return QWidget::mousePressEvent(event);
}

void CCheckButton::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    if (m_bMousePress)
    {
        m_bCkecked = !m_bCkecked;
        emit clicked(m_bCkecked);
        m_bMousePress = false;
        update();
    }
}

QSize CCheckButton::sizeHint() const
{
    return QSize(80, 28);
}

void CCheckButton::init()
{
    m_bCkecked = false;
    m_bMousePress = false;
}
