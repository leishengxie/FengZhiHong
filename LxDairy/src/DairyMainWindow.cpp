#include "DairyMainWindow.h"
#include "ui_DairyMainWindow.h"
#include <QIcon>
#include <QtDebug>
#include <QMdiSubWindow>
#include <QSqlTableModel>
#include <QSqlError>
#include <QTimer>
#include "LoginWidget.h"
#include "SqlOperate.h"
#include "SkinWidget.h"
#include "model/DairyTagListModel.h"
#include "model/DairyDateTreeModel.h"
#include "model/DairyStatisticsModel.h"
#include "model/PrivateMenuModel.h"
#include "delegate/DairyTagDelegate.h"
#include "delegate/DairyDateDelegate.h"
#include "delegate/DairyStatisticsDelegate.h"
#include "User.h"
#include "DairyEdit.h"
#include "DairyEditWidget.h"
#include "music/LMusicPlayer.h"
#include "MusicSettingDialog.h"
#include "tts/windows/LWindowsTTSS.h"
#include "tool_rename/RenameWidget.h"

CDairyMainWindow::CDairyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DairyMainWindow)
    , m_pSkinWidget(new CSkinWidget())
    , m_pMusicPlayer(new CLMusicPlayer(this, this))
    , m_pMusicSettingDialog(new CMusicSettingDialog())
{
    ui->setupUi(this);
    setWindowTitle("LxDairy - " + CUser::getInstance()->getUserName());
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    setPalette(pal);

    initPageDairy();
    initPagePrivate();

}

CDairyMainWindow::~CDairyMainWindow()
{
    m_pMusicSettingDialog->deleteLater();
    delete ui;
}

void CDairyMainWindow::initPageDairy()
{
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


    // 音乐播放模块
    statusBar()->addWidget((QWidget*)m_pMusicPlayer->getLrcWidget());
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    //tts
    m_pITTS = new CLWindowsTTSS(this);
    m_pITTS->initSpeech();

    // 等所有初始化完成
    QTimer::singleShot(1000,[=](){
        pDairyDateTreeModel->loadAllDairy();
    });

}

void CDairyMainWindow::initPagePrivate()
{
    //ui->btnAdd->setEnabled();
    ui->listWidgetPrivate->setIconSize(QSize(64,64));
    ui->listWidgetPrivate->setGridSize(QSize(96,96));
    //ui->listWidgetPrivate->set
    //ui->listWidgetPrivate->setResizeMode(QListView::Adjust); //设置QListView大小改变时，图标的调整模式，默认是固定的，但可以改成自动调整：
//    CPrivateMenuModel *pModel = new CPrivateMenuModel(this);
//    ui->listViewPrivate->setModel(pModel);
//    ui->listViewPrivate->setViewMode(QListView::IconMode);
    // 此处用listWidget替代listView

    //直接操作数据库
//    ui->tableViewPrivate->setShowGrid(false); //设置不显示格子线
    ui->tableViewPrivate->horizontalHeader()->setStyleSheet( \
                "QHeaderView::section{font:14px 'Microsoft YaHei UI';" \
                                      "border-bottom:3px solid #DEE1E4;}"); //设置表头背景色
    ui->tableViewPrivate->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewPrivate->setSelectionBehavior(QAbstractItemView::QAbstractItemView::SelectRows);
    ui->tableViewPrivate->verticalHeader()->hide();

    ui->tableViewPrivate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // 让列头可被点击，触发点击事件
    //ui->tableViewPrivate->horizontalHeader()->setSectionsClickable(true);
    // 去掉选中表格时，列头的文字高亮
    //ui->tableViewPrivate->horizontalHeader()->setHighlightSections(false);
    //ui->tableViewPrivate->horizontalHeader()->setBackgroundRole(QPalette::Background);
    // 列头灰色
   // ui->tableViewPrivate->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(225,225,225)};");
    //connect(ui->tableViewPrivate->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    QSqlTableModel* pApasswdTableModel = new QSqlTableModel(this);
    pApasswdTableModel->setTable("tAPasswd");
    // 三种提交方式，改动即提交，选择其他行时提交，手动提交；经实际测试，其中只有手动提交在显示效果上是最好的
        pApasswdTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //pApasswdTableModel->setFilter();
//    pApasswdTableModel->setQuery("select item account passwd form tAPasswd where uid ="
//                                 + QString::number(CUser::getInstance()->getUid()));
    pApasswdTableModel->select();
    pApasswdTableModel->removeColumn(0); // 不显示aid列
    pApasswdTableModel->setHeaderData(0, Qt::Horizontal, "当前账户");
    pApasswdTableModel->setHeaderData(1, Qt::Horizontal, "栏目");
    pApasswdTableModel->setHeaderData(2, Qt::Horizontal, "账号");
    pApasswdTableModel->setHeaderData(3, Qt::Horizontal, "密码");
    ui->tableViewPrivate->setModel(pApasswdTableModel);

    CRenameWidget* pRenameWidget = new CRenameWidget(ui->stackedWidgetTool);
    ui->stackedWidgetTool->addWidget(pRenameWidget);

    QWidget* pWidget = new QWidget(ui->stackedWidgetTool);
    ui->stackedWidgetTool->addWidget(pWidget);

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
    // 个人隐私
    QSqlTableModel *pModel = dynamic_cast<QSqlTableModel *>(ui->tableViewPrivate->model());
        pModel->database().transaction(); //开始事务操作
        if (pModel->submitAll()) // 提交所有被修改的数据到数据库中
        {
            pModel->database().commit(); //提交成功，事务将真正修改数据库数据
        }
        else
        {
            pModel->database().rollback(); //提交失败，事务回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(pModel->lastError().text()));
        }
        pModel->revertAll(); //撤销修改


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



void CDairyMainWindow::on_btnAdd_clicked()
{
    QSqlTableModel* model = (QSqlTableModel*)ui->tableViewPrivate->model();
    int rowNum = model->rowCount(); //获得表的行数
        model->insertRow(rowNum); //添加一行
        model->setData(model->index(rowNum, 0), CUser::getInstance()->getUid());
        //model->submitAll(); //可以直接提交
}

void CDairyMainWindow::on_btnCommit_clicked()
{
    QSqlTableModel* model = (QSqlTableModel*)ui->tableViewPrivate->model();
    model->database().transaction(); //开始事务操作
    if (model->submitAll())
    {
        model->database().commit(); //提交
    }
    else
    {
        model->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"), tr("数据库错误: %1").arg(model->lastError().text()));
    }
}

void CDairyMainWindow::on_btnDelete_clicked()
{
    QSqlTableModel* model = (QSqlTableModel*)ui->tableViewPrivate->model();
    int curRow = ui->tableViewPrivate->currentIndex().row();
        //获取选中的行
        model->removeRow(curRow);
        //删除该行
        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        {
           model->revertAll(); //如果不删除，则撤销
        }
        else
        {
            model->submitAll(); //否则提交，在数据库中删除该行
        }
}

// setting
void CDairyMainWindow::on_action_music_triggered()
{
    m_pMusicSettingDialog->exec();
}




void CDairyMainWindow::on_btnPlayMusic_clicked()
{
    m_pMusicPlayer->onPlay(m_pMusicSettingDialog->getMusicListPath());
}

void CDairyMainWindow::on_btnTTSPlay_clicked()
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

void CDairyMainWindow::on_listWidgetPrivate_clicked(const QModelIndex &index)
{
   ui->stackedWidgetTool->setCurrentIndex(index.row());
}
