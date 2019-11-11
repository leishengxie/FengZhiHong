#ifndef CGLOBALFUNC_H
#define CGLOBALFUNC_H

#include <QObject>
#include <QColor>
#include <QPalette>
#include <QWidget>
#include <QDesktopWidget>

class CGlobalFunc : public QObject
{
    Q_OBJECT
public:
    explicit CGlobalFunc(QObject *parent = 0);
    
    //设置为开机启动
    static void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath);


    //设置皮肤样式


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



    //窗体居中显示
    static void moveToCenter(QWidget *widget)
    {
        int frmX = widget->width();
        int frmY = widget->height();
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        widget->move(movePoint);
    }

signals:

public slots:
};

#endif // CGLOBALFUNC_H
