#include "DairyEditWidget.h"
#include "ui_DairyEditWidget.h"
#include <QDateTime>
#include <QtDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDrag>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QMimeData>
#include <QFileInfo>
#include "SqlOperate.h"

#include "dairy_tag/DairyTagListModel.h"
#include "DairyApp.h"

#include "NetAppointments.h"
#include "DairyHttpClient.h"

CDairyEditWidget::CDairyEditWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CDairyEditWidget)
{
    init();
}

CDairyEditWidget::CDairyEditWidget(T_Dairy dairy, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CDairyEditWidget)
{
    init();

    setWindowTitle(dairy.strTitle);

    QString strDateTime = dairy.strDateTime;
    QDateTime datetime = QDateTime::fromString(strDateTime, FORMAT_DATETIME);
    QString strDateTimeDisplay = datetime.toString(FORMAT_DATETIME_DISPLAYER);
    did = dairy.did;
    ui->comboBoxWeather->setCurrentText(dairy.strWeather);
    ui->comboBoxTag->setCurrentText(dairy.strTag);
    ui->labelDateTime->setText(strDateTimeDisplay);
    ui->leTitle->setText(dairy.strTitle);
    ui->dairyEdit->setPlainText(dairy.strContent);


}

CDairyEditWidget::~CDairyEditWidget()
{
    delete ui;
}

void CDairyEditWidget::init()
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    // 获取并显示标签
    ui->comboBoxTag->clear();
    ui->comboBoxTag->addItems(CDairyTagListModel::listSysDefaultDairyTagNames());

    // 拖放相关 拖-放
    m_dragLabel.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);   //防止拖动到任务栏
    m_dragLabel.setStyleSheet("QLabel{border:1px solid rgb(220, 239, 251); background-color: #FCFEFF; font-size:12px; min-height: 20px;}");
    m_bLeftMousePressed = false;
//    m_bHasDrag = false;
    setAcceptDrops(true);
//    setDragDropMode(QAbstractItemView::DragDrop);
//    setDragEnabled(true);
//    setDropIndicatorShown(true);

}

void CDairyEditWidget::onSave()
{
    QString strDateTimeDisplayer = ui->labelDateTime->text();
    QDateTime datetime = QDateTime::fromString(strDateTimeDisplayer, FORMAT_DATETIME_DISPLAYER);
    QString strDateTime = datetime.toString(FORMAT_DATETIME);

    T_Dairy dairy;
    //T_Dairy dairySaved;
    dairy.did = did;
    dairy.uid = CDairyApp::userInfo().uid;
    dairy.strTitle = ui->leTitle->text();
    dairy.strDateTime = strDateTime;
    dairy.strTag = ui->comboBoxTag->currentText();
    dairy.strWeather = ui->comboBoxWeather->currentText();
    dairy.strContent = ui->dairyEdit->toPlainText(); //toPlainText 去除textEdit当中的纯文本


    CDairyHttpClient* pDairyHttpClient = new CDairyHttpClient(this, true);
    connect(pDairyHttpClient, &CDairyHttpClient::finished_1, [ = ](QByteArray byteArray)
    {
        T_Dairy dairySaved = CNetAppointments::deserialization<T_Dairy>(byteArray);
        if (dairy.isNewDairy())
        {
            emit saveDairyfinished(dairy, dairySaved);
            did = dairySaved.did;
            setWindowTitle(dairySaved.strTitle);
            ui->dairyEdit->document()->setModified(false);
        }
    });
    pDairyHttpClient->post(CNetAppointments::urlDairyUpload(), CNetAppointments::serializa(dairy));


//    QString strError;
//    if (!CSqlOperate::saveDairy(dairy, dairySaved, strError))
//    {
//        QMessageBox::warning(this, "save error", strError);
//    }
//    else
//    {
//        emit saveDairyfinished(dairy, dairySaved);
//        did = dairySaved.did;
//        setWindowTitle(dairySaved.strTitle);
//        ui->dairyEdit->document()->setModified(false);
//    }



}

CDairyEdit* CDairyEditWidget::dairyEdit()
{
    return ui->dairyEdit;
}

void CDairyEditWidget::closeEvent(QCloseEvent* event)
{
    //qDebug() << parent() << "调用了子控件的close";
    if(ui->dairyEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("the File is changed");
        // 显示的文本
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        // 设置默认选中button
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
            case QMessageBox::Save:
                onSave();
                break;
            case QMessageBox::Discard:
                break;
            case QMessageBox::Cancel:
                event->ignore();
                return;
            default:
                break;
        }
    }
    event->accept();
}


#ifdef Q_OS_WIN
    #include <windows.h>
    #include "shlobj.h"
    //#include <tlhelp32.h>
    //#include <tchar.h>
    //#include "./shellext/dndobjects.h"
#endif

QString CDairyEditWidget::getDropDownFilePath()
{
    QString localPath;
#ifdef Q_OS_WIN
    POINT pt;   // 当前鼠标位置
    ::GetCursorPos(&pt);
    char szClassName[100];  // 窗口类名
    char path[MAX_PATH];
    HWND hChooseHandle = ::WindowFromPoint(pt); // 窗口句柄
    HWND hParent = ::GetParent(hChooseHandle);  // 父窗口句柄
    //HWND	hParent = ::GetForegroundWindow();
    //得到当前鼠标所在的窗口，判断是桌面还是资源管理器

    GetClassNameA(hParent, szClassName, 100);
    qDebug() << szClassName;

    if (_stricmp(szClassName, "SHELLDLL_DefView") == 0)
    {
        hParent = ::GetParent(hParent);
        GetClassNameA(hParent, szClassName, 100);
        if (_stricmp(szClassName, "Progman") == 0 || _stricmp(szClassName, "WorkerW") == 0)
        {
            // 拖到桌面的路径:
            SHGetSpecialFolderPathA(0, path, CSIDL_DESKTOPDIRECTORY, 0);
            qDebug() << path;
            localPath = path;
        }
        else
        {
            hParent = hChooseHandle;
            for (int i = 0; i < 6; i++)
            {
                hParent = ::GetParent(hParent);
            }
            const CHAR* szBuffer[6] = { ("WorkerW")
                                        , ("ReBarWindow32")
                                        , ("Address Band Root")
                                        , ("msctls_progress32")
                                        , ("Breadcrumb Parent")
                                        , ("ToolbarWindow32")
                                      };
            for (int i = 0; i < 6; i++)
            {
                HWND hChild = ::GetWindow(hParent, GW_CHILD);
                while (hChild != NULL)
                {
                    GetClassNameA(hChild, szClassName, 100);
                    if (_stricmp(szClassName, szBuffer[i]) == 0)
                    {
                        hParent = hChild;
                        break;
                    }
                    hChild = ::GetNextWindow(hChild, GW_HWNDNEXT);
                }
            }
            ::GetWindowTextA(hParent, path, MAX_PATH);//得到资源管理器所代表的文件夹路径
            qDebug() << path;
            localPath = path;		//下载路径
            int pos = localPath.indexOf(":");
            if (pos > 0)
            {
                if (localPath.contains('\\') || localPath.contains('/'))
                {
                    //非我的电脑目录
                    localPath = localPath.mid(pos + 2);
                }
                else
                {
                    //我的电脑目录
                    localPath.clear();
                }
            }
            else
            {
                //其它异常目录
                localPath.clear();
            }
        }
    }
    else
    {
        GetClassNameA(hChooseHandle, szClassName, 100);
        if (_stricmp(szClassName, "SHELLDLL_DefView") == 0)
        {
            // 拖到二级桌面的路径
            SHGetSpecialFolderPathA(0, path, CSIDL_DESKTOPDIRECTORY, 0);
            localPath = path;		//下载路径
        }
    }
#endif
    localPath.replace('\\', '/');
    return localPath;
}

void CDairyEditWidget::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        m_ptLeftPress = event->pos();
        m_bLeftMousePressed = true;
    }
}

void CDairyEditWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        m_bLeftMousePressed = false;
        QPoint ptMove = event->pos();
        int distance = (ptMove - m_ptLeftPress).manhattanLength();
        if (distance >= QApplication::startDragDistance() && !this->rect().contains(ptMove))
        {
            QString localPath = getDropDownFilePath();  //动态获取拖动时路径
            QString strTitle = ui->leTitle->text();
            if (!localPath.isEmpty() && !strTitle.isEmpty())
            {
                QString strFileName = localPath + "/" + strTitle + ".txt";
                QFile file(strFileName);
                file.open(QFile::WriteOnly | QIODevice::Truncate);
                QTextStream out(&file);
                out << ui->dairyEdit->toPlainText();
                file.close();
            }

        }
        m_dragLabel.hide();
    }
}

void CDairyEditWidget::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);

    if ((event->buttons() & Qt::LeftButton) && m_bLeftMousePressed)
    {
        QPoint ptMove = event->pos();
        int distance = (ptMove - m_ptLeftPress).manhattanLength();
        if (distance >= QApplication::startDragDistance() && !this->rect().contains(ptMove))
        {
            QString localPath = getDropDownFilePath();  //动态获取拖动时路径
            if (!localPath.isEmpty())
            {
                m_dragLabel.setText(QString("<font style = 'font-family:MicrosoftYaHei; font-size:12px; color:rgb(74,216,255);'>导出日记到 </font>")
                                    + QString("<font style = 'font-family:MicrosoftYaHei; font-size:12px;'>%1</font>").arg(localPath));
                QPoint ptCursor(QCursor::pos().x() + 11, QCursor::pos().y() + 13);
                m_dragLabel.move(ptCursor);
                m_dragLabel.show();
            }
            else
            {
                m_dragLabel.hide();
            }

        }
        else
        {
            m_dragLabel.hide();
        }
    }


}

void CDairyEditWidget::dragEnterEvent(QDragEnterEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.size() != 1)
    {
        event->ignore();
        return;
    }
    QUrl url = urls.at(0);
    QString strPath = url.toLocalFile();
    if (strPath.right(4).toLower() != ".txt")
    {
        event->ignore();
        return;
    }
    event->setDropAction(Qt::CopyAction);
    event->accept();

}

void CDairyEditWidget::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.size() != 1)
    {
        return QWidget::dropEvent(event);
    }
    QUrl url = urls.at(0);
    QString strPath = url.toLocalFile();
    QFileInfo fileInfo(strPath);
    if (fileInfo.suffix() != "txt")
    {
        return QWidget::dropEvent(event);
    }

    QString strFileCompleteBaseName = fileInfo.completeBaseName();
    QFile file(strPath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return QWidget::dropEvent(event);
    }
    QTextStream in(&file);
    QString strContent = in.readAll();
    file.close();
    ui->leTitle->setText(strFileCompleteBaseName);
    ui->dairyEdit->setText(strContent);
}

void CDairyEditWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
    return QWidget::dragLeaveEvent(event);

}

// A widget will receive drag move events repeatedly while the drag is within its boundaries
// 当拖动在其边界内时，小部件才将重复接收拖动移动事件
void CDairyEditWidget::dragMoveEvent(QDragMoveEvent* event)
{
    return QWidget::dragMoveEvent(event);
}

void CDairyEditWidget::onCopy()
{
    ui->dairyEdit->copy();
}




