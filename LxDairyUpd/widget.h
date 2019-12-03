#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QHostInfo>
#include "LVersionXmlTool.h"
#include "LHttpDownload.h"

namespace Ui {
class Widget;
}


class CWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CWidget(QWidget *parent = 0);
    ~CWidget();

    // 更新步骤
    enum E_StepUpd
    {
        ES_CheckXml,
        ES_CheckUpdFiles
    };


    bool checkUpdateFiles(const QString & strNewFile, const QString & strOldFile);


    void executeMainApp(QString strMain);

private slots:

    void onDownloadProgress(qint64 bytesReceived,qint64 bytesTotal);
    void onDownloadProgressAll(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadCompleted(T_TaskDownloadInfo tTaskDownloadInfo);
    void onFinishedAllTask();

    void downLoadUpdateFiles();
    //void onLookupHost(QHostInfo host);
private:
    void init();
    //void checkNetWorkOnline();
    void downLoadVersionFile();


private:
    Ui::Widget *ui;

    LHttpDownload* m_httpDownload;

    QList<T_BinFileNodeMsg> m_lstBinFileMsg;

    bool  m_bIsFinished;
    QString m_strTip;

    E_StepUpd m_eStepUpd;
};



#endif // WIDGET_H
