#include "DairyMainWindow.h"
#include "ui_mainwindow.h"
#include <QIcon>



CDairyMainWindow::CDairyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DairyMainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("MyNotepad");
    this->setWindowIcon(QIcon(":new/icon/icon/1440x900_94.jpg"));
    //trigger:引发，触发
    QObject::connect(ui->action_N,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    QObject::connect(ui->action_O,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    QObject::connect(ui->action_S_2,SIGNAL(triggered()),this,SLOT(saveFileSlot()));
    QObject::connect(ui->action_X,SIGNAL(triggered()),this,SLOT(exitFileSlot()));
    QObject::connect(ui->action_P,SIGNAL(triggered()),this,SLOT(printFileSlot()));
    QObject::connect(ui->action_F,SIGNAL(triggered()),this,SLOT(setFontSlot()));
    QObject::connect(ui->action_C_2,SIGNAL(triggered()),this,SLOT(setColorSlot()));
    QObject::connect(ui->action_D,SIGNAL(triggered()),this,SLOT(currentDaateTimeSlot()));
    QObject::connect(ui->action_C,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));
    QObject::connect(ui->action_P_2,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    QObject::connect(ui->action_T,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));
    QObject::connect(ui->action_H,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));
    QObject::connect(ui->action_U_2,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));
    QObject::connect(ui->action_Qt_A,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    QObject::connect(ui->action_AW,SIGNAL(triggered()),this,SLOT(aboutWebServicesSlot()));
    QObject::connect(ui->action_AS,SIGNAL(triggered()),this,SLOT(aboutSoftwareSlot()));

}

void CDairyMainWindow::closeEvent(QCloseEvent *event)
{
    // event->ignore();
    //event->accept();
    /*
     switch (ret) {
  case QMessageBox::Save:// Save was clicked
      break;
  case QMessageBox::Discard:// Don't Save was clicked
      break;
  case QMessageBox::Cancel:// Cancel was clicked
      break;
  default:// should never be reached
      break;
}
    */
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("the File is changed");
        //msgBox.setText("文件已经改变了");
        //显示的文本
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save); //设置默认选中button
        int ret=msgBox.exec();
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

CDairyMainWindow::~CDairyMainWindow()
{
    delete ui;
}
void CDairyMainWindow::  newFileSlot()
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

void CDairyMainWindow::saveFileSlot()
{
    if(saveFileName.isEmpty())
    {
        this->saveAsFileSlot();
    }
    else {
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
void CDairyMainWindow:: exitFileSlot()
{
    ui->textEdit->clear();
    this->close();
}
void CDairyMainWindow::printFileSlot()
{
    //


}
void CDairyMainWindow::setFontSlot()
{
    /*
    bool ok;
    QFont font = QFontDialog::getFont(
                    &ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        // the user clicked OK and font is set to the font the user selected
    } else {
        // the user canceled the dialog; font is set to the initial
        // value, in this case Helvetica [Cronyx], 10
    }
    */
    //get user select font
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
void CDairyMainWindow::setColorSlot()
{
    /*
    const QColorDialog::ColorDialogOptions options = QFlag(colorDialogOptionsWidget->value());
        const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);

        if (color.isValid()) {
            colorLabel->setText(color.name());
            colorLabel->setPalette(QPalette(color));
            colorLabel->setAutoFillBackground(true);
        }
     */
    //options:选择
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
void CDairyMainWindow::currentDaateTimeSlot()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("yyyy-M-dd hh:mm:ss");
    ui->textEdit->append(time); //append:附加，贴上
}

void CDairyMainWindow::aboutWebServicesSlot()
{
   QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
}

void CDairyMainWindow::aboutSoftwareSlot()
{
    CAboutDialog *dialog=new CAboutDialog;
    dialog->show(); //unmodal dialog;
    //dialog.exec()    modal dialog
}


