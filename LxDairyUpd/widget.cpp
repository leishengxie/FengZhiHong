#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>
#include <QDesktopWidget>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QTimer>


//const QString c_strUrlDownloadRoot = "http://47.104.141.61:8080/LxDiaryUpdateDir/"; 自己的web服务端口
const QString c_strUrlDownloadRoot = "http://47.104.141.61/LxDiaryUpdateDir/";  //apache
const QString c_strLocalVersionFile = "version_msg.xml";
const QString c_strUrlVersionFile = "version_msg.xml";
const QString c_strDownloadDirName= "tempDir";
const QString c_strMainAppName = "LxDairy.exe";

// 思路
// 1、下载版本文件，并对比新老版本，得到需要更新的文件列表
// 2、法一:需要更新的文件下载到一个新的临时目录，全部下载完后拷贝覆盖主程序相关的文件
// 2、法二:先删除主程序目录里所有需要更新的目录文件，然后直接下载需要更新的文件到主程序目录
// 2、法三:下载过程中直接写入更新文件的内容到旧文件当中

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //init();
    m_httpDownload = new LHttpDownload(this);
    connect(m_httpDownload, SIGNAL(downloadCompleted(T_TaskDownloadInfo)), this, SLOT(onDownloadCompleted(T_TaskDownloadInfo)));
    connect(m_httpDownload, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
    connect(m_httpDownload, SIGNAL(downloadProgressAll(qint64,qint64)), this, SLOT(onDownloadProgressAll(qint64,qint64)));
    connect(m_httpDownload, SIGNAL(finishedAllTask()), this, SLOT(onFinishedAllTask()));
    downLoadVersionFile();
}

Widget::~Widget()
{
    delete m_httpDownload;
    delete ui;
}


void Widget::init()
{
    //应用程序在屏幕中间
    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() -this->width())/2, (deskdop->height() - this->height())/2);

    setWindowFlags(Qt::FramelessWindowHint);//没有标题栏

    //固定高和宽：
    setFixedSize(400,200);

    //设置背景颜色（两种方法都可以）
    //this->setStyleSheet("QMainWindow{background:rgb(240,250,250)}");
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(255,245,225) );
    setPalette(pal);
    setAutoFillBackground(true);

}

///
/// \brief Widget::downLoadVersionFile 下载version_msg.xml
///
void Widget::downLoadVersionFile()
{
    m_httpDownload->download(c_strUrlDownloadRoot + c_strUrlVersionFile
                             , c_strUrlVersionFile
                             , QDir::currentPath() + "/" + c_strDownloadDirName);
}

void Widget::onDownloadCompleted(T_TaskDownloadInfo tTaskDownloadInfo)
{
    // 如果不是version_msg.xml则返回
    if (tTaskDownloadInfo.rename != c_strUrlVersionFile)
    {
        return;
    }

    m_lstBinFileMsg.clear();
    m_lstBinFileMsg = CLVersionXmlTool::getListVersionDownload(QDir::currentPath() + "/" + c_strLocalVersionFile
                     , QDir::currentPath() + "/" + c_strDownloadDirName + "/" + c_strUrlVersionFile);
    if (m_lstBinFileMsg.empty())
    {
        executeMainApp(c_strMainAppName);
        return;
    }
    //QTimer::singleShot(1000, this, SLOT(downLoadUpdateFiles()));
    downLoadUpdateFiles();
}


void Widget::onFinishedAllTask()
{
    ui->labelTitle->setText("更新完成……");
    executeMainApp(c_strMainAppName);
}


// 根据更新列表下载
void Widget::downLoadUpdateFiles()
{
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
    m_httpDownload->downloadList(urlsStringList);
}


void Widget::executeMainApp(QString strMain)
{
    if(!strMain.isEmpty())
    {
        /**运行主程序，并且退出当前更新程序(说明：主程序在上上一级目录中)**/
        QStringList strlstArg;
        strlstArg << "1";
        if(!QProcess::startDetached(strMain, strlstArg))//启动主程序，主程序在其上一级目录, 程序不能使用exit(0),会发生线程错误
        {
            QMessageBox::warning(this,"警告信息","启动主程序错误!\n可能主程序不存在或者被破坏!\n解决办法：重新安装程序!");
        }
    }
    close();
}

void Widget::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBarCur->setValue(bytesReceived / bytesTotal * 100);
    // 下载内容 速度 (已下载/总大小)
}

void Widget::onDownloadProgressAll(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBarTotal->setValue(bytesReceived / bytesTotal * 100);

}

