#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>
#include <QDesktopWidget>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTimer>
#include "LQt.h"


//const QString c_strUrlDownloadRoot = "http://47.104.141.61:8080/LxDiaryUpdateDir/"; 自己的web服务端口
static const QString c_strUrlDownloadRoot = "http://47.104.141.61/LxDiaryUpdateDir/";  //apache
static const QString c_strLocalVersionFile = "version_msg.xml";
static const QString c_strUrlVersionFile = "version_msg.xml";
static const QString c_strDownloadDirName = "tempDir";
static const QString c_strMainAppName = "LxDairy.exe";

// 思路
// 1、下载版本文件，并对比新老版本，得到需要更新的文件列表
// 2、法一:需要更新的文件下载到一个新的临时目录，全部下载完后拷贝覆盖主程序相关的文件
// 2、法二:先删除主程序目录里所有需要更新的目录文件，然后直接下载需要更新的文件到主程序目录
// 2、法三:下载过程中直接写入更新文件的内容到旧文件当中

CWidget::CWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

CWidget::~CWidget()
{
    delete m_httpDownload;
    delete ui;
}


void CWidget::init()
{
    //应用程序在屏幕中间
    QDesktopWidget* deskdop = QApplication::desktop();
    move((deskdop->width() - width()) / 2, (deskdop->height() - height()) / 2);


    //设置背景颜色（两种方法都可以）
    QPalette pal;
    pal.setColor(QPalette::Background, QColor(255, 245, 225) );
    setPalette(pal);
    setAutoFillBackground(true);

    m_httpDownload = new LHttpDownload(this);
    connect(m_httpDownload, SIGNAL(downloadCompleted(T_TaskDownloadInfo)), this, SLOT(onDownloadCompleted(T_TaskDownloadInfo)));
    connect(m_httpDownload, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
    connect(m_httpDownload, SIGNAL(downloadProgressAll(qint64, qint64)), this, SLOT(onDownloadProgressAll(qint64, qint64)));
    connect(m_httpDownload, SIGNAL(finishedAllTask()), this, SLOT(onFinishedAllTask()));

    // 检测网络连接
    //ui->labelTitle->setText("正在检测网络……");
    //checkNetWorkOnline();

    downLoadVersionFile();

}

//void Widget::checkNetWorkOnline()
//{
//    QHostInfo::lookupHost("47.104.141.61", this, SLOT(onLookupHost(QHostInfo)));
//}

//void Widget::onLookupHost(QHostInfo host)
//{
//    if (host.error() == QHostInfo::NoError)
//    {
//        downLoadVersionFile();
//    }
//    else
//    {
//        ui->labelTitle->setText("网络连接失败……");
//    }
//}

///
/// \brief Widget::downLoadVersionFile 下载version_msg.xml
///
void CWidget::downLoadVersionFile()
{
    m_eStepUpd = ES_CheckXml;
    m_httpDownload->download(c_strUrlDownloadRoot + c_strUrlVersionFile
                             , c_strUrlVersionFile
                             , QDir::currentPath() + "/" + c_strDownloadDirName);
}

void CWidget::onDownloadCompleted(T_TaskDownloadInfo tTaskDownloadInfo)
{
    // 如果不是version_msg.xml则返回
    if (tTaskDownloadInfo.rename != c_strUrlVersionFile)
    {
        return;
    }

    ui->labelTitle->setText("正在校验更新文件……");
    CLQt::Sleep(1000);
    QString strLocalXmlFile = QDir::currentPath() + "/" + c_strLocalVersionFile;
    QString strRemoteXmlFile = QDir::currentPath() + "/" + c_strDownloadDirName + "/" + c_strUrlVersionFile;
    QFile file(strLocalXmlFile);
    if (!file.exists())
    {
        // 校验文件失败
        return;
    }

    m_lstBinFileMsg.clear();
    m_lstBinFileMsg = CLVersionXmlTool::getListVersionDownload(strLocalXmlFile, strRemoteXmlFile);
    if (m_lstBinFileMsg.empty())
    {
        executeMainApp(c_strMainAppName);
        return;
    }

    // 替换掉旧的xml文件
    QFile::remove(strLocalXmlFile);
    QFile::copy(strRemoteXmlFile, strLocalXmlFile);
    downLoadUpdateFiles();
}


void CWidget::onFinishedAllTask()
{
    if ( m_eStepUpd == ES_CheckXml)
    {
        return;
    }
    ui->labelTitle->setText("更新完成……");
    executeMainApp(c_strMainAppName);
}


// 根据更新列表下载
void CWidget::downLoadUpdateFiles()
{
    m_eStepUpd = ES_CheckUpdFiles;
    ui->labelTitle->setText("正在下载更新文件……");
    QStringList urlsStringList;
    foreach (T_BinFileNodeMsg tBinFileMsg, m_lstBinFileMsg)
    {
        QString strUrlFull;
        if (tBinFileMsg.dir.isEmpty())
        {
            strUrlFull = c_strUrlDownloadRoot + tBinFileMsg.dir + tBinFileMsg.name;
        }
        else
        {
            strUrlFull = c_strUrlDownloadRoot + tBinFileMsg.dir + "/" + tBinFileMsg.name;
        }
        urlsStringList.append(strUrlFull);
    }
    m_httpDownload->downloadList(urlsStringList, "");
}




void CWidget::executeMainApp(QString strMain)
{
    if(strMain.isEmpty())
    {
        return;
    }
    /**运行主程序，并且退出当前更新程序(说明：主程序在上上一级目录中)**/
    QStringList strlstArg;
    strlstArg << "1";
    if(!QProcess::startDetached(strMain, strlstArg))//启动主程序，主程序在其上一级目录, 程序不能使用exit(0),会发生线程错误
    {
        QMessageBox::warning(this, "警告信息", "启动主程序错误!\n可能主程序不存在或者被破坏!\n解决办法：重新安装程序!");
    }
    close();
}

void CWidget::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    T_TaskDownloadInfo* pTaskDownloadInfo = m_httpDownload->getCurTask();
    QString strTip = QString("下载内容:%1 速度%2 (已下载%3/总大小%4)")
            .arg(pTaskDownloadInfo->rename)
            .arg(/*pTaskDownloadInfo->speed*/"")
            .arg(CLQt::formatBytes(bytesReceived, 2))
            .arg(CLQt::formatBytes(bytesTotal, 2));
    ui->labelTip->setText(strTip);
    ui->progressBarCur->setValue((bytesReceived / (double)bytesTotal) * 100);

}

void CWidget::onDownloadProgressAll(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBarTotal->setValue(bytesReceived / (double)bytesTotal * 100);

}

