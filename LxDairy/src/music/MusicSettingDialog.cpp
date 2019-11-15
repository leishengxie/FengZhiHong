#include "MusicSettingDialog.h"
#include "ui_MusicSettingDialog.h"
#include <QSignalMapper>
#include <QFileDialog>
#include <QSettings>
#include <QDir>

static const QString s_strIniPath = "music_conf.ini";
static const QString s_strDefaultMusic = "蔡依林 - 日不落.mp3";

CMusicSettingDialog::CMusicSettingDialog(QWidget *parent) :
    QDialog(parent)
  , ui(new Ui::CMusicSettingDialog)
  , m_eMusicMood(EM_Happy)
  , m_nMode(Sequential)
{
    ui->setupUi(this);
    initSignalMap();
    loadSetting();
}

CMusicSettingDialog::~CMusicSettingDialog()
{
    delete ui;
}

void CMusicSettingDialog::initSignalMap()
{
    QSignalMapper *signalMapperRadioBtns = new QSignalMapper(this);
    connect(ui->radioBtnHappy, SIGNAL(clicked()), signalMapperRadioBtns, SLOT(map()));
    connect(ui->radioBtnSad, SIGNAL(clicked()), signalMapperRadioBtns, SLOT(map()));
    connect(ui->radioBtnMiss, SIGNAL(clicked()), signalMapperRadioBtns, SLOT(map()));
    connect(ui->radioBtnAngry, SIGNAL(clicked()), signalMapperRadioBtns, SLOT(map()));
    connect(ui->radioBtnLonely, SIGNAL(clicked()), signalMapperRadioBtns, SLOT(map()));
    connect(ui->radioBtnUserDefine, SIGNAL(clicked()), signalMapperRadioBtns, SLOT(map()));

    signalMapperRadioBtns->setMapping(ui->radioBtnHappy, EM_Happy);
    signalMapperRadioBtns->setMapping(ui->radioBtnSad, EM_Sad);
    signalMapperRadioBtns->setMapping(ui->radioBtnMiss, EM_Miss);
    signalMapperRadioBtns->setMapping(ui->radioBtnAngry, EM_Angry);
    signalMapperRadioBtns->setMapping(ui->radioBtnLonely, EM_Lonely);
    signalMapperRadioBtns->setMapping(ui->radioBtnUserDefine, EM_UserDefine);
    connect(signalMapperRadioBtns, SIGNAL(mapped(int)), this, SLOT(onRadioButtonClicked(int)));

    QSignalMapper *signalMapperBtns = new QSignalMapper(this);
    connect(ui->btnHappy, SIGNAL(clicked()), signalMapperBtns, SLOT(map()));
    connect(ui->btnSad, SIGNAL(clicked()), signalMapperBtns, SLOT(map()));
    connect(ui->btnMiss, SIGNAL(clicked()), signalMapperBtns, SLOT(map()));
    connect(ui->btnAngry, SIGNAL(clicked()), signalMapperBtns, SLOT(map()));
    connect(ui->btnLonely, SIGNAL(clicked()), signalMapperBtns, SLOT(map()));

    signalMapperBtns->setMapping(ui->btnHappy, EM_Happy);
    signalMapperBtns->setMapping(ui->btnSad, EM_Sad);
    signalMapperBtns->setMapping(ui->btnMiss, EM_Miss);
    signalMapperBtns->setMapping(ui->btnAngry, EM_Angry);
    signalMapperBtns->setMapping(ui->btnLonely, EM_Lonely);
    connect(signalMapperBtns, SIGNAL(mapped(int)), this, SLOT(onBtnClicked(int)));

}

void CMusicSettingDialog::loadSetting()
{
    QSettings conf(s_strIniPath, QSettings::IniFormat);
    conf.beginGroup("mood_type");
    uint unIndex = conf.value("mood_index", 0).toUInt();
    conf.endGroup();
    m_eMusicMood = E_MusicMood(unIndex);
    switch (m_eMusicMood)
    {
    case EM_Happy:
        ui->radioBtnHappy->setChecked(true);
        break;
    case EM_Sad:
        ui->radioBtnSad->setChecked(true);
        break;
    case EM_Miss:
        ui->radioBtnMiss->setChecked(true);
        break;
    case EM_Angry:
        ui->radioBtnAngry->setChecked(true);
        break;
    case EM_Lonely:
        ui->radioBtnLonely->setChecked(true);
        break;
    case EM_UserDefine:
        ui->radioBtnUserDefine->setChecked(true);
        break;
    default:
        break;
    }

    QString strDefaultHappyPath = qApp->applicationDirPath() + "/" + s_strDefaultMusic;

    conf.beginGroup("mood_path");
    QString strMoodPath = conf.value("mood_happy_path", strDefaultHappyPath).toString();
    m_mapPath[EM_Happy] = QStringList(strMoodPath);
    ui->leHappy->setText(strMoodPath);

    strMoodPath = conf.value("mood_sad_path", "").toString();
    m_mapPath[EM_Sad] = QStringList(strMoodPath);
    ui->leSad->setText(strMoodPath);

    strMoodPath = conf.value("mood_miss_path", "").toString();
    m_mapPath[EM_Miss] = QStringList(strMoodPath);
    ui->leMiss->setText(strMoodPath);

    strMoodPath = conf.value("mood_angry_path", "").toString();
    m_mapPath[EM_Angry] = QStringList(strMoodPath);
    ui->leAngry->setText(strMoodPath);

    strMoodPath = conf.value("mood_lonely_path", "").toString();
    m_mapPath[EM_Lonely] = QStringList(strMoodPath);
    ui->leLonely->setText(strMoodPath);

    int size = conf.beginReadArray("mood_user_define_path");
    QStringList strlstUserDefine;
     for (int i = 0; i < size; ++i)
     {
         conf.setArrayIndex(i);
         strlstUserDefine << conf.value("single_song_path").toString();
     }
     conf.endArray();
     m_mapPath[EM_UserDefine] = strlstUserDefine;
     ui->listWidgetSongs->addItems(strlstUserDefine);

    conf.endGroup();

}

void CMusicSettingDialog::onRadioButtonClicked(int id)
{
    m_eMusicMood = (E_MusicMood)id;
    QSettings conf(s_strIniPath, QSettings::IniFormat);
    conf.beginGroup("mood_type");
    conf.setValue("mood_index", id);
    conf.endGroup();
}

void CMusicSettingDialog::onBtnClicked(int id)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", "MP3 file (*.mp3)");
    m_mapPath[id] = QStringList(fileName);
    QSettings conf(s_strIniPath, QSettings::IniFormat);
    conf.beginGroup("mood_path");
    switch ((E_MusicMood)id)
    {
    case EM_Happy:
        ui->leHappy->setText(fileName);
        conf.setValue("mood_happy_path", fileName);
        break;
    case EM_Sad:
        ui->leSad->setText(fileName);
        conf.setValue("mood_sad_path", fileName);
        break;
    case EM_Miss:
        ui->leMiss->setText(fileName);
        conf.setValue("mood_miss_path", fileName);
        break;
    case EM_Angry:
        ui->leAngry->setText(fileName);
        conf.setValue("mood_angry_path", fileName);
        break;
    case EM_Lonely:
        ui->leLonely->setText(fileName);
        conf.setValue("mood_lonely_path", fileName);
        break;
    default:
        break;
    }
    conf.endGroup();

}

void CMusicSettingDialog::on_btnUserListMusic_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"), ".", "MP3 file (*.mp3)");
    m_mapPath[EM_UserDefine] = fileNames;
    ui->listWidgetSongs->addItems(fileNames);
    QSettings settings(s_strIniPath, QSettings::IniFormat);
    settings.beginGroup("mood_path");
    settings.beginWriteArray("mood_user_define_path");
    //    for (int i = 0; i < ui->listWidgetSongs->count(); ++i)
    //    {
    //        ui->listWidgetSongs->item(i)->text();
    //    }
    for (int i = 0; i < fileNames.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("single_song_path", fileNames.at(i));
    }
    settings.endArray();
    settings.endGroup();

}

void CMusicSettingDialog::on_radioBtnOrder_clicked()
{
    m_nMode = Sequential;
}

void CMusicSettingDialog::on_radioBtnCycleList_clicked()
{
    m_nMode = Loop;
}

void CMusicSettingDialog::on_radioBtnCycleSingle_clicked()
{
    m_nMode = CurrentItemInLoop;
}
