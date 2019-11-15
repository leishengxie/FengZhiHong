#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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



private:
    Ui::DairyMainWindow *ui;
    CSkinWidget* m_pSkinWidget;
    CLoginWidget* m_pLoginWidget;

};

#endif // MAINWINDOW_H
