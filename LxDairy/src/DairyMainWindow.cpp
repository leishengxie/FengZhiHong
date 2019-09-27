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
    connect(pDairyDateTreeModel, SIGNAL(requireExpand(QModelIndex)), this, SLOT(onRequireExpand(QModelIndex)));
    pDairyDateTreeModel->loadAllDairy();
    //connect(ui->treeDairy, SIGNAL(clicked(QModelIndex))


    CDairyStatisticsModel* pDairyStatisticsModel = new CDairyStatisticsModel(this);
    CDairyStatisticsDelegate* pDairyStatisticsDelegate = new CDairyStatisticsDelegate;
    ui->listViewStatistics->setModel(pDairyStatisticsModel);
    ui->listViewStatistics->setItemDelegate(pDairyStatisticsDelegate);
    connect(ui->listViewStatistics->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(slotSelectionChanged(QItemSelection,QItemSelection)));


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
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())
    {
        event->ignore();
    }
    else
    {
        event->accept();//关闭
    }
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
        m_dairyActive = dairy;
    }
    else
    {
        bool bOk = false;
        m_dairyActive = CSqlOperate::getDairy(dairy.getDid(), bOk);
        if (!bOk)
        {
            // print error
            return;
        }
    }

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
    connect(pDairyEditWidget, SIGNAL(saveDairyfinished(CDairy,CDairy)), this, SLOT(onSaveDairyfinished(CDairy,CDairy)));
    QMdiSubWindow * pSubWindow = ui->mdiArea->addSubWindow(pDairyEditWidget);
    pSubWindow->showMaximized();
    }
    else
    {
        ui->mdiArea->setActiveSubWindow(pMdiSubWindowDest);
    }

}

void CDairyMainWindow::onRequireExpand(const QModelIndex &index)
{
    ui->treeDairy->expand(index);
    QList<QModelIndex> lstIndex;
    QModelIndex indexParent = index.parent();
    while (indexParent.isValid())
    {
        lstIndex.push_front(indexParent);
        indexParent = indexParent.parent();
    }
    for(QModelIndex index: lstIndex)
    {
        ui->treeDairy->expand(index);
    }
    on_treeDairy_clicked(index);

}



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


///
/// \brief CDairyMainWindow::slotSelectionChanged
/// \param selected 新选择的项目
/// \param deselected 刚刚被取消选择的项目
///
void CDairyMainWindow::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected)
    int nSelected = selected.indexes().size();
    qDebug() << "nSelected：" << nSelected;
    if (nSelected == 1)
    {
        ui->btnOpenDairy->setEnabled(true);
    }
    else
    {
        ui->btnOpenDairy->setEnabled(false);
    }
    QItemSelectionModel *selectionModel = ui->listViewStatistics->selectionModel();
    QModelIndexList listSelected = selectionModel->selectedIndexes();
    qDebug() << QString("%1 item selected").arg(listSelected.size()); //不能用items,即使是没有选择的数目也不对

}

void CDairyMainWindow::onSaveDairyfinished(const CDairy &dairySaveBefore, const CDairy &dairySaved)
{
    ((CDairyDateTreeModel*)ui->treeDairy->model())->dairyModify(dairySaveBefore, dairySaved);
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
//    CSqlOperate::test();
//    return;
    //
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

void CDairyMainWindow::on_treeDairy_clicked(const QModelIndex &index)
{
    qDebug() << "tree click " << "row=" << index.row() << " column=" << index.column();
    T_DairyDateItem* tDairyTagItem = qvariant_cast<T_DairyDateItem*>(index.data());
    switch (tDairyTagItem->eDairyDateNodeType)
    {
    case ED_Year:
    {
        QList<CDairy> lstDairy = CSqlOperate::getListDairyByLimit(tDairyTagItem->strYear);
        ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
        ui->labelDairyTotal->setText(QString("(共%1项)").arg(lstDairy.size()));
        ui->labelTitle->setText(QString("%1年的日记").arg(tDairyTagItem->strYear));
        ui->btnOpenDairy->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(1);
        break;
    }
    case ED_Month:
    {
        QString strDate = QString("%1-%2").arg(tDairyTagItem->strYear).arg(tDairyTagItem->strMonth);
        QList<CDairy> lstDairy = CSqlOperate::getListDairyByLimit(strDate);
        ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
        ui->labelDairyTotal->setText(QString("(共%1项)").arg(lstDairy.size()));
        ui->labelTitle->setText(QString("%1年%2月的日记").arg(tDairyTagItem->strYear).arg(tDairyTagItem->strMonth));
        ui->btnOpenDairy->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(1);
        break;
    }
    case ED_Day:
    {
        CDairy dairy;
        dairy.setDid(tDairyTagItem->did);
        slot_displayDairy(dairy);
        ui->stackedWidget->setCurrentIndex(0);
        break;
    }
    default:
        break;
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

void CDairyMainWindow::on_btnOpenDairy_clicked()
{
    QModelIndex indexCur = ui->listViewStatistics->currentIndex();
    T_DairyStatisticsItem tDairyStatisticsItem = qvariant_cast<T_DairyStatisticsItem>(indexCur.data());
    ((CDairyDateTreeModel*)ui->treeDairy->model())->expandDairy(tDairyStatisticsItem.did);
}

void CDairyMainWindow::on_listViewTag_clicked(const QModelIndex &index)
{
    ui->mdiArea->closeAllSubWindows();
    ui->stackedWidget->setCurrentIndex(1);
    T_DairyTagItem tDairyTagItem = qvariant_cast<T_DairyTagItem>(index.data());
    ((CDairyDateTreeModel*)ui->treeDairy->model())->reloadDairyByTag(tDairyTagItem.strTagName);
    QString strQueryTag = ("全部日记" == tDairyTagItem.strTagName) ? "" : tDairyTagItem.strTagName;
    QList<CDairy> lstDairy = CSqlOperate::getListDairyByLimit("", strQueryTag);
    ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
    ui->labelDairyTotal->setText(QString("(共%1项)").arg(lstDairy.size()));
    ui->labelTitle->setText(tDairyTagItem.strTagName);
    ui->btnOpenDairy->setEnabled(false);
}

void CDairyMainWindow::on_calendarWidget_clicked(const QDate &date)
{

}
