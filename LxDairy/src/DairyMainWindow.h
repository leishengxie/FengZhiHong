#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

namespace Ui {
class DairyMainWindow;
}

class CSkinWidget;
class CLoginWidget;
class CLMusicPlayer;
class ITTS;


class CDairyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDairyMainWindow(QWidget *parent = 0);
    ~CDairyMainWindow();

public:
    void setLoginWidget(CLoginWidget* pLoginWidget);

public slots:
    void onBgPixmapChanged(const QPixmap & pixmap);

protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:

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

    void on_action_save_all_triggered();

    void on_action_music_triggered();



    void on_action_download_android_triggered();

private:
    Ui::DairyMainWindow *ui;

    /// 各控件指针 ////
    // 皮肤控制控件
    CSkinWidget* m_pSkinWidget;

    // 登录
    CLoginWidget* m_pLoginWidget;

    // 音乐播放器
    CLMusicPlayer* m_pMusicPlayer;

    // tts播放
    ITTS* m_pITTS;

    // 背景图片
    QPixmap m_pixBg;

};

#endif // MAINWINDOW_H
