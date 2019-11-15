#include "DairyMainWindow.h"
#include "ui_DairyMainWindow.h"
#include <QIcon>
#include <QtDebug>
#include <QMdiSubWindow>
#include <QTimer>
#include "LoginWidget.h"
#include "SqlOperate.h"
#include "SkinWidget.h"
#include "User.h"
#include "music/LMusicPlayer.h"
#include "tts/windows/LWindowsTTSS.h"


CDairyMainWindow::CDairyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DairyMainWindow)
    , m_pSkinWidget(new CSkinWidget())
    , m_pMusicPlayer(new CLMusicPlayer(this, this))
{
    ui->setupUi(this);
    setWindowTitle("LxDairy - " + CUser::getInstance()->getUserName());
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    setPalette(pal);


    // 音乐播放模块
    statusBar()->addWidget((QWidget*)m_pMusicPlayer->getLrcWidget());
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));


}

CDairyMainWindow::~CDairyMainWindow()
{

    delete ui;
}



void CDairyMainWindow::resizeEvent(QResizeEvent *event)
{
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    setPalette(pal);
}



void CDairyMainWindow::setLoginWidget(CLoginWidget *pLoginWidget)
{
    m_pLoginWidget = pLoginWidget;
}


void CDairyMainWindow::on_action_logout_triggered()
{
    m_pLoginWidget->show();
    deleteLater();
}

void CDairyMainWindow::on_action_new_dairy_triggered()
{
    // 今天的日记已经创建了，过去的不能再创建
}

void CDairyMainWindow::on_action_save_triggered()
{

    // 个人隐私, 已经连接信号槽


    // 日记部分
    QMdiSubWindow* pMdiSubWindow = ui->mdiArea->currentSubWindow();
    if (pMdiSubWindow == NULL)
    {
        return;
    }
    CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
    pDairyEditWidget->onSave();

}

void CDairyMainWindow::on_action_undo_triggered()
{

}

void CDairyMainWindow::on_action_cut_triggered()
{

}

void CDairyMainWindow::on_action_copy_triggered()
{

}

void CDairyMainWindow::on_action_paste_triggered()
{

}

void CDairyMainWindow::on_action_color_triggered()
{
    //    const QColorDialog::ColorDialogOptions options = QFlag(colorDialogOptionsWidget->value());
    //        const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);
        QColor color = QColorDialog::getColor(Qt::green,this);
        if(color.isValid())
        {
            //ui->textEdit->setTextColor(color);
        }
        else
        {
            QMessageBox::information(this,"Error Message","set color fail");
        }
}

void CDairyMainWindow::on_action_redo_triggered()
{

}

void CDairyMainWindow::on_action_about_triggered()
{
    CAboutDialog dialog(this);
    //dialog->show(); //unmodal dialog;
    dialog.exec();    //modal dialog
    //QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
}

void CDairyMainWindow::on_action_lock_triggered()
{

}

void CDairyMainWindow::on_action_tool_triggered()
{

}

void CDairyMainWindow::on_action_skin_triggered()
{
    m_pSkinWidget->show();
}

void CDairyMainWindow::on_action_exit_triggered()
{
    //ui->textEdit->clear();
    close();
}

void CDairyMainWindow::on_action_font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,QFont("Helvetica [Cronyx]", 10),this);
    if(ok)
    {
        //ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"Error Message","set font fail");
    }
}


void CDairyMainWindow::on_action_save_all_triggered()
{
    QList<QMdiSubWindow *> lstSubWindow = ui->mdiArea->subWindowList();
    foreach (QMdiSubWindow *pMdiSubWindow, lstSubWindow)
    {
        CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
        pDairyEditWidget->onSave();
    }
}


// setting
void CDairyMainWindow::on_action_music_triggered()
{
   m_pMusicPlayer->showSetting();
}



