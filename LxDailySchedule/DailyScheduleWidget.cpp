#include "DailyScheduleWidget.h"
#include "ui_DailyScheduleWidget.h"
#include "MiniWidget.h"
#include "DailyScheduleEditor.h"
#include <QMenu>
#include <QCloseEvent>

CDailyScheduleWidget::CDailyScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDailyScheduleWidget)
{
    ui->setupUi(this);
    connect(ui->listView, SIGNAL(sigBookClicked(T_DailySchedule))
            , ui->tableView, SLOT(slotLoadDailySchedule(T_DailySchedule)));

    m_pMiniWidget = new CMiniWidget(this);
    m_pMiniWidget->hide();

    m_pDailyScheduleEditor = new CDailyScheduleEditor(this, Qt::Window);
    connect(m_pDailyScheduleEditor, SIGNAL(sigSaveDailySchedule(T_DailySchedule))
            , ui->listView, SLOT(slotReqSaveDailySchedule(T_DailySchedule)));

    m_pSystemTrayIcon = new QSystemTrayIcon(QIcon(":/img/tool_img/maple_leaf_book.png"), this);
    connect(m_pSystemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason))
            , this, SLOT(on_sysTrayIcon_activated(QSystemTrayIcon::ActivationReason)));

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

}

CDailyScheduleWidget::~CDailyScheduleWidget()
{
    delete ui;
}

void CDailyScheduleWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
    m_pSystemTrayIcon->show();
}

void CDailyScheduleWidget::changeEvent(QEvent *event)
{
    //重点，窗口最小化时最小化窗口（废话），显示浮标
        //窗口还原时，隐藏浮标，还原主窗口（这里是一个LABEL）
        if(event->type()==QEvent::WindowStateChange)
        {
            //changeEvent会在窗口最小化之前调用，如果不加QTimer，
            //我们把窗口隐藏了，但是Qt还以为窗口正要最小化，这样就会出错
            if(windowState() & Qt::WindowMinimized)
            {
                hide();
                m_pMiniWidget->showText("abcdefg");
                m_pMiniWidget->show();
            }
//                QTimer::singleShot(0, this, SLOT(HideMainWindow()));
//            else if(windowState() & Qt::WindowNoState)
//                QTimer::singleShot(0, this, SLOT(ShowMainWindow()));
        }
        QWidget::changeEvent(event);
}

void CDailyScheduleWidget::on_sysTrayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
    if (QSystemTrayIcon::Trigger == reason)
    {
        show();
    }
}


void CDailyScheduleWidget::on_btnAdd_clicked()
{
    m_pDailyScheduleEditor->showWithAdd();
}

void CDailyScheduleWidget::slotShowWindows(bool checked)
{
    show();
}

void CDailyScheduleWidget::slotExitApp(bool checked)
{
    QApplication::exit(0);
}


