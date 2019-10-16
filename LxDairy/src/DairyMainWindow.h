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
#include "Dairy.h"
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
class QMdiSubWindow;

class CDairyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDairyMainWindow(QWidget *parent = 0);
    ~CDairyMainWindow();

public:
    void setLoginWidget(CLoginWidget* pLoginWidget);

public slots:
    void slot_displayDairy(const CDairy &dairy);
    void onRequireExpand(const QModelIndex & index);

protected:
    void closeEvent(QCloseEvent *event);

private slots:

    void slotUpdateMenu(QMdiSubWindow *pMdiSubWindow);
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved);


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

    void on_action_save_all_triggered();

    void on_btnOpenDairy_clicked();

    void on_listViewTag_clicked(const QModelIndex &index);

    void on_calendarWidget_clicked(const QDate &date);

    void on_listViewPrivate_clicked(const QModelIndex &index);

private:
    void initPageDairy();
    void initPagePrivate();

private:
    Ui::DairyMainWindow *ui;
    CSkinWidget* m_pSkinWidget;
    CLoginWidget* m_pLoginWidget;
    // 当前活动的日记
    CDairy m_dairyActive;
};

#endif // MAINWINDOW_H
