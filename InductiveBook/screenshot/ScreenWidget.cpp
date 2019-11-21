#include "ScreenWidget.h"
#include "ui_ScreenWidget.h"

//#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QKeyEvent>
#include <QTime>
#include <QFileDialog>
#include <QClipboard>

CScreenWidget::CScreenWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CScreenWidget)
    , m_rectf(QRectF(0, 0, 0, 0))
    , m_eVertexType(NO)

{
    ui->setupUi(this);

    //截取全屏
    QScreen* scrPix = QGuiApplication::primaryScreen();
    m_pixmapScreen = scrPix->grabWindow(0);

    //全局路径的初始化，一个全屏闭合回路
    m_painterPathScreen.lineTo(0, 0);
    m_painterPathScreen.lineTo(m_pixmapScreen.width(), 0);
    m_painterPathScreen.lineTo(m_pixmapScreen.width(), m_pixmapScreen.height());
    m_painterPathScreen.lineTo(0, m_pixmapScreen.height());

    //m_bFirstLeftPress = true;

    //想到了添加一个bool labelimageShow()的函数的方法，找时间试一下
    m_rectfTip.setWidth(71);
    m_rectfTip.setHeight(21);

}

QPixmap CScreenWidget::getSelectPixmap()
{
    return m_pixmapScreen.copy(m_ptPress.x()
                               , m_ptPress.y()
                               , m_ptMove.x() - m_ptPress.x()
                               , m_ptMove.y() - m_ptPress.y());
}

void CScreenWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmapScreen);

    // 相当于绘制遮罩
    drawOutSideSlelectArea(painter);

    //绘制选取左上角显示宽高的区域
    drawRectTip(painter);

    //绘制四个小正方形
    drawControlArea(painter);
}

void CScreenWidget::mousePressEvent(QMouseEvent* event)
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

void CScreenWidget::mouseReleaseEvent(QMouseEvent* event)
{
    //m_bFirstLeftPress = false;

    ui->controlWidget->setStyleSheet("QWidget#control{\
                           background-color: #eaecf0;}");
    //ui->controlWidget->setScreenQuote(this);
    //设置控制面板的位置
    ui->controlWidget->setGeometry(m_ptMove.x() - 543, m_ptMove.y() + 6, 543, 25);
    ui->controlWidget->show();
}

void CScreenWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint tempPoint = event->pos();     //当前鼠标位置
    setSelectImageLabel();

    if(event->buttons() & Qt::LeftButton)   //如果左键按下
    {
        //选取左上角的信息更改
        int x = qAbs(m_ptMove.x() - m_ptPress.x());//movepoint即终点坐标
        int y = qAbs(m_ptMove.y() - m_ptPress.y());

        m_strTip = QString("%1 * %2").arg(x).arg(y);   //将截图选区的长宽信息显示在widthinforect中
        if( comparePoint(m_ptPress, m_ptMove))
        {

            m_rectfTip.setX(m_ptPress.x());
            m_rectfTip.setY(m_ptPress.y() - 21);

            //计算选区矩形
            rect.setX(m_ptPress.x());
            rect.setY(m_ptPress.y());
            rect.setWidth(m_ptMove.x() - m_ptPress.x());
            rect.setHeight(m_ptMove.y() - m_ptPress.y());
        }
        else
        {
            m_rectfTip.setX(m_ptMove.x());
            m_rectfTip.setY(m_ptMove.y() - 21);

            rect.setX(m_ptMove.x());
            rect.setY(m_ptMove.y());
            rect.setWidth(m_ptPress.x() - m_ptMove.x());
            rect.setHeight(m_ptPress.y() - m_ptMove.y());
        }

        if( m_bFirstLeftPress )    //如果是第一次按下时候，
        {
            m_ptMove = event->pos();   //终点即为鼠标此时位置
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
        E_VertexType r = pointInWhere(event->pos());
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

void CScreenWidget::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    switch( key )
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            on_btnFinish_clicked();
            break;
        default:
            break;
    }
}

void CScreenWidget::setSelectImageLabel()
{
    int nWidth = abs(m_ptMove.x() - m_ptPress.x());
    int nHeight = abs(m_ptMove.y() - m_ptPress.y());
    int x = m_ptPress.x() < m_ptMove.x() ? m_ptPress.x() : m_ptMove.x();
    int y = m_ptPress.y() < m_ptMove.y() ? m_ptPress.y() : m_ptMove.y();
    QImage imageSelect = m_pixmapScreen.copy(x, y, nWidth, nHeight).toImage();

    ui->imageLabel->setImageToLabel(imageSelect);
    ui->imageLabel->setFixedSize(nWidth, nHeight);
    ui->imageLabel->move(QPoint(x, y));
    ui->imageLabel->show();
}

void CScreenWidget::drawOutSideSlelectArea(QPainter & painter)
{
    painter.save();
    //pen-蓝色边框 brush-透明灰色遮罩
    painter.setPen(Qt::blue);
    painter.setBrush(QColor(0, 0, 0, 100));

    QPainterPath path;
    path.moveTo(m_ptPress.x(), m_ptPress.y());
    path.lineTo(m_ptMove.x(), m_ptPress.y());
    path.lineTo(m_ptMove.x(), m_ptMove.y());
    path.lineTo(m_ptPress.x(), m_ptMove.y());
    path.lineTo(m_ptPress.x(), m_ptPress.y());
    // 取反交集
    QPainterPath pathOutSide =  m_painterPathScreen.subtracted(path);
    painter.drawPath(pathOutSide);
    painter.restore();
}

void CScreenWidget::drawRectTip(QPainter & painter)
{

}

void CScreenWidget::drawControlArea(QPainter & painter)
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

void CScreenWidget::on_btnFinish_clicked()
{
    QPixmap pix = getSelectPixmap();
    QClipboard* board = QApplication::clipboard();
    board->setImage(pix.toImage());
}

void CScreenWidget::on_btnSave_clicked()
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
        QImage pimage = ui->imageLabel->resultImage();
        pimage.save(filename, "jpg");
    }
}
