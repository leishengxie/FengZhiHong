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

private:
    Ui::CMusicSettingDialog *ui;
    E_MusicMood m_eMusicMood;
    QMap< qint32, QStringList > m_mapPath;
};

#endif // MUSICSETTINGDIALOG_H
