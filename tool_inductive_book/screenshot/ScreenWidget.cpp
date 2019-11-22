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
    , m_rectfTip(QRectF(0, 0, 71, 21))
    , m_eVertexType(NO)
    , m_bFirstLeftPress(true)

{
    ui->setupUi(this);
    showFullScreen();
    setMouseTracking(true);
    setAttribute(Qt::WA_DeleteOnClose);

    //截取全屏
    QScreen* scrPix = QGuiApplication::primaryScreen();
    m_pixmapScreen = scrPix->grabWindow(0);

    ui->controlWidget->hide();

}


void CScreenWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    //
    painter.drawPixmap(0, 0, m_pixmapScreen);

    // 相当于绘制遮罩
    drawOutSideSlelectArea(painter);

    //绘制四个小正方形
    drawControlArea(painter);

    //绘制选取左上角显示宽高的区域
    drawRectTip(painter);


}

void CScreenWidget::mousePressEvent(QMouseEvent* event)
{
    if( event->button() & Qt::LeftButton && m_bFirstLeftPress)   //如果鼠标左键第一次按下
    {
        m_ptPress = event->pos();
    }
    else
    {
        oldPoint = event->pos();
    }
}

void CScreenWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_bFirstLeftPress = false;

    ui->controlWidget->setStyleSheet("QWidget#control{background-color: #eaecf0;}");

    //设置控制面板的位置
    ui->controlWidget->move(QPoint((int)m_rectf.x(), (int)m_rectf.bottomLeft().y()));
    ui->controlWidget->show();
}

void CScreenWidget::mouseMoveEvent(QMouseEvent* event)
{
    int x = m_ptPress.x() < m_ptMove.x() ? m_ptPress.x() : m_ptMove.x();
    int y = m_ptPress.y() < m_ptMove.y() ? m_ptPress.y() : m_ptMove.y();
    int w = qAbs(m_ptMove.x() - m_ptPress.x());
    int h = qAbs(m_ptMove.y() - m_ptPress.y());
    m_rectf.setRect(x, y, w, h);
    QImage imageSelect = m_pixmapScreen.copy(m_rectf.toRect()).toImage();
    ui->imageLabel->setImageToLabel(imageSelect);
    ui->imageLabel->setFixedSize(w, h);
    ui->imageLabel->move(QPoint(x, y));
    ui->imageLabel->show();

    QPoint ptCursor = event->pos();     //当前鼠标位置
    if(event->buttons() & Qt::LeftButton)   //如果左键按下
    {

        m_strTip = QString("%1 * %2").arg(w).arg(h);   //将截图选区的长宽信息显示在widthinforect中
        m_rectfTip.moveTo(m_rectf.x(), m_rectf.y() - 21);

        if( m_bFirstLeftPress )    //如果是第一次按下时候，
        {
            m_ptMove = event->pos();   //终点即为鼠标此时位置
            //此时的移动代表选区的变化
        }
        else
        {

            ui->controlWidget->hide();
            int moveX = ptCursor.x() - oldPoint.x();  //鼠标移动的x距离
            int moveY = ptCursor.y() - oldPoint.y();   //鼠标移动的y距离
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
            oldPoint = ptCursor;    //更新位置坐标信息
        }

    }
    else                            //指的是当鼠标位于四个角落小矩形中和选区中时候鼠标的图标变化
    {
        if( rect1.contains(ptCursor))
        {
            m_eVertexType = RECT1;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if( rect2.contains(ptCursor))
        {
            m_eVertexType = RECT2;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if( rect3.contains(ptCursor))
        {
            m_eVertexType = RECT3;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if( rect4.contains(ptCursor))
        {
            m_eVertexType = RECT4;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if( m_rectf.contains(ptCursor))
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



void CScreenWidget::drawOutSideSlelectArea(QPainter & painter)
{
    painter.save();
    //pen-蓝色边框 brush-透明灰色遮罩
    painter.setPen(Qt::blue);
    painter.setBrush(QColor(0, 0, 0, 100));

    QPainterPath painterPathScreen;
    painterPathScreen.addRect(m_pixmapScreen.rect());

    QPainterPath path;
    path.addRect(m_rectf);
    // 取反交集
    QPainterPath pathOutSide =  painterPathScreen.subtracted(path);
    painter.drawPath(pathOutSide);
    painter.restore();
}

void CScreenWidget::drawRectTip(QPainter & painter)
{
    painter.save();
    painter.setPen(QPen());
    painter.setBrush(QColor(0, 0, 0, 150));
    painter.drawRect(m_rectfTip);
    //设置白色文字
    painter.setPen(QColor(255, 255, 255));
    //居中画出文字
    painter.drawText(m_rectfTip, Qt::AlignCenter, m_strTip);
    painter.restore();
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
    QPixmap pix = m_pixmapScreen.copy(m_rectf.toRect());
    emit finishScreenshot(pix);
    QClipboard* board = QApplication::clipboard();
    board->setImage(pix.toImage());
    close();
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

void CScreenWidget::on_btnCancel_clicked()
{
    close();
}

void CScreenWidget::on_btnDrawLine_clicked()
{
    ui->imageLabel->setDrawType(ED_Line);
}

void CScreenWidget::on_btnRectangle_clicked()
{
    ui->imageLabel->setDrawType(ED_Rectangle);
}

void CScreenWidget::on_btnDrawRound_clicked()
{
    ui->imageLabel->setDrawType(ED_Round);
}

void CScreenWidget::on_btnArrow_clicked()
{
    ui->imageLabel->setDrawType(ED_Arrow);
}

void CScreenWidget::on_btnTextEdit_clicked()
{
    ui->imageLabel->setDrawType(ED_Text);
}
