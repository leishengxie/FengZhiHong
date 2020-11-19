#include "LSortButton.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

CLSortButton::CLSortButton(const QPixmap &pixUp, const QPixmap &pixDown, QWidget *parent)
    : QWidget(parent)
    , m_pixUp(new QPixmap(pixUp))
    , m_pixDown(new QPixmap(pixDown))
{
    init();
}

CLSortButton::CLSortButton(QWidget *parent)
    : QWidget(parent)
    , m_pixUp(nullptr)
    , m_pixDown(nullptr)
{
    init();
}

void CLSortButton::init()
{
    m_eSortType = ES_Up;
    m_bPressed = false;
    if (m_pixUp)
    {
        resize(m_pixUp->size());
    }
}

CLSortButton::~CLSortButton()
{
    delete m_pixUp;
    delete m_pixDown;
}

QSize CLSortButton::sizeHint() const
{
    return QSize(50, 30);
}

void CLSortButton::setPixmap(const QPixmap &pixUp, const QPixmap &pixDown)
{
    if (m_pixUp || m_pixDown)
    {
        return;
    }
    m_pixUp = new QPixmap(pixUp);
    m_pixDown = new QPixmap(pixDown);
    resize(m_pixUp->size());
}

void CLSortButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if(m_eSortType == ES_Up)
    {
        painter.drawPixmap(rect(), *m_pixUp);
    }
    else
    {
        painter.drawPixmap(rect(), *m_pixDown);
    }
}

void CLSortButton::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
    }
}

void CLSortButton::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    if ((event->button() == Qt::LeftButton) && m_bPressed)
    {
        if (m_eSortType == ES_Up)
        {
            m_eSortType = ES_Down;
        }
        else
        {
            m_eSortType = ES_Up;
        }
        update();
        emit clicked(m_eSortType);
    }
    m_bPressed = false;
}

