#include "RenameWidget.h"
#include "ui_RenameWidget.h"
#include <QtDebug>
#include <QFileDialog>
#include <QFile>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QButtonGroup>

CRenameWidget::CRenameWidget(QWidget *parent)
    : QWidget(parent)
    , m_originNum("1")
    , m_eIncrementPos(EI_Tail)
    , m_nIncrement(1)
    , m_strNewBaseName("")
    , m_strReplacePrevious("")
    , m_strReplaceAfter("")
    , ui(new Ui::CRenameWidget)
{
    ui->setupUi(this);
    initButtons();
    initTabWidget();
    initTable();
    setWindowTitle("批命名工具");
}

CRenameWidget::~CRenameWidget()
{
    delete ui;
}



void CRenameWidget::initButtons()
{

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addFile()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(delFile()));
    connect(ui->btnHandle, SIGNAL(clicked()), this, SLOT(beginHandle()));
    ui->btnDelete->hide();
}

void CRenameWidget::initTabWidget()
{

    connect(ui->lineEditOldFile, SIGNAL(textChanged(QString)), SLOT(oldFileChanged(QString)));
    connect(ui->lineEditOriginValue, SIGNAL(textChanged(QString)), SLOT(originValueChanged(QString)));
    connect(ui->spinBoxIncrement, SIGNAL(valueChanged(int)), SLOT(incrementChanged(int)));
    connect(ui->radioAddBack, SIGNAL(clicked(bool)), SLOT(addBackClicked(bool)));
    connect(ui->radioAddFore, SIGNAL(clicked(bool)), SLOT(addForeClicked(bool)));
    connect(ui->lineEditReplacePrevious, SIGNAL(textChanged(QString)), SLOT(replacePreviousChanged(QString)));
    connect(ui->lineEditReplaceAfter, SIGNAL(textChanged(QString)), SLOT(replaceAfterChanged(QString)));
    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(ui->rBtnNoOne);
    pButtonGroup->addButton(ui->rBtnAllLowper);
    pButtonGroup->addButton(ui->rBtnAllUper);
    pButtonGroup->addButton(ui->rBtnFrontUper);
    connect(pButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonGroupClicked(int)));

}

void CRenameWidget::initTable()
{
    m_model = new QStandardItemModel();
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
        if(m_lstFileMsg[i].bHandle)
        {
            continue;
        }
        if (QFile::rename(m_lstFileMsg[i].strFilePath, m_lstFileMsg[i].newFilePath()))
        {
            m_lstFileMsg[i].bHandle = true;
        }
    }
    updateTableList();
    //QFile::rename
}

void CRenameWidget::onButtonGroupClicked(int id)
{
    Q_UNUSED(id)
    update();
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
    if (!m_strNewBaseName.isEmpty())
    {
        for (int i = 0; i < m_lstFileMsg.size(); ++i)
        {
            QString strNewBaseNameTemp = m_strNewBaseName;
            strNewBaseNameTemp.replace("原文件名", m_lstFileMsg[i].strBaseName);
            m_lstFileMsg[i].strNewBaseName = strNewBaseNameTemp;
        }
    }

    // 起始值


    // 递增量
    int nTotalIncrement = 0;
    for (int i = 0; i < m_lstFileMsg.size(); ++i)
    {
        if (m_eIncrementPos == EI_Front)
        {
            m_lstFileMsg[i].strNewBaseName = m_originNum.after(nTotalIncrement) + m_lstFileMsg[i].strNewBaseName;
        }
        else
        {
            m_lstFileMsg[i].strNewBaseName = m_lstFileMsg[i].strNewBaseName + m_originNum.after(nTotalIncrement);
        }
        nTotalIncrement += m_nIncrement;
    }


    // 替换
    if (!m_strReplacePrevious.isEmpty() && !m_strReplaceAfter.isEmpty())
    {
        for (int i = 0; i < m_lstFileMsg.size(); ++i)
        {
            if (m_lstFileMsg[i].strNewBaseName.contains(m_strReplacePrevious))
            {
                m_lstFileMsg[i].strNewBaseName = m_lstFileMsg[i].strNewBaseName.replace(m_strReplacePrevious, m_strReplaceAfter);
            }
        }
    }



    // 格式化
    for (int i = 0; i < m_lstFileMsg.size(); ++i)
    {
        if (ui->rBtnAllUper->isChecked())
        {
            m_lstFileMsg[i].strNewBaseName = m_lstFileMsg[i].strNewBaseName.toUpper();
            m_lstFileMsg[i].strNewExtenName = m_lstFileMsg[i].strNewExtenName.toUpper();
        }
        else if (ui->rBtnAllLowper->isChecked())
        {
            m_lstFileMsg[i].strNewBaseName = m_lstFileMsg[i].strNewBaseName.toLower();
            m_lstFileMsg[i].strNewExtenName = m_lstFileMsg[i].strNewExtenName.toLower();
        }
        else if (ui->rBtnFrontUper->isChecked())
        {
            if (m_lstFileMsg[i].strNewBaseName.isEmpty())
            {
                continue;
            }
            QChar ch = m_lstFileMsg[i].strNewBaseName.at(0).toUpper();
            m_lstFileMsg[i].strNewBaseName = QString(ch) + m_lstFileMsg[i].strNewBaseName.toLower().mid(1);
        }
    }

}

void CRenameWidget::oldFileChanged(QString strOldFile)
{
    m_strNewBaseName = strOldFile;
    update();
}

void CRenameWidget::originValueChanged(QString strOriginValue)
{
    m_originNum = COriginNum(strOriginValue);
    update();
}

void CRenameWidget::incrementChanged(int nIncrement)
{
    m_nIncrement = nIncrement;
    update();
}

void CRenameWidget::addBackClicked(bool checked)
{
    Q_UNUSED(checked)
    m_eIncrementPos = EI_Tail;
    update();
}

void CRenameWidget::addForeClicked(bool checked)
{
    Q_UNUSED(checked)
    m_eIncrementPos = EI_Front;
    update();
}

void CRenameWidget::replacePreviousChanged(QString strPrev)
{
    m_strReplacePrevious = strPrev;
    update();
}

void CRenameWidget::replaceAfterChanged(QString strAfter)
{
    m_strReplaceAfter = strAfter;
    update();
}


