#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QDir> //目录头文件
#include <QTextStream>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QDateTime>
#include <QUrl>
#include <QDesktopServices>
#include "AboutDialog.h"
#include <QCloseEvent>

//当程序需要关闭的时候所处理的内容
//所有的事件都是受保护的 成员函数
//protected
//QWidget closeEvent() QMainWindow closeEvent();


namespace Ui {
class DairyMainWindow;
}

class CSkinWidget;

class CDairyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDairyMainWindow(QWidget *parent = 0);
    ~CDairyMainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void newFileSlot();
    void openFileSlot();
    void saveFileSlot();
    void saveAsFileSlot();
    void exitFileSlot();
    void printFileSlot();
    void setFontSlot();
    void setColorSlot();
    void currentDaateTimeSlot();
    void aboutWebServicesSlot();
    void aboutSoftwareSlot();

private:
    Ui::DairyMainWindow *ui;
    QString saveFileName;
    CSkinWidget* m_pSkinWidget;
};

#endif // MAINWINDOW_H
