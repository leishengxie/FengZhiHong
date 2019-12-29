#include "DairyWidget.h"
#include "ui_DairyWidget.h"

#include "dairy_date/DairyDateTreeModel.h"
#include "dairy_date/DairyDateDelegate.h"

#include "dairy_tag/DairyTagListModel.h"
#include "dairy_tag/DairyTagDelegate.h"
#include "SqlOperate.h"
#include "DairyApp.h"

#include <QIcon>
#include <QtDebug>

#include <QTimer>
#include <QCloseEvent>

CDairyWidget::CDairyWidget(QWidget* parent)
    : CLBaseWidget(parent)
    , ui(new Ui::CDairyWidget)
{
    ui->setupUi(this);

    // 初始化listViewTag
    pDairyTagListModel = new CDairyTagListModel(this);
    CDairyTagDelegate* pDairyTagDelegate = new CDairyTagDelegate;
    ui->listViewTag->setModel(pDairyTagListModel);
    ui->listViewTag->setItemDelegate(pDairyTagDelegate);

    // 初始化pDairyDateTreeModel
    pDairyDateTreeModel = new CDairyDateTreeModel(this);
    CDairyDateDelegate* pDairyDateDelegate = new CDairyDateDelegate;
    ui->treeDairy->setModel(pDairyDateTreeModel);
    ui->treeDairy->setItemDelegate(pDairyDateDelegate);

    connect(pDairyDateTreeModel, SIGNAL(loadTodayDairyFinished(CDairy)), ui->page_dairy, SLOT(slot_displayDairy(CDairy)));
    connect(pDairyDateTreeModel, SIGNAL(requireExpand(QModelIndex)), this, SLOT(onRequireExpand(QModelIndex)));


    connect(ui->page_dairy_statistics, SIGNAL(expandDairy(int)), pDairyDateTreeModel, SLOT(expandDairy(int)));

    connect(ui->page_dairy, SIGNAL(saveDairyfinishedS1(CDairy,CDairy)), this, SLOT(onSaveDairyfinished(CDairy,CDairy)));
    connect(ui->page_dairy, SIGNAL(requirePlayMusic()), this, SIGNAL(requirePlayMusicS1()));
    connect(ui->page_dairy, SIGNAL(requireTTSspeak(QString)), this, SIGNAL(requireTTSspeakS1(QString)));
    connect(this, SIGNAL(musicFinishedS1()), ui->page_dairy, SLOT(onMusicFinished()));

    //ui->mdiArea->cascadeSubWindows(); //MDI区域内的所有子窗口重叠排列
    //ui->mdiArea->tileSubWindows(); //将所有子窗口在MDI区域内排列整齐
    //QMdiArea::AreaOption option;
    //ui->mdiArea->setOption(option, true);
    //connect(ui->mdiArea, SIGNAL(customContextMenuRequested(QPoint))
    QTimer::singleShot(500, [ = ]()
    {
        QList<CDairy> lstDairy = CSqlOperate::getDairyList(CDairyApp::userInfoLocal().uid);
        pDairyTagListModel->loadDiaryList(lstDairy);
        pDairyDateTreeModel->loadDairyList(lstDairy);
        //ui->page_dairy_statistics->showStatisticsByTag("全部日记");
    });


}

CDairyWidget::~CDairyWidget()
{
    delete ui;
}

void CDairyWidget::saveAllDairy()
{
    ui->page_dairy->saveAllDairy();
}



// 父类 与 父对象
///
/// \brief CDairyWidget::closeEvent 重写并检测子类的关闭情况
/// \param event
///
void CDairyWidget::closeEvent(QCloseEvent* event)
{
    if(ui->page_dairy->close())
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
    ui->page_dairy->saveDairy();
}

//怎么让窗口show的时候里面的组件也逐个show
//我的程序是一个QFrame,里面有很多的按钮,label之类的,每次切换的都是不同的QFrame,所以QFrame要来回show或者hide.
//我现在的程序需要提升下用户体验,我的程序运行在开发板上,所以切换程序界面的时候,很慢,得等1s才能显示.后来发现当Qframe->show()的时候
//,是等待了里面的组件初始化好才全部一下子加载上的,所以我在想我可不可以QFrame->show()的时候,QFrame里面的组件从上到下逐个show,
//这样可能带来好点的用户体验,不至于界面太慢,影响使用.

//有什么好点的办法没呢?谢谢各位了!
//------解决方案--------------------
//“我的程序是一个QFrame,里面有很多的按钮,label之类的,”
//Qt的显示机制就是那样的，只有优化程序，目前只是想到减少每个界面上的控件数目。
//想一想手机上的程序，界面上没几个控件。
void CDairyWidget::showEvent(QShowEvent* event)
{
    qDebug() << "-----showEvent()";
    CLBaseWidget::showEvent(event);
}

void CDairyWidget::hideEvent(QHideEvent* event)
{
    qDebug() << "-----hideEvent()";
    CLBaseWidget::hideEvent(event);
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




void CDairyWidget::on_treeDairy_clicked(const QModelIndex & index)
{
    qDebug() << "tree click " << "row=" << index.row() << " column=" << index.column();
    T_DairyDateItem* tDairyTagItem = qvariant_cast<T_DairyDateItem*>(index.data());
    switch (tDairyTagItem->eDairyDateNodeType)
    {
        case ED_Year:
            {
                ui->stackedWidget->setCurrentIndex(1);
                ui->page_dairy_statistics->showStatisticsByDate(tDairyTagItem->strYear, "");
                break;
            }
        case ED_Month:
            {

                ui->stackedWidget->setCurrentIndex(1);
                ui->page_dairy_statistics->showStatisticsByDate(tDairyTagItem->strYear, tDairyTagItem->strMonth);
                break;

            }
        case ED_Day:
            {
                ui->stackedWidget->setCurrentIndex(0);
                CDairy dairy;
                dairy.setDid(tDairyTagItem->did);
                ui->page_dairy->slot_displayDairy(dairy);

                break;
            }
        default:
            break;
    }


}

void CDairyWidget::onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved)
{
    ((CDairyDateTreeModel*)ui->treeDairy->model())->dairyModify(dairySaveBefore, dairySaved);
}


void CDairyWidget::on_listViewTag_clicked(const QModelIndex & index)
{
    T_DairyTagItem tDairyTagItem = qvariant_cast<T_DairyTagItem>(index.data());

    pDairyDateTreeModel->reloadDairyByTag(tDairyTagItem.strTagName);

    ui->stackedWidget->setCurrentIndex(1);
    ui->page_dairy_statistics->showStatisticsByTag(tDairyTagItem.strTagName);

}

void CDairyWidget::on_calendarWidget_clicked(const QDate & date)
{

}

