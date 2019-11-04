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
#include "LVersion.h"

const QString c_strUrlDownloadRoot = "http://39.105.96.146:8080/";
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

    //隐藏菜单栏和工具栏
    ui->menuBar->hide();
    ui->mainToolBar->hide();

    //固定高和宽：
    setFixedSize(400,200);

    //设置背景颜色（两种方法都可以）
    //this->setStyleSheet("QMainWindow{background:rgb(240,250,250)}");
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(255,245,225) );
    setPalette(pal);
    setAutoFillBackground(true);

}


void Widget::downLoadVersionFile()
{
    m_httpDownload->download(c_strUrlDownloadRoot + c_strUrlVersionFile, c_strUrlVersionFile
                             , QDir::currentPath() + "/" + c_strDownloadDirName);
}

void Widget::onDownloadCompleted(T_TaskDownloadInfo tTaskDownloadInfo)
{
    if (tTaskDownloadInfo.rename != c_strUrlVersionFile)
    {
        return;
    }
    bool bSuccess = checkUpdateFiles(QDir::currentPath() + "/" + c_strDownloadDirName + "/" + c_strUrlVersionFile
                     , QDir::currentPath() + "/" + c_strLocalVersionFile);
    if (!bSuccess)
    {
        ui->labelTitle->setText("校验文件失败……");
    }
    if (m_lstBinFileMsg.empty())
    {
        executeMainApp(c_strMainAppName);
        return;
    }
    QTimer::singleShot(1000, this, SLOT(downLoadUpdateFiles()));
}

void Widget::onFinishedAllTask()
{
    ui->labelTitle->setText("更新完成……");
    executeMainApp(c_strMainAppName);
}

bool Widget::checkUpdateFiles(QString strNewFile, QString strOldFile)
{
    m_lstBinFileMsg.clear();
    if(strNewFile.isEmpty() || strOldFile.isEmpty())
    {
        return false;
    }
    if(!QFile::exists(strOldFile))
    {
        m_strTip="本地的更新文件不存在！";
        return false;
    }
    if(!QFile::exists(strNewFile))
    {
        m_strTip="下载更新文件错误！";
        return false;
    }
    m_strTip = "检查需要更新的文件...";
    QFile fileNew(strNewFile);
    if(!fileNew.open(QIODevice::ReadOnly|QFile::Text))
    {
        m_strTip="不能打开更新文件！";
        return false;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if(!doc.setContent(&fileNew,false,&errorStr,&errorLine,&errorColumn))
    {
        qDebug()<<"set content error...";
        return false;
    }
    fileNew.close();
    QDomElement root = doc.documentElement();
    if(root.tagName() != "filelist")
    {
        m_strTip="XML内容错误！";
        return false;
    }
    QDomNodeList nodeList=root.elementsByTagName("file");
    for(int i=0; i<nodeList.size(); i++)
    {
        T_BinFileNodeMsg tBinFileMsgNeW;
        tBinFileMsgNeW.name = nodeList.at(i).toElement().attribute("name");
        tBinFileMsgNeW.dir = nodeList.at(i).toElement().attribute("dir");
        tBinFileMsgNeW.version = nodeList.at(i).toElement().attribute("version");
        T_BinFileNodeMsg tBinFileMsgOld = getElementMsgByName(strOldFile, tBinFileMsgNeW.name);//获取本地xml文件对应文件（name）的版本信息
        checkVersion(tBinFileMsgNeW, tBinFileMsgOld);
    }
    return true;
}

// 获取strXmlFile文件下file节点的属性为文件的版本
T_BinFileNodeMsg Widget::getElementMsgByName(QString strXmlFile, QString strBinName)
{
    T_BinFileNodeMsg tBinFileMsg;
    if (strXmlFile.isEmpty() || strBinName.isEmpty())
    {
        qDebug()<< "名称或者xml文件路径为空";
        return tBinFileMsg;
    }
    if (!QFile::exists(strXmlFile))
    {
        qDebug()<<"xml文件不存在";
        return tBinFileMsg;
    }
    QFile file(strXmlFile);
    if (!file.open(QIODevice::ReadOnly|QFile::Text))
    {
        qDebug()<<"open for read error...";
        return tBinFileMsg;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        return tBinFileMsg;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if(root.tagName() != "filelist")
    {
        qDebug()<< "root.tagname!=filelist..";
        return tBinFileMsg;
    }
    int i = 0;
    QDomNodeList nodeList = root.elementsByTagName("file");
    for( ; i < nodeList.size(); ++i)
    {
        tBinFileMsg.name = nodeList.at(i).toElement().attribute("name");
        tBinFileMsg.dir   = nodeList.at(i).toElement().attribute("dir");
        tBinFileMsg.version = nodeList.at(i).toElement().attribute("version");
        if(tBinFileMsg.name == strBinName)
        {
            qDebug() << "find!" << strBinName;
            break;
        }
    }
    if(i == nodeList.size())
    {
        qDebug()<< "can't find!"<< strBinName;
        tBinFileMsg.init();
    }
    return tBinFileMsg;
}

// 确认哪些文件加入下载列表
void Widget::checkVersion(const T_BinFileNodeMsg &tBinFileMsgNew, const T_BinFileNodeMsg &tBinFileMsgOld)
{
    // 本地XML没有此文件,加入下载列表
    if (tBinFileMsgOld.version.isEmpty())
    {
        m_lstBinFileMsg.append(tBinFileMsgNew);
        return;
    }

    // 检查版本，如果本地版本低于下载的版本，则加入下载列表
    if ( LVersion(tBinFileMsgNew.version) > LVersion(tBinFileMsgOld.version) )
    {
        m_lstBinFileMsg.append(tBinFileMsgNew);
    }
    else
    {
        qDebug()<< tBinFileMsgNew.name <<"文件是最新版本，不需要更新";
    }
}



// 根据更新列表下载
void Widget::downLoadUpdateFiles()
{
    ui->labelTitle->setText("正在下载更新文件……");
    QStringList urlsStringList;
    foreach (T_BinFileNodeMsg tBinFileMsg, m_lstBinFileMsg)
    {
        QString strUrlFull = c_strUrlDownloadRoot + tBinFileMsg.dir + "/" + tBinFileMsg.name;
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

