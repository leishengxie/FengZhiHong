#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "network/LHttpDownload.h"

namespace Ui {
class Widget;
}


///
/// \brief The T_BinFileNodeMsg struct 序列化的xml节点为版本信息文件
///
struct T_BinFileNodeMsg
{
    QString name;
    QString dir;
    QString version;
    T_BinFileNodeMsg()
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



class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();



    T_BinFileNodeMsg getElementMsgByName(QString strXmlFile, QString strBinName);
    void checkVersion(const T_BinFileNodeMsg & tBinFileMsgNew, const T_BinFileNodeMsg & tBinFileMsgOld);
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
    Ui::Widget *ui;

    LHttpDownload* m_httpDownload;

    QList<T_BinFileNodeMsg> m_lstBinFileMsg;

    bool  m_bIsFinished;
    QString m_strTip;
};



#endif // WIDGET_H
