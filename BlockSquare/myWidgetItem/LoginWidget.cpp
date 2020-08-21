#include "LoginWidget.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QObject>
#include <QTimer>
#include "QTime"

void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

CLoginWidget::CLoginWidget(QWidget *parent)
    : QGraphicsView(parent)
{


    QGraphicsScene *scene=new QGraphicsScene;
    //scene->setBackgroundBrush(QPixmap(":/new/prefix1/images/myBackground.png"));
    //scene->setSceneRect(5,5,800,600);

    //m_pGraView = new QGraphicsView(this);
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    //m_pGraView->setAttribute(Qt::WA_TranslucentBackground, true);
    resize(800,500);
    setScene(scene);
    //m_pGraView->setStyleSheet("background-color:rgb(184,7,235);color:white;");
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setStyleSheet("background: transparent;border:0px");

    // 创建部件，并关联它们的信号和槽
    QTextEdit *edit = new QTextEdit;
    QPushButton *button = new QPushButton("clear");
    QObject::connect(button, SIGNAL(clicked()), edit, SLOT(clear()));

    // 将部件添加到场景中
    QGraphicsWidget *textEdit = scene->addWidget(edit);
    QGraphicsWidget *pushButton = scene->addWidget(button);
    // 将部件添加到布局管理器中
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->addItem(textEdit);
    layout->addItem(pushButton);
    // 创建图形部件，设置其为一个顶层窗口，然后在其上应用布局
    m_pGraWgtLogin = new QGraphicsWidget;
//    m_pGraWgtLogin->setWindowFlags(Qt::Window);
//    m_pGraWgtLogin->setWindowTitle("Widget Item");
    QPalette palette=m_pGraWgtLogin->palette();
    palette.setBrush(QPalette::Background,QBrush(QColor(184,7,235)));
    m_pGraWgtLogin->setPalette(palette);
    m_pGraWgtLogin->setAutoFillBackground(true);
    m_pGraWgtLogin->setLayout(layout);
    m_pGraWgtLogin->resize(300,200);
//    m_pGraWgtLogin->setMaximumSize(500,400);
//    m_pGraWgtLogin->setMinimumSize(500,400);
    m_pGraWgtLogin->setX((width() - m_pGraWgtLogin->size().width()) / 2);
    m_pGraWgtLogin->setY((height() - m_pGraWgtLogin->size().height()) / 2);
    scene->addItem(m_pGraWgtLogin);
    //m_pGraView->show();

    //       view.setStyleSheet("background: transparent");
    //       view.setWindowFlags(Qt::FramelessWindowHint);
    //       view.setStyleSheet("background:transparent;border:0px");
    //       view.setWindowFlags(Qt::FramelessWindowHint);
    //       view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //       view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //       for(int i=1;i<=360;i++)
    //       {
    //           form->setTransform(QTransform()
    //                              .translate(r.width() / 2, r.height() / 2)
    //                              .rotate(i - 360 * 1, Qt::YAxis)
    //                              .translate(-r.width() / 2, -r.height() / 2));
    //           sleep(20);
    //           view.update();
    //       }


    QTimer::singleShot(1000, this, SLOT(slot_rotate()));

}

void CLoginWidget::slot_rotate()
{
    QRectF r = m_pGraWgtLogin->boundingRect();
    for(int i=1;i<=89;i++)
    {
        m_pGraWgtLogin->setTransform(QTransform()
                           .translate(r.width() / 2, r.height() / 2)
                           .rotate(i, Qt::YAxis)
                           .translate(-r.width() / 2, -r.height() / 2));
        sleep(100);
        update();
    }


    for(int i=1;i<=91;i++)
    {
        m_pGraWgtLogin->setTransform(QTransform()
                           .translate(r.width() / 2, r.height() / 2)
                           .rotate(i+270, Qt::YAxis)
                           .translate(-r.width() / 2, -r.height() / 2));
        sleep(100);
        update();
    }
}
