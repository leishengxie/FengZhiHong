#include "DairyEditMainWidget.h"
#include "ui_DairyEditMainWidget.h"

#include "DairyEdit.h"
#include "DairyEditWidget.h"
#include "SqlOperate.h"

#include <QMdiSubWindow>
#include <QtDebug>

CDairyEditMainWidget::CDairyEditMainWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CDairyEditMainWidget)
{
    ui->setupUi(this);

    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(slotUpdateMenu(QMdiSubWindow*)));

}

CDairyEditMainWidget::~CDairyEditMainWidget()
{
    delete ui;
}



void CDairyEditMainWidget::saveDairy()
{
    QMdiSubWindow* pMdiSubWindow = ui->mdiArea->currentSubWindow();
    if (pMdiSubWindow == NULL)
    {
        return;
    }
    CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
    pDairyEditWidget->onSave();
}

void CDairyEditMainWidget::saveAllDairy()
{
    QList<QMdiSubWindow*> lstSubWindow = ui->mdiArea->subWindowList();
    foreach (QMdiSubWindow* pMdiSubWindow, lstSubWindow)
    {
        CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
        pDairyEditWidget->onSave();
    }
}

bool CDairyEditMainWidget::closeAllSubWindows()
{
    // 作为顶层窗口时用，不是顶层窗口无意义
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())
    {
        return false;
    }
    return true;
}


void CDairyEditMainWidget::slotUpdateMenu(QMdiSubWindow* pMdiSubWindow)
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



void CDairyEditMainWidget::slot_displayDairy(const CDairy & dairy)
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
        connect(pDairyEditWidget, SIGNAL(saveDairyfinished(CDairy, CDairy)), this, SIGNAL(saveDairyfinishedS1(CDairy,CDairy)));
        QMdiSubWindow* pSubWindow = ui->mdiArea->addSubWindow(pDairyEditWidget);
        pSubWindow->showMaximized();
    }
    else
    {
        ui->mdiArea->setActiveSubWindow(pMdiSubWindowDest);
    }

}

void CDairyEditMainWidget::on_btnTTSPlay_clicked()
{
    QMdiSubWindow* pMdiSubWindow = ui->mdiArea->activeSubWindow();
    if (pMdiSubWindow == NULL)
    {
        return;
    }


    CDairyEditWidget* pDairyEditWidget = qobject_cast<CDairyEditWidget*>(pMdiSubWindow->widget());
    QString strContent = pDairyEditWidget->dairyEdit()->toPlainText();
    emit requireTTSspeak(strContent);
}

void CDairyEditMainWidget::on_btnPlayMusic_clicked()
{
    emit requirePlayMusic();
}
