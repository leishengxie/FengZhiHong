#include "DairyMainWindow.h"
#include "ui_DairyMainWindow.h"
#include "LoginWidget.h"
#include <QIcon>
#include "SkinWidget.h"
#include "model/DairyTagListModel.h"
#include "delegate/DairyTagDelegate.h"


CDairyMainWindow::CDairyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DairyMainWindow)
    , m_pSkinWidget(new CSkinWidget())
{
    ui->setupUi(this);
    setWindowTitle("LxDairy");
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    setPalette(pal);

    CDairyTagListModel* pDairyTagListModel = new CDairyTagListModel(this);
    CDairyTagDelegate* pDairyTagDelegate = new CDairyTagDelegate;
    ui->listViewTag->setModel(pDairyTagListModel);
    ui->listViewTag->setItemDelegate(pDairyTagDelegate);
}

CDairyMainWindow::~CDairyMainWindow()
{
    delete ui;
}

void CDairyMainWindow::closeEvent(QCloseEvent *event)
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("the File is changed");
        // 显示的文本
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        // 设置默认选中button
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Save:
            this->saveAsFileSlot();
            break;
        case QMessageBox::Discard:
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        default:
            break;
        }
    }
    else
    {
        event->accept();
    }
}



void CDairyMainWindow::setLoginWidget(CLoginWidget *pLoginWidget)
{
    m_pLoginWidget = pLoginWidget;
}


void CDairyMainWindow::openFileSlot()
{
    /*
     QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "/home",
                                                tr("Images (*.png *.xpm *.jpg)"));
    */
    QString fileName = QFileDialog:: getOpenFileName(this,"Open File",QDir::currentPath(),tr("*.png *.xpm *.jpg *.txt"));
    qDebug()<<"the fileName is"<<fileName;
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Please Select a Text File");
        return;
    }
    QFile *file = new QFile;
    file->setFileName(fileName); //set file name
    bool ok=file->open(QIODevice::ReadOnly);
    //open file as read only mode
    if(ok)
    {
        QTextStream in(file);
        ui->textEdit->setText(in.readAll()); //read all content from the file
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","File Open Error"+file->errorString());
        return;

    }
}


void CDairyMainWindow::saveAsFileSlot()
{
    QString saveFileName =QFileDialog::getSaveFileName(this,"save as file",QDir::currentPath(),tr("*.png;; *.xpm ;;*.jpg ;;*.txt"));
    if(saveFileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Please Select A File");
        return;
    }
    QFile *file=new QFile;
    file->setFileName(saveFileName);
    bool ok=file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText(); //去除textEdit当中的纯文本
        file->close();
        this->setWindowTitle(saveFileName+"----notepad");
        delete file;

    }
    else
    {
        QMessageBox::information(this,"Error Message","Save file fail");
        return;
    }
}



void CDairyMainWindow::currentDaateTimeSlot()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("yyyy-M-dd hh:mm:ss");
    ui->textEdit->append(time); //append:附加，贴上
}



void CDairyMainWindow::on_action_logout_triggered()
{
    m_pLoginWidget->show();
    deleteLater();
}

void CDairyMainWindow::on_action_new_dairy_triggered()
{
    // Modify:更改，修改
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"current text isModified";
    }
    else
    {
        qDebug()<<"Not isModified";
        ui->textEdit->clear();
        this->setWindowTitle("unTitle");
    }
}

void CDairyMainWindow::on_action_save_triggered()
{
    if(saveFileName.isEmpty())
    {
        this->saveAsFileSlot();
    }
    else
    {
        QFile *file=new QFile;
        file->setFileName(saveFileName);
        bool ok=file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText(); //去除textEdit当中的纯文本
            file->close();
            this->setWindowTitle(saveFileName+"----notepad");
            delete file;
        }
        else
        {
            QMessageBox::information(this,"Error Message","Save file fail");
            return;
        }
    }
}

void CDairyMainWindow::on_action_undo_triggered()
{

}

void CDairyMainWindow::on_action_cut_triggered()
{

}

void CDairyMainWindow::on_action_copy_triggered()
{
    ui->textEdit->copy();
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
            ui->textEdit->setTextColor(color);
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
    ui->textEdit->clear();
    close();
}

void CDairyMainWindow::on_action_font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,QFont("Helvetica [Cronyx]", 10),this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"Error Message","set font fail");
    }
}
