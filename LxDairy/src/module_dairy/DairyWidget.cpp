#include "DairyWidget.h"
#include "ui_DairyWidget.h"
#include "model/DairyTagListModel.h"
#include "model/DairyDateTreeModel.h"
#include "model/DairyStatisticsModel.h"
#include "delegate/DairyTagDelegate.h"
#include "delegate/DairyDateDelegate.h"
#include "delegate/DairyStatisticsDelegate.h"
#include "DairyEdit.h"
#include "DairyEditWidget.h"
#include "music/LMusicPlayer.h"
#include "tts/windows/LWindowsTTSS.h"
#include "SqlOperate.h"

#include <QIcon>
#include <QtDebug>
#include <QMdiSubWindow>
#include <QTimer>
#include <QCloseEvent>

CDairyWidget::CDairyWidget(QWidget* parent)
    : CLBaseWidget(parent)
    , ui(new Ui::CDairyWidget)
    , m_pMusicPlayer(new CLMusicPlayer(this, this))
{
    ui->setupUi(this);

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

    //connect(ui->treeDairy, SIGNAL(clicked(QModelIndex))

    // 初始化日记统计
    ui->btnOpenDairy->hide();

    CDairyStatisticsModel* pDairyStatisticsModel = new CDairyStatisticsModel(this);
    CDairyStatisticsDelegate* pDairyStatisticsDelegate = new CDairyStatisticsDelegate;
    ui->listViewStatistics->setModel(pDairyStatisticsModel);
    ui->listViewStatistics->setItemDelegate(pDairyStatisticsDelegate);
    connect(ui->listViewStatistics->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this, SLOT(slotSelectionChanged(QItemSelection, QItemSelection)));


    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(slotUpdateMenu(QMdiSubWindow*)));
    //ui->mdiArea->cascadeSubWindows(); //MDI区域内的所有子窗口重叠排列
    //ui->mdiArea->tileSubWindows(); //将所有子窗口在MDI区域内排列整齐
    //QMdiArea::AreaOption option;
    //ui->mdiArea->setOption(option, true);
    //connect(ui->mdiArea, SIGNAL(customContextMenuRequested(QPoint))

    //tts
    m_pITTS = new CLWindowsTTSS(this);
    m_pITTS->initSpeech();

    // 等所有初始化完成
    QTimer::singleShot(1000, [ = ]()
    {
        pDairyDateTreeModel->loadAllDairy();
    });


    // 测试stackwidget 切换时界面刷新效率
//        ui->calendarWidget->hide();
//        //ui->treeDairy->hide();
//        //ui->listViewTag->hide();
//        ui->stackedWidget->hide();
//        QStack s;
//                QStackedWidget t;
//                QStackedLayout d;

}

CDairyWidget::~CDairyWidget()
{
    delete ui;
}



void CDairyWidget::saveDairy()
{
    QMdiSubWindow* pMdiSubWindow = ui->mdiArea->currentSubWindow();
    if (pMdiSubWindow == NULL)
    {
        return;
    }
    CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
    pDairyEditWidget->onSave();
}

void CDairyWidget::saveAllDairy()
{
    QList<QMdiSubWindow*> lstSubWindow = ui->mdiArea->subWindowList();
    foreach (QMdiSubWindow* pMdiSubWindow, lstSubWindow)
    {
        CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
        pDairyEditWidget->onSave();
    }
}

bool CDairyWidget::closeAllSubWindows()
{
    // 作为顶层窗口时用，不是顶层窗口无意义
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())
    {
        return false;
    }
    return true;
}

// 当前控件作为顶层窗口时用，不是顶层窗口无意义
// 父类 与 父对象
void CDairyWidget::closeEvent(QCloseEvent* event)
{
    if (!isWindow())
    {
        event->accept();//关闭
        return;
    }

    if(closeAllSubWindows())
    {
        event->accept();//关闭
    }
    else
    {
        event->ignore();
    }
}

void CDairyWidget::actSaveEvent()
{
    qDebug() << "-----actSaveEvent()";
    saveDairy();
}

void CDairyWidget::slot_displayDairy(const CDairy & dairy)
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
    QMdiSubWindow* pMdiSubWindowDest = NULL;
    QList<QMdiSubWindow*> lstSubWindow = ui->mdiArea->subWindowList();
    foreach (QMdiSubWindow* pMdiSubWindow, lstSubWindow)
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
        connect(pDairyEditWidget, SIGNAL(saveDairyfinished(CDairy, CDairy)), this, SLOT(onSaveDairyfinished(CDairy, CDairy)));
        QMdiSubWindow* pSubWindow = ui->mdiArea->addSubWindow(pDairyEditWidget);
        pSubWindow->showMaximized();
    }
    else
    {
        ui->mdiArea->setActiveSubWindow(pMdiSubWindowDest);
    }

}

void CDairyWidget::onRequireExpand(const QModelIndex & index)
{
    ui->treeDairy->expand(index);
    QList<QModelIndex> lstIndex;
    QModelIndex indexParent = index.parent();
    while (indexParent.isValid())
    {
        lstIndex.push_front(indexParent);
        indexParent = indexParent.parent();
    }
    for(QModelIndex index : lstIndex)
    {
        ui->treeDairy->expand(index);
    }
    on_treeDairy_clicked(index);

}

void CDairyWidget::slotUpdateMenu(QMdiSubWindow* pMdiSubWindow)
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
void CDairyWidget::slotSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    Q_UNUSED(deselected)
    int nSelected = selected.indexes().size();
    qDebug() << "nSelected：" << nSelected;
    if (nSelected == 1)
    {
        ui->btnOpenDairy->show();
    }
    else
    {
        ui->btnOpenDairy->hide();
    }
    QItemSelectionModel* selectionModel = ui->listViewStatistics->selectionModel();
    QModelIndexList listSelected = selectionModel->selectedIndexes();
    qDebug() << QString("%1 item selected").arg(listSelected.size()); //不能用items,即使是没有选择的数目也不对
}


void CDairyWidget::onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved)
{
    ((CDairyDateTreeModel*)ui->treeDairy->model())->dairyModify(dairySaveBefore, dairySaved);
}


void CDairyWidget::on_treeDairy_clicked(const QModelIndex & index)
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
                //ui->btnOpenDairy->setEnabled(false);
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
                //ui->btnOpenDairy->setEnabled(false);
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



void CDairyWidget::on_btnOpenDairy_clicked()
{
    QModelIndex indexCur = ui->listViewStatistics->currentIndex();
    T_DairyStatisticsItem tDairyStatisticsItem = qvariant_cast<T_DairyStatisticsItem>(indexCur.data());
    ((CDairyDateTreeModel*)ui->treeDairy->model())->expandDairy(tDairyStatisticsItem.did);
}

void CDairyWidget::on_listViewTag_clicked(const QModelIndex & index)
{
    ui->btnOpenDairy->hide();
    //ui->btnOpenDairy->setEnabled(false);
    ui->mdiArea->closeAllSubWindows();
    ui->stackedWidget->setCurrentIndex(1);
    T_DairyTagItem tDairyTagItem = qvariant_cast<T_DairyTagItem>(index.data());
    ((CDairyDateTreeModel*)ui->treeDairy->model())->reloadDairyByTag(tDairyTagItem.strTagName);
    QString strQueryTag = ("全部日记" == tDairyTagItem.strTagName) ? "" : tDairyTagItem.strTagName;
    QList<CDairy> lstDairy = CSqlOperate::getListDairyByLimit("", strQueryTag);
    ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
    ui->labelDairyTotal->setText(QString("(共%1项)").arg(lstDairy.size()));
    ui->labelTitle->setText(tDairyTagItem.strTagName);

}

void CDairyWidget::on_calendarWidget_clicked(const QDate & date)
{

}






void CDairyWidget::on_btnTTSPlay_clicked()
{
    QMdiSubWindow* pMdiSubWindow = ui->mdiArea->activeSubWindow();
    if (pMdiSubWindow == NULL)
    {
        return;
    }
    // 停止音乐播放
    //m_pMusicPlayer->stop();

    CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
    QString strContent = pDairyEditWidget->dairyEdit()->toPlainText();
    m_pITTS->speak(strContent);

}

void CDairyWidget::on_btnPlayMusic_clicked()
{
    m_pMusicPlayer->onPlay();
}
