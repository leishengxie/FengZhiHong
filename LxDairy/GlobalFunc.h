#ifndef CGLOBALFUNC_H
#define CGLOBALFUNC_H

#include <QObject>

class CGlobalFunc : public QObject
{
    Q_OBJECT
public:
    explicit CGlobalFunc(QObject *parent = 0);
    
    //设置为开机启动
    static void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath);


    //设置皮肤样式
    static void SetStyle(const QString &styleName)
    {
        QFile file(QString(":/image/%1.css").arg(styleName));
        file.open(QFile::ReadOnly);
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        qApp->setPalette(QPalette(QColor("#F0F0F0")));
    }

    //判断是否是IP地址
    static bool IsIP(QString IP)
    {
        QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return RegExp.exactMatch(IP);
    }

//    //显示信息框,仅确定按钮
//    static void ShowMessageBoxInfo(QString info)
//    {
//        frmMessageBox *msg = new frmMessageBox;
//        msg->SetMessage(info, 0);
//        msg->exec();
//    }

//    //显示错误框,仅确定按钮
//    static void ShowMessageBoxError(QString info)
//    {
//        frmMessageBox *msg = new frmMessageBox;
//        msg->SetMessage(info, 2);
//        msg->exec();
//    }

//    //显示询问框,确定和取消按钮
//    static int ShowMessageBoxQuesion(QString info)
//    {
//        frmMessageBox *msg = new frmMessageBox;
//        msg->SetMessage(info, 1);
//        return msg->exec();
//    }

//    //延时
//    static void Sleep(int sec)
//    {
//        QTime dieTime = QTime::currentTime().addMSecs(sec);
//        while ( QTime::currentTime() < dieTime ) {
//            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//        }
//    }

//    //窗体居中显示
//    static void FormInCenter(QWidget *frm)
//    {
//        int frmX = frm->width();
//        int frmY = frm->height();
//        QDesktopWidget w;
//        int deskWidth = w.width();
//        int deskHeight = w.height();
//        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
//        frm->move(movePoint);
//    }

signals:

public slots:
};

#endif // CGLOBALFUNC_H
