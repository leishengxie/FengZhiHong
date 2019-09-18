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
class CLoginWidget;

class CDairyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDairyMainWindow(QWidget *parent = 0);
    ~CDairyMainWindow();

public:
    void setLoginWidget(CLoginWidget* pLoginWidget);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    //void openFileSlot();
    //void saveAsFileSlot();
    void currentDaateTimeSlot();


    void on_action_logout_triggered();

    void on_action_new_dairy_triggered();

    void on_action_save_triggered();

    void on_action_undo_triggered();

    void on_action_cut_triggered();

    void on_action_copy_triggered();

    void on_action_paste_triggered();

    void on_action_color_triggered();

    void on_action_redo_triggered();

    void on_action_about_triggered();

    void on_action_lock_triggered();

    void on_action_tool_triggered();

    void on_action_skin_triggered();

    void on_action_exit_triggered();

    void on_action_font_triggered();

    void on_treeDairy_clicked(const QModelIndex &index);

private:
    Ui::DairyMainWindow *ui;
    CSkinWidget* m_pSkinWidget;
    CLoginWidget* m_pLoginWidget;
};

#endif // MAINWINDOW_H
