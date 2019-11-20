#include "ScreenWidget.h"

CScreenWidget::CScreenWidget(QWidget *parent)
    : QWidget(parent)
{
    //截取全屏
    QScreen* scrPix = QGuiApplication::primaryScreen();
    m_pixmapScreen = scrPix->grabWindow(0);

    //全局路径的初始化，一个全屏闭合回路
    m_painterPathScreen.lineTo(0, 0);
    m_painterPathScreen.lineTo(m_pixmapScreen.width(), 0);
    m_painterPathScreen.lineTo(m_pixmapScreen.width(), m_pixmapScreen.height());
    m_painterPathScreen.lineTo(0, m_pixmapScreen.height());
}

void CScreenWidget::paintEvent(QPaintEvent *event)
{

}

void CScreenWidget::mousePressEvent(QMouseEvent *event)
{

}

void CScreenWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void CScreenWidget::mouseMoveEvent(QMouseEvent *event)
{

}
