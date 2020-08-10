#include "DailyScheduleWidget.h"
#include "ui_DailyScheduleWidget.h"
#include "MiniWidget.h"
#include "DailyScheduleEditor.h"
#include <QMenu>
#include <QtDebug>
#include <QCloseEvent>

CDailyScheduleWidget::CDailyScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDailyScheduleWidget)
{
    ui->setupUi(this);
    connect(ui->listView, SIGNAL(sigDailyScheduleClicked(T_DailySchedule))
            , this, SLOT(slotLoadDailySchedule(T_DailySchedule)));

    m_pDailyScheduleEditor = new CDailyScheduleEditor(this, Qt::Window);
    connect(m_pDailyScheduleEditor, SIGNAL(sigSaveDailySchedule(T_DailySchedule))
            , ui->listView, SLOT(slotReqSaveDailySchedule(T_DailySchedule)));
    connect(ui->listView, SIGNAL(sigDailyScheduleEdit(T_DailySchedule))
            , m_pDailyScheduleEditor, SLOT(slot_showWithEdit(T_DailySchedule)));

    m_pSystemTrayIcon = new QSystemTrayIcon(QIcon(":/img/appIcon/app.ico"), this);
    connect(m_pSystemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason))
            , this, SLOT(slot_sysTrayIcon_activated(QSystemTrayIcon::ActivationReason)));

    QMenu* menu = new QMenu();
    QAction* actShowWindow = new QAction("桌面显示");
    connect(actShowWindow, SIGNAL(triggered(bool)), this, SLOT(slotShowWindows(bool)));
    QAction* actExitApp = new QAction("关闭程序");
    connect(actExitApp, SIGNAL(triggered(bool)), this, SLOT(slotExitApp(bool)));
    menu->addAction(actShowWindow);
    menu->addSeparator();
    menu->addAction(actExitApp);
    m_pSystemTrayIcon->setToolTip("日作息时间表");
    m_pSystemTrayIcon->setContextMenu(menu);
    m_pSystemTrayIcon->show();

    ui->laTitle->clear();

    //m_pMiniWidget = new CMiniWidget(this); // 有this主窗口最小化，子窗口也会跟随
    m_pMiniWidget = new CMiniWidget();
//    m_pMiniWidget->hide();
    m_pMiniWidget->slot_show("无");
    connect(ui->listViewSchedule, SIGNAL(sigCurScheduleChanged(QString))
            , m_pMiniWidget, SLOT(slot_show(QString)));

}

CDailyScheduleWidget::~CDailyScheduleWidget()
{
    delete ui;
    m_pMiniWidget->deleteLater();
}

void CDailyScheduleWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void CDailyScheduleWidget::changeEvent(QEvent *event)
{
//    //重点，窗口最小化时最小化窗口（废话），显示浮标
//        //窗口还原时，隐藏浮标，还原主窗口（这里是一个LABEL）
//        if(event->type()==QEvent::WindowStateChange)
//        {
//            //changeEvent会在窗口最小化之前调用，如果不加QTimer，
//            //我们把窗口隐藏了，但是Qt还以为窗口正要最小化，这样就会出错
//            if(windowState() & Qt::WindowMinimized)
//            {
//                //hide();
//                m_pMiniWidget->show("abcdefg");
//                qDebug() << __FUNCTION__;
//            }
////                QTimer::singleShot(0, this, SLOT(HideMainWindow()));
////            else if(windowState() & Qt::WindowNoState)
////                QTimer::singleShot(0, this, SLOT(ShowMainWindow()));
//        }
        QWidget::changeEvent(event);
}

void CDailyScheduleWidget::slot_sysTrayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
    if (QSystemTrayIcon::Trigger == reason)
    {
        show();
    }
}


void CDailyScheduleWidget::on_btnAdd_clicked()
{
    m_pDailyScheduleEditor->slot_showWithAdd();
}

void CDailyScheduleWidget::slotShowWindows(bool checked)
{
    show();
}

void CDailyScheduleWidget::slotExitApp(bool checked)
{
    QApplication::exit(0);
}

void CDailyScheduleWidget::slotLoadDailySchedule(const T_DailySchedule &tDailySchedule)
{
    ui->laTitle->setText(tDailySchedule.strScheduleName);
    ui->listViewSchedule->loadDailySchedule(tDailySchedule);
}


