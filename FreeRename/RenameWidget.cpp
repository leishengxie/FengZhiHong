#include "RenameWidget.h"
#include "ui_RenameWidget.h"
#include <QtDebug>
#include <QFileDialog>
#include <QFile>
#include <QStandardItemModel>
#include "OriginNum.h"


CRenameWidget::CRenameWidget(QWidget *parent)
    : QWidget(parent)
    //, m_nOriginValue(1)
    , m_bAddFore(true)
    , ui(new Ui::CRenameWidget)
{
    ui->setupUi(this);
    initToolBar();
    initTabWidget();
    initTable();
    setWindowTitle("批命名工具");
}

CRenameWidget::~CRenameWidget()
{
    delete ui;
}



void CRenameWidget::initToolBar()
{

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addFile()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(delFile()));
    connect(ui->btnHandle, SIGNAL(clicked()), this, SLOT(beginHandle()));
}

void CRenameWidget::initTabWidget()
{
    ui->tabWidget->setMaximumWidth(300);
    connect(ui->lineEditOldFile, SIGNAL(textChanged(QString)), SLOT(oldFileChanged(QString)));
    connect(ui->lineEditOriginValue, SIGNAL(textChanged(QString)), SLOT(originValueChanged(QString)));
    connect(ui->spinBoxIncrement, SIGNAL(valueChanged(int)), SLOT(incrementChanged(int)));
    connect(ui->radioAddBack, SIGNAL(clicked(bool)), SLOT(addBackClicked(bool)));
    connect(ui->radioAddFore, SIGNAL(clicked(bool)), SLOT(addForeClicked(bool)));
    connect(ui->lineEditReplacePrevious, SIGNAL(textChanged(QString)), SLOT(replacePreviousChanged(QString)));
    connect(ui->lineEditReplaceAfter, SIGNAL(textChanged(QString)), SLOT(replaceAfterChanged(QString)));
    //connect(ui->checkBoxZero, SIGNAL(clicked(bool)),
}

void CRenameWidget::initTable()
{
    m_model = new QStandardItemModel();
    ui->tableView->setModel(m_model);
    //ui->tableView->horizontalHeader()->setSectionResizeMode (0,QHeaderView::Stretch); //设置列宽可伸缩
    //ui->tableView->horizontalHeader()->setSectionResizeMode (1,QHeaderView::Stretch);
    QStringList lstHead = {"原文件名", "新文件名", "状态"}; //c++ 98 不支持 c++ 11支持
    //lstHead << "原文件名" << "新文件名" << "状态";
    //ui->tableView->setColumnCount(3);
    //ui->tableView->setHorizontalHeaderLabels(lstHead);
    m_model->setColumnCount(3);
    m_model->setHorizontalHeaderLabels(lstHead);

}

void CRenameWidget::addFile()
{
    QStringList strFilePaths = QFileDialog::getOpenFileNames(this, "打开文件", "../");
    //    QString strOpenPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "../",
    //                                                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //    addFileToList(strOpenPath);
    foreach(QString strFilePath, strFilePaths)
    {
        T_FileMsg tFileMsg;
        tFileMsg.strFilePath = strFilePath;
        QFileInfo fileInfo(strFilePath);
        tFileMsg.strDir = fileInfo.dir().absolutePath();
        tFileMsg.strFileName = fileInfo.fileName();
        //tFileMsg.strBaseName = fileInfo.baseName();
        tFileMsg.strBaseName = fileInfo.completeBaseName();
        tFileMsg.strExtenName = fileInfo.suffix();
        tFileMsg.strNewFileName = fileInfo.fileName();
        //tFileMsg.strNewBaseName = fileInfo.baseName();
        tFileMsg.strNewBaseName = fileInfo.completeBaseName();
        tFileMsg.strNewExtenName = fileInfo.suffix();
        m_lstFileMsg.append(tFileMsg);
    }
    update();
}

void CRenameWidget::addFileToList(QString strFilePath)
{
    QDir dir(strFilePath);
    if (!dir.exists())
    {
        qDebug()<< "the dir:" << strFilePath << "is not exists";
        return;
    }
    dir.setFilter(QDir::Dirs|QDir::Files);//除了目录或文件，其他的过滤掉
    dir.setSorting(QDir::DirsFirst);//优先显示目录
    QFileInfoList lstFileInfo = dir.entryInfoList();//获取文件信息列表 // QFileInfoList lstFileInfo = dir.entryInfoList(filter,QDir::Dirs|QDir::Files,QDir::DirsFirst);
    foreach(QFileInfo fileInfo, lstFileInfo)
    {
        if(fileInfo.isFile())
        {
            T_FileMsg tFileMsg;
            tFileMsg.strFilePath = fileInfo.filePath();
            tFileMsg.strFileName = fileInfo.fileName();
            m_lstFileMsg.append(tFileMsg);
        }
        else
        {
            if(fileInfo.fileName()=="." || fileInfo.fileName() == "..")
            {
                continue;
            }
            qDebug() << "Entry Dir" << fileInfo.absoluteFilePath();
            addFileToList(fileInfo.absoluteFilePath()); //递归
        }
    }

}

void CRenameWidget::delFile()
{

}

void CRenameWidget::beginHandle()
{
    for (int i = 0; i < m_lstFileMsg.size(); ++i)
    {
        if (QFile::rename(m_lstFileMsg[i].strFilePath, m_lstFileMsg[i].newFilePath()))
        {
            m_lstFileMsg[i].bHandle = true;
        }
    }
    updateTableList();
    //QFile::rename
}



void CRenameWidget::update()
{
    updateDataList();
    updateTableList();
}

void CRenameWidget::updateTableList()
{
    int row = 0;
    QStandardItem *newItem = 0;
    foreach(T_FileMsg tFileMsg, m_lstFileMsg)
    {
        newItem = new QStandardItem(tFileMsg.strFileName);
        m_model->setItem(row, 0, newItem);
        newItem = new QStandardItem(tFileMsg.newFileName());
        m_model->setItem(row, 1, newItem);
        newItem = new QStandardItem(tFileMsg.bHandle ? "已处理" : "未处理");
        m_model->setItem(row, 2, newItem);
        ++row;
    }
}

void CRenameWidget::updateDataList()
{
    // 恢复到原文件名
    for (int i = 0; i < m_lstFileMsg.size(); ++i)
    {
        m_lstFileMsg[i].strNewBaseName = m_lstFileMsg[i].strBaseName;
    }
    // 操作前改名
    QString strNewBaseName = ui->lineEditOldFile->text();
    for (int i = 0; i < m_lstFileMsg.size(); ++i)
    {
        QString strNewBaseNameTemp = strNewBaseName;
        strNewBaseNameTemp.replace("原文件名", m_lstFileMsg[i].strBaseName);
        m_lstFileMsg[i].strNewBaseName = strNewBaseNameTemp;
    }

    // 起始值
    QString strOriginValue = ui->lineEditOriginValue->text();
    COriginNum originNum(strOriginValue);

    // add 20180905
    // 是否用0占位，本次采用自动根据文件最大数确定占位数，而不需要用户输入001等手动确定控制
    bool bUseZero = ui->checkBoxZero->isChecked();

    // 递增量
    int nIncrement = ui->spinBoxIncrement->value();
    int nTotalIncrement = 0;
    m_bAddFore = ui->radioAddFore->isChecked();
    for (int i = 0; i < m_lstFileMsg.size(); ++i)
    {
        if (m_bAddFore)
        {
            m_lstFileMsg[i].strNewBaseName = originNum.add(nTotalIncrement) + m_lstFileMsg[i].strNewBaseName;
        }
        else
        {
            m_lstFileMsg[i].strNewBaseName = m_lstFileMsg[i].strNewBaseName + originNum.add(nTotalIncrement);
        }
        nTotalIncrement += nIncrement;
    }


    // 替换
    QString strReplacePrevious = ui->lineEditReplacePrevious->text();
    QString strReplaceAfter = ui->lineEditReplaceAfter->text();
    if (strReplacePrevious.isEmpty() || strReplaceAfter.isEmpty())
    {
        return;
    }

    for (int i = 0; i < m_lstFileMsg.size(); ++i)
    {
        if (m_lstFileMsg[i].strNewBaseName.contains(strReplacePrevious))
        {
            m_lstFileMsg[i].strNewBaseName = m_lstFileMsg[i].strNewBaseName.replace(strReplacePrevious, strReplaceAfter);
        }
    }

}

void CRenameWidget::oldFileChanged(QString strOldFile)
{
    update();
}

void CRenameWidget::originValueChanged(QString strOriginValue)
{
    update();
}

void CRenameWidget::incrementChanged(int nIncrement)
{
    update();
}

void CRenameWidget::addBackClicked(bool checked)
{
    update();
}

void CRenameWidget::addForeClicked(bool checked)
{
    update();
}

void CRenameWidget::replacePreviousChanged(QString strPrev)
{
    update();
}

void CRenameWidget::replaceAfterChanged(QString strAfter)
{
    update();
}

void CRenameWidget::useZero(bool bUse)
{
    update();
}
