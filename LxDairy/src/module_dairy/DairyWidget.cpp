#include "DairyWidget.h"
#include "ui_DairyWidget.h"


#include "NetAppointments.h"
#include "DairyHttpClient.h"

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
    init();

}

void CDairyWidget::init()
{
    // dairy_edit
    connect(ui->page_dairy, SIGNAL(saveDairyfinishedS1(T_Dairy, T_Dairy)), ui->treeDairy, SLOT(onSaveDairyfinished(T_Dairy, T_Dairy)));
    connect(ui->page_dairy, SIGNAL(requirePlayMusic()), this, SIGNAL(requirePlayMusicS1()));
    connect(ui->page_dairy, SIGNAL(requireTTSspeak(QString)), this, SIGNAL(requireTTSspeakS1(QString)));
    connect(this, SIGNAL(musicFinishedS1()), ui->page_dairy, SLOT(onMusicFinished()));

    // dairy_tag
    connect(ui->listViewTag, SIGNAL(dairyTagListClicked(QString)), ui->treeDairy, SLOT(sortDairyByTag(QString)));

    // dairy_date
    connect(ui->treeDairy, SIGNAL(sortDairyByTagFinished(QString, QList<T_Dairy>))
            , ui->page_dairy_statistics, SLOT(showStatisticsByTag(QString, QList<T_Dairy>)));
    connect(ui->treeDairy, SIGNAL(sortDairyByDateFinished(QString, QString, QList<T_Dairy>))
            , ui->page_dairy_statistics, SLOT(showStatisticsByDate(QString, QString, QList<T_Dairy>)));
    connect(ui->treeDairy, SIGNAL(requreOpenDairy(T_Dairy)), ui->page_dairy, SLOT(onOpenDairy(T_Dairy)));
    connect(ui->treeDairy, &CDairyDateTreeView::sortDairyByTagFinished, [ = ]()
    {
        ui->stackedWidget->setCurrentIndex(EP_Statistics);
    });
    connect(ui->treeDairy, &CDairyDateTreeView::sortDairyByDateFinished, [ = ]()
    {
        ui->stackedWidget->setCurrentIndex(EP_Statistics);
    });
    connect(ui->treeDairy, &CDairyDateTreeView::requreOpenDairy, [ = ]()
    {
        ui->stackedWidget->setCurrentIndex(EP_Dairy);
    });

    // dairy_statistics
    connect(ui->page_dairy_statistics, SIGNAL(openDairyClicked(T_Dairy)), ui->treeDairy, SLOT(onOpenDairyClicked(T_Dairy)));
    connect(ui->page_dairy_statistics, &CDairyStatisticsWidget::openDairyClicked, [ = ]()
    {
        ui->stackedWidget->setCurrentIndex(EP_Dairy);
    });

    //ui->mdiArea->cascadeSubWindows(); //MDI区域内的所有子窗口重叠排列
    //ui->mdiArea->tileSubWindows(); //将所有子窗口在MDI区域内排列整齐
    //QMdiArea::AreaOption option;
    //ui->mdiArea->setOption(option, true);
    //connect(ui->mdiArea, SIGNAL(customContextMenuRequested(QPoint))
    QTimer::singleShot(500, [ = ]()
    {
//        QList<T_Dairy> lstDairy = CSqlOperate::getDairyList(CDairyApp::userInfoLocal().uid);
//        ui->listViewTag->loadDiaryList(lstDairy);
//        ui->treeDairy->loadDairyList(lstDairy);
//        ui->page_dairy_statistics->showStatisticsByTag("全部日记", lstDairy);
        T_DairyListRequest tDairyListRequest;
        tDairyListRequest.uid = CDairyApp::userInfo().uid;
        requestDairyList(tDairyListRequest);
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

void CDairyWidget::requestDairyList(const T_DairyListRequest &tDairyListRequest, bool bAppend)
{
    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        T_DairyListResp tDairyListResp = CNetAppointments::deserialization<T_DairyListResp>(byteArray);
        if (bAppend)
        {
            //m_pJokeModel->appendListJoke(tDairyListResp.dairyList);
        }
        else
        {
            ui->listViewTag->loadDiaryList(tDairyListResp.dairyList);
            ui->treeDairy->loadDairyList(tDairyListResp.dairyList);
            ui->page_dairy_statistics->showStatisticsByTag("全部日记", tDairyListResp.dairyList);

        }
    });
    pDairyHttpClient->post(CNetAppointments::urlDairyList(), CNetAppointments::serializa(tDairyListRequest));
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



void CDairyWidget::on_calendarWidget_clicked(const QDate & date)
{

}



