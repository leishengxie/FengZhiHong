#ifndef MUSICSETTINGDIALOG_H
#define MUSICSETTINGDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class CMusicSettingDialog;
}

class CMusicSettingDialog : public QDialog
{
    Q_OBJECT
    enum PlaybackMode { CurrentItemOnce, CurrentItemInLoop, Sequential, Loop, Random };
public:
    enum E_MusicMood
    {
        EM_Happy,
        EM_Sad,
        EM_Miss,
        EM_Angry,
        EM_Lonely,
        EM_UserDefine
    };


    explicit CMusicSettingDialog(QWidget *parent = 0);
    ~CMusicSettingDialog();

    QStringList getMusicListPath()
    {
        return m_mapPath[m_eMusicMood];
    }

signals:

private:
    void initSignalMap();
    void loadSetting();

private slots:
    void onRadioButtonClicked(int id);
    void onBtnClicked(int id);

    void on_btnUserListMusic_clicked();

    void on_radioBtnOrder_clicked();

    void on_radioBtnCycleList_clicked();

    void on_radioBtnCycleSingle_clicked();

private:
    Ui::CMusicSettingDialog *ui;
    E_MusicMood m_eMusicMood;
    QMap< qint32, QStringList > m_mapPath;
    int m_nMode;
};

#endif // MUSICSETTINGDIALOG_H
