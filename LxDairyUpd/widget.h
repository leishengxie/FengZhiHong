#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "LVersionXmlTool.h"
#include "network/LHttpDownload.h"

namespace Ui {
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


    bool checkUpdateFiles(const QString & strNewFile, const QString & strOldFile);


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
    Ui::Widget *ui;

    LHttpDownload* m_httpDownload;

    QList<T_BinFileNodeMsg> m_lstBinFileMsg;

    bool  m_bIsFinished;
    QString m_strTip;
};



#endif // WIDGET_H
