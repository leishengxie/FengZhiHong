#include "DairyMainWindow.h"
#include "ui_DairyMainWindow.h"

#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QCloseEvent>

#include "LoginWidget.h"
#include "SkinWidget.h"
#include "User.h"
#include "music/LMusicPlayer.h"
#include "AboutDialog.h"
#include "DairyApp.h"
#include "LEvent.h"


CDairyMainWindow::CDairyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DairyMainWindow)
    , m_pSkinWidget(new CSkinWidget())
{
    ui->setupUi(this);
    setWindowTitle("LxDairy - " + CUser::getInstance()->getUserName());

    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    setPalette(pal);


    // 音乐播放模块
    statusBar()->addWidget((QWidget*)ui->tabDairy->musicPlayer()->getLrcWidget());
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

void CDairyMainWindow::closeEvent(QCloseEvent *event)
{
    //CDairyApp::postEvent(ui->tabDairy, (QEvent *)event);
    if(ui->tabDairy->closeAllSubWindows())
    {
        event->accept();//关闭
    }
    else
    {
        event->ignore();
    }
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
    CDairyApp::postEvent(ui->tabDairy, new CSaveEvent());

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
    ui->tabDairy->saveAllDairy();
}


// music setting
void CDairyMainWindow::on_action_music_triggered()
{
   ui->tabDairy->musicPlayer()->showSetting();
}



