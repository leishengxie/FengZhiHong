#include "DairyMainWindow.h"
#include "ui_DairyMainWindow.h"
#include <QIcon>
#include <QtDebug>
#include <QMdiSubWindow>
#include "LoginWidget.h"
#include "SqlOperate.h"
#include "SkinWidget.h"
#include "model/DairyTagListModel.h"
#include "model/DairyDateTreeModel.h"
#include "model/DairyStatisticsModel.h"
#include "delegate/DairyTagDelegate.h"
#include "delegate/DairyDateDelegate.h"
#include "delegate/DairyStatisticsDelegate.h"
#include "User.h"
#include "DairyEdit.h"
#include "DairyEditWidget.h"


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

    // 初始化listViewTag
    CDairyTagListModel* pDairyTagListModel = new CDairyTagListModel(this);
    CDairyTagDelegate* pDairyTagDelegate = new CDairyTagDelegate;
    ui->listViewTag->setModel(pDairyTagListModel);
    ui->listViewTag->setItemDelegate(pDairyTagDelegate);


    // 初始化pDairyDateTreeModel
    CDairyDateTreeModel* pDairyDateTreeModel = new CDairyDateTreeModel(this);
    CDairyDateDelegate* pDairyDateDelegate = new CDairyDateDelegate;
    ui->treeDairy->setModel(pDairyDateTreeModel);
    ui->treeDairy->setItemDelegate(pDairyDateDelegate);
    connect(pDairyDateTreeModel, SIGNAL(loadTodayDairyFinished(CDairy)), this, SLOT(slot_displayDairy(CDairy)));
    pDairyDateTreeModel->loadDairy();
    //connect(ui->treeDairy, SIGNAL(clicked(QModelIndex))

    CDairyStatisticsModel* pDairyStatisticsModel = new CDairyStatisticsModel(this);
    CDairyStatisticsDelegate* pDairyStatisticsDelegate = new CDairyStatisticsDelegate;
    ui->listViewStatistics->setModel(pDairyStatisticsModel);
    ui->listViewStatistics->setItemDelegate(pDairyStatisticsDelegate);

    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(slotUpdateMenu(QMdiSubWindow*)));
    //ui->mdiArea->cascadeSubWindows(); //MDI区域内的所有子窗口重叠排列
    //ui->mdiArea->tileSubWindows(); //将所有子窗口在MDI区域内排列整齐
    //QMdiArea::AreaOption option;
    //ui->mdiArea->setOption(option, true);
    //connect(ui->mdiArea, SIGNAL(customContextMenuRequested(QPoint))

}

CDairyMainWindow::~CDairyMainWindow()
{
    delete ui;
}

void CDairyMainWindow::closeEvent(QCloseEvent *event)
{
    //QMainWindow::closeEvent(event);
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())
    {
        event->ignore();
    }
    else
    {
        event->accept();//关闭
    }
//    if(ui->textEdit->document()->isModified())
//    {
//        QMessageBox msgBox;
//        msgBox.setText("the File is changed");
//        // 显示的文本
//        msgBox.setInformativeText("Do you want to save your changes?");
//        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//        // 设置默认选中button
//        msgBox.setDefaultButton(QMessageBox::Save);
//        int ret = msgBox.exec();
//        switch (ret)
//        {
//        case QMessageBox::Save:
//            on_action_save_triggered();
//            break;
//        case QMessageBox::Discard:
//            event->accept();
//            break;
//        case QMessageBox::Cancel:
//            event->ignore();
//            break;
//        default:
//            break;
//        }
//    }
//    else
//    {
//        event->accept();
//    }
}



void CDairyMainWindow::setLoginWidget(CLoginWidget *pLoginWidget)
{
    m_pLoginWidget = pLoginWidget;
}

void CDairyMainWindow::slot_displayDairy(const CDairy &dairy)
{
    // 确定日记
    if (dairy.isNewDairy())
    {
        m_dairyActive = CDairy();
    }
    m_dairyActive = dairy;

    // 根据did确定是否已经加载了edit，否则创建新的edit
    bool bNeedCreateEdit = true;
    QMdiSubWindow *pMdiSubWindowDest = NULL;
    QList<QMdiSubWindow *> lstSubWindow = ui->mdiArea->subWindowList();
    foreach (QMdiSubWindow *pMdiSubWindow, lstSubWindow)
    {
        CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
        if (pDairyEditWidget->getDid() == m_dairyActive.getDid())
        {
            bNeedCreateEdit = false;
            pMdiSubWindowDest = pMdiSubWindow;
            break;
        }
    }

    if (bNeedCreateEdit)
    {
    // 创建edit
    CDairyEditWidget* pDairyEditWidget = new CDairyEditWidget(m_dairyActive);
    QMdiSubWindow * pSubWindow = ui->mdiArea->addSubWindow(pDairyEditWidget);
    pSubWindow->showMaximized();
    }
    else
    {
        ui->mdiArea->setActiveSubWindow(pMdiSubWindowDest);
    }

}

/*
void CDairyMainWindow::openFileSlot()
{
//     QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
//                                                "/home",
//                                                tr("Images (*.png *.xpm *.jpg)"));
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
*/

/*
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
*/



void CDairyMainWindow::slotUpdateMenu(QMdiSubWindow* pMdiSubWindow)
{
    // 关闭时会调用当前函数，指针为NULL
    bool bHasActiveWindow = pMdiSubWindow == NULL ? false : true;
    QString str = bHasActiveWindow ? "NOT NULL" : "NULL";
    qDebug() << "slotUpdateMenu " << str;
    //QMdiSubWindow *active_sub_window = ui->mdiArea->activeSubWindow();


    /*
    ui->action_save->setEnabled(bHasActiveWindow);
    ui->action_paste->setEnabled(bHasActiveWindow);

    CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
    bool bHasTextSelection = pDairyEditWidget->dairyEdit()->textCursor().hasSelection();
    ui->action_cut->setEnabled(bHasTextSelection);
    ui->action_copy->setEnabled(bHasTextSelection);

    //有活动窗口，且系统判断可以执行撤销操作时才显示撤销可用,判断恢复操作可执行时恢复操作才可用
    ui->action_undo->setEnabled(pDairyEditWidget && pDairyEditWidget->dairyEdit()->document()->isUndoAvailable());
    ui->action_redo->setEnabled(pDairyEditWidget && pDairyEditWidget->dairyEdit()->document()->isRedoAvailable());
    */
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

void CDairyMainWindow::on_treeDairy_clicked(const QModelIndex &index)
{
    qDebug() << "tree click";
    T_DairyDateItem tDairyTagItem = qvariant_cast<T_DairyDateItem>(index.data());
    switch (tDairyTagItem.eDairyDateNodeType)
    {
    case ED_Year:
    {
        QList<CDairy> lstDairy = CSqlOperate::getListDairyByDate(tDairyTagItem.strYear);
        ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
        ui->stackedWidget->setCurrentIndex(1);
        break;
    }
    case ED_Month:
    {
        QString strDate = QString("%1-%2").arg(tDairyTagItem.strYear).arg(tDairyTagItem.strMonth);
        QList<CDairy> lstDairy = CSqlOperate::getListDairyByDate(strDate);
        ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
        ui->stackedWidget->setCurrentIndex(1);
        break;
    }
    case ED_Day:
    {
        CDairy dairy;
        if (tDairyTagItem.did != INVAILD_DAIRY_ID)
        {
            bool bOk = false;
            dairy = CSqlOperate::getDairy(tDairyTagItem.did, bOk);
            if (!bOk)
            {
                // print error
            }
        }
        slot_displayDairy(dairy);
        ui->stackedWidget->setCurrentIndex(0);
        break;
    }
    default:
        break;
    }


}
