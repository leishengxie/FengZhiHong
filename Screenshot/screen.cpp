#include "screen.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPoint>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QFileDialog>
#include <QRectF>
#include "controlwidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTime>
#include"myrect.h"

Screen::Screen(QWidget* parent)
    : QWidget(parent),
      m_myRect(QRectF(0, 0, 0, 0)),
      control(NULL)
{
    showFullScreen();
    setMouseTracking(true);

    //截取全屏
    QScreen* scrPix = QGuiApplication::primaryScreen();
    m_pixmapScreen = scrPix->grabWindow(0);

    //全局路径的初始化，一个全屏闭合回路
    m_painterPathScreen.lineTo(0, 0);
    m_painterPathScreen.lineTo(m_pixmapScreen.width(), 0);
    m_painterPathScreen.lineTo(m_pixmapScreen.width(), m_pixmapScreen.height());
    m_painterPathScreen.lineTo(0, m_pixmapScreen.height());

    m_bFirstLeftPress = true;

    //想到了添加一个bool labelimageShow()的函数的方法，找时间试一下
    m_pSLabel = new CImageLabel(this);
    Qt::WindowFlags nType = Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;
    m_pSLabel->setWindowFlags(nType);

    m_eVertexType = NO;

}

void Screen::paintEvent(QPaintEvent* e)//将上一个函数得到的全屏灰色图绘制在painter上，并添加宽高信息矩形和边角拖曳小正方形
{


    QPainter paint(this);
    paint.drawPixmap(0, 0, m_pixmapScreen);

    //pen-蓝色边框 brush-透明灰色遮罩
    paint.setPen(Qt::blue);
    paint.setBrush(QColor(0, 0, 0, 100));

    //设置路径
    QPainterPath path = getPath();
    paint.drawPath(path);

    //绘制选取左上角显示宽高的区域
    m_myRect.drawMe(paint);

    //绘制四个小正方形
    drawControlArea(paint);

}
//绘制正方形
void Screen::drawControlArea(QPainter & painter) //已看懂
{
    //计算四个小正方形
    rect1.setX(m_ptMove.x() - 3);
    rect1.setY(m_ptPress.y() - 3);
    rect1.setWidth(6);
    rect1.setHeight(6);

    rect2.setX(m_ptPress.x() - 3);
    rect2.setY(m_ptPress.y() - 3);
    rect2.setWidth(6);
    rect2.setHeight(6);

    rect3.setX(m_ptPress.x() - 3);
    rect3.setY(m_ptMove.y() - 3);
    rect3.setWidth(6);
    rect3.setHeight(6);

    rect4.setX(m_ptMove.x() - 3);
    rect4.setY(m_ptMove.y() - 3);
    rect4.setWidth(6);
    rect4.setHeight(6);

    painter.save();
    painter.setBrush(Qt::blue);
    painter.drawRect(rect1);
    painter.drawRect(rect2);
    painter.drawRect(rect3);
    painter.drawRect(rect4);
    painter.restore();
}



//得到选区之外的路径
QPainterPath Screen::getPath()   //这个函数得到的是开始截图时候得到的白色选区
{
    //选取路径
    QPainterPath path;
    path.moveTo(m_ptPress.x(), m_ptPress.y());
    path.lineTo(m_ptMove.x(), m_ptPress.y());
    path.lineTo(m_ptMove.x(), m_ptMove.y());
    path.lineTo(m_ptPress.x(), m_ptMove.y());
    path.lineTo(m_ptPress.x(), m_ptPress.y());
    return m_painterPathScreen.subtracted(path);    //从灰色全屏路径中扣掉这个白色路径区域，然后作为截取的图片？
}


void Screen::mousePressEvent(QMouseEvent* e)
{
    if( e->button() & Qt::LeftButton && m_bFirstLeftPress)   //如果鼠标左键第一次按下
    {
        m_ptPress = e->pos();
    }
    else
    {
        oldPoint = e->pos();
    }
}

//只有已经按下鼠标按键，才会存在鼠标释放行为，释放鼠标后会立刻出现控制面板
void Screen::mouseReleaseEvent(QMouseEvent* e)
{
    m_bFirstLeftPress = false;
    if( !control )        //如果未出现截图操作控件
    {
        qDebug() << "new ControlWidget";
        control = new QWidget(this);         //新建一个窗口控件
        controlUi = new ControlWidget(control);  //新建控制窗口
        QHBoxLayout* layout = new QHBoxLayout(control);    //在control上建立水平布局
        layout->addWidget(controlUi);         //将控制窗口应用于水平布局
        layout->setContentsMargins(0, 0, 0, 0);
        control->setObjectName("control");
        control->setStyleSheet("QWidget#control{\
                               background-color: #eaecf0;}");
        controlUi->setScreenQuote(this);
    }
    //设置控制面板的位置
    control->setGeometry(m_ptMove.x() - 543, m_ptMove.y() + 6, 543, 25);
    control->show();
}

void Screen::mouseMoveEvent(QMouseEvent* e)
{
    QPoint tempPoint = e->pos();     //当前鼠标位置
    setSelectImageLabel();

    if(e->buttons() & Qt::LeftButton)   //如果左键按下
    {
        //选取左上角的信息更改
        int x = qAbs(m_ptMove.x() - m_ptPress.x());//movepoint即终点坐标
        int y = qAbs(m_ptMove.y() - m_ptPress.y());
        m_myRect.setText(tr("%1 * %2").arg(x).arg(y));   //将截图选区的长宽信息显示在widthinforect中
        if( comparePoint(m_ptPress, m_ptMove))
        {
            m_myRect.setLocation(m_ptPress.x(), m_ptPress.y());
            //计算选区矩形
            rect.setX(m_ptPress.x());
            rect.setY(m_ptPress.y());
            rect.setWidth(m_ptMove.x() - m_ptPress.x());
            rect.setHeight(m_ptMove.y() - m_ptPress.y());
        }
        else
        {
            m_myRect.setLocation(m_ptMove.x(), m_ptMove.y());
            rect.setX(m_ptMove.x());
            rect.setY(m_ptMove.y());
            rect.setWidth(m_ptPress.x() - m_ptMove.x());
            rect.setHeight(m_ptPress.y() - m_ptMove.y());
        }

        if( m_bFirstLeftPress )    //如果是第一次按下时候，
        {
            m_ptMove = e->pos();   //终点即为鼠标此时位置
            //此时的移动代表选区的变化
        }
        else
        {

            if( control )  //如果控制面板已经出现，则第二次以后的每一次鼠标按键都会使其暂时隐藏
            {
                control->hide();
            }
            int moveX = tempPoint.x() - oldPoint.x();  //鼠标移动的x距离
            int moveY = tempPoint.y() - oldPoint.y();   //鼠标移动的y距离
            switch( m_eVertexType )         //选区角落四个小矩形的位置
            {
                case RECT1:               //意思是第一次选区之后，分别拖动四个角落的小矩形时候，截图选区的变化
                    m_ptPress.setY(m_ptPress.y() + moveY);  //右上角的矩形
                    m_ptMove.setX(m_ptMove.x() + moveX);
                    break;
                case RECT2:
                    m_ptPress.setX(m_ptPress.x() + moveX);    //左上角的矩形
                    m_ptPress.setY(m_ptPress.y() + moveY);
                    break;
                case RECT3:
                    m_ptPress.setX(m_ptPress.x() + moveX);  //左下角的矩形
                    m_ptMove.setY(m_ptMove.y() + moveY);
                    break;
                case RECT4:
                    m_ptMove.setX(m_ptMove.x() + moveX);     //右下角的矩形
                    m_ptMove.setY(m_ptMove.y() + moveY);
                    break;
                case RECT:                  //指的是当鼠标在截图选区中按下左键然后拖动时候，截图选区的整体位置变化
                    {

                        int tempPressX = m_ptPress.x() + moveX;
                        int tempPressY = m_ptPress.y() + moveY;
                        int tempMoveX = m_ptMove.x() + moveX;
                        int tempMoveY = m_ptMove.y() + moveY;
                        int deskWidth = m_pixmapScreen.width();
                        int deskHeight = m_pixmapScreen.height();
                        if( tempPressX < 0 )
                        {
                            tempPressX = 0;
                            tempMoveX = m_ptMove.x();
                        }
                        if( tempPressX > deskWidth)
                        {
                            tempPressX = deskHeight;
                        }
                        if(tempPressY < 0)
                        {
                            tempPressY = 0;
                            tempMoveY = m_ptMove.y();
                        }
                        if( tempPressY > deskHeight)
                        {

                            tempPressY = deskHeight;
                        }
                        if( tempMoveX < 0)
                        {
                            tempMoveX = 0;
                        }
                        if( tempMoveX > deskWidth)
                        {
                            tempMoveX = deskWidth;
                            tempPressX = m_ptPress.x();
                        }
                        if( tempMoveY < 0)
                        {
                            tempMoveY = 0;
                        }
                        if( tempMoveY > deskHeight)
                        {
                            tempMoveY = deskHeight;
                            tempPressY = m_ptPress.y();

                        }
                        m_ptPress.setX(tempPressX);    //鼠标在截图区域中拖动结束后，选区的位置
                        m_ptPress.setY(tempPressY);
                        m_ptMove.setX(tempMoveX);
                        m_ptMove.setY(tempMoveY);
                        break;
                    }
                case NO:
                    break;
                default:
                    break;
            }
            oldPoint = tempPoint;    //更新位置坐标信息
        }

    }
    else                            //指的是当鼠标位于四个角落小矩形中和选区中时候鼠标的图标变化
    {
        E_VertexType r = pointInWhere(e->pos());
        if( r == RECT1)
        {
            m_eVertexType = RECT1;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if( r == RECT2)
        {
            m_eVertexType = RECT2;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if( r == RECT3)
        {
            m_eVertexType = RECT3;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if( r == RECT4)
        {
            m_eVertexType = RECT4;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if( r == RECT)
        {
            m_eVertexType = RECT;
            setCursor(Qt::SizeAllCursor);
        }
        else
        {
            m_eVertexType = NO;
            setCursor(Qt::ArrowCursor);
        }
    }
    repaint();


}

bool Screen::compareRect(QRectF & r1, QRectF & r2)
{
    return false;
}

//计算此时鼠标移动在哪个选区上面
E_VertexType Screen::pointInWhere(QPoint p)
{
    if( pointInRect(p, rect1))
    {
        return RECT1;
    }
    else if( pointInRect(p, rect2))
    {
        return RECT2;
    }
    else if( pointInRect(p, rect3))
    {
        return RECT3;
    }
    else if( pointInRect(p, rect4))
    {
        return RECT4;
    }
    else if( pointInRect(p, rect))
    {
        return RECT;
    }
    else
    {
        return NO;
    }

}

//判断点是否在矩形之内   已看懂
bool Screen::pointInRect(QPoint & p, QRectF & r)
{
    if( p.x() > r.x() && p.x() < r.x() + r.width() &&
            p.y() > r.y() && p.y() < r.y() + r.height())
    {
        return true;
    }
    return false;
}

void Screen::keyPressEvent(QKeyEvent* e)    //键盘事件，包括esc退出截图，回车键完成截图，返回键完成截图
{
    int key = e->key();
    switch( key )
    {
        case Qt::Key_Escape :
            close();
            break;
        case Qt::Key_Enter:
            if( controlUi )
            {
                controlUi->finishBtn_slot();
            }
            break;
        case Qt::Key_Return :
            if( controlUi )
            {
                controlUi->finishBtn_slot();
            }
            break;
        default:
            break;
    }
}

//如果p1的x和y坐标都小于p2的x和y坐标返回true
bool Screen::comparePoint(QPoint & p1, QPoint & p2)    //点p1的位置坐标是否小于p2点
{
    if(p1.x() < p2.x() && p1.y() < p2.y())
    {
        return true;
    }
    return false;
}

void Screen::setselectimagelabel(QMouseEvent* event)
{
    int wid = abs(m_ptMove.x() - m_ptPress.x());
    int hei = abs(m_ptMove.y() - m_ptPress.y());
    int x = m_ptPress.x() < m_ptMove.x() ? m_ptPress.x() : m_ptMove.x();
    int y = m_ptPress.y() < m_ptMove.y() ? m_ptPress.y() : m_ptMove.y();
    QImage selectimage = m_pixmapScreen.copy(x, y, wid, hei).toImage();

    m_pSLabel->setImageToLabel(selectimage);
    m_pSLabel->setFixedSize(wid, hei);
    m_pSLabel->move(QPoint(x, y));
    m_pSLabel->show();
}

//保存截取出来的图片
void Screen::savePixmap()
{

    //生成图片名称
    QString picName;
    QTime time;
    //获取当前系统时间，用做伪随机数的种子
    time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    //随机字符串
    QString randStr;
    randStr.setNum(qrand());
    picName.append(randStr);

    QString filename = QFileDialog::getSaveFileName(this, QStringLiteral("保存截图"), picName, "JPEG Files(*.jpg)");

    if(filename.length() > 0)
    {
        QImage pimage = m_pSLabel->resultImage();
        pimage.save(filename, "jpg");
    }
}

QPixmap Screen::getSelectPixmap()   //返回截到的图片
{
    return m_pixmapScreen.copy(m_ptPress.x(), m_ptPress.y(), m_ptMove.x() - m_ptPress.x(),
                       m_ptMove.y() - m_ptPress.y());   //这个地方是关键，可以从这里入手了，得到了pixmap之后，进行toimage，然后进行编辑操作
}

void Screen::drawline()
{

    m_pSLabel->setDrawLineEnable();

}

void Screen::textedit()
{
    m_pSLabel->setTextEditEnable();
}

void Screen::drawarrow()
{
    m_pSLabel->setDrawArrowEnable();
}

void Screen::drawround()
{
    m_pSLabel->setRoundEnable();
}

void Screen::drawrectang()
{
    m_pSLabel->setRectAngleEnable();
}

void Screen::Exit()
{
    if(m_pSLabel)
    {
        m_pSLabel->close();
    }
}

Screen::~Screen()
{
    // delete control;
}
