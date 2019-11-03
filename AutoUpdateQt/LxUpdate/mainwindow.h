#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**********************Ugrade.exe*************/
#include <QMainWindow>
#include "LHttpDownload.h"

namespace Ui {
class MainWindow;
}

//class LHttpDownload;

struct T_BinFileMsg
{
    QString name;
    QString dir;
    QString version;
    T_BinFileMsg()
    {
        init();
    }

    void init()
    {
        name = "";
        dir = "";
        version = "";
    }
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    T_BinFileMsg getElementMsgByName(QString strXmlFile, QString strBinName);
    void checkVersion(const T_BinFileMsg & tBinFileMsgNew, const T_BinFileMsg & tBinFileMsgOld);
    bool checkUpdateFiles(QString strNewFile, QString strOldFile);


    void executeMainApp(QString strMain);

private slots:

    void onDownloadProgress(qint64 bytesReceived,qint64 bytesTotal);
    void onDownloadProgressAll(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadCompleted(T_TaskDownloadInfo tTaskDownloadInfo);
    void onFinishedAllTask();

    void downLoadUpdateFiles();
private:
    void init();
    void downLoadVersionFile();


private:
    Ui::MainWindow *ui;

    LHttpDownload* m_httpDownload;

    QList<T_BinFileMsg> m_lstBinFileMsg;

    bool  m_bIsFinished;
    QString m_strTip;

};

#endif // MAINWINDOW_H
