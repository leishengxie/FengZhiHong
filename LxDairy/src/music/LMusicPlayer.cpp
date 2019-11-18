#include "LMusicPlayer.h"

#include <QMediaService>
#include <QFileDialog>
#include <QMediaPlaylist>
#include "LLrcWidget.h"
#include "MusicSettingDialog.h"

CLMusicPlayer::CLMusicPlayer(QObject *parent, QWidget *pWgtParent)
    : QObject(parent)
    , m_llCurDuration(0)
    , m_pMediaPlaylist(new QMediaPlaylist(this))
    , m_pMediaPlayer(new QMediaPlayer(this))
    , m_pMusicSettingDialog(new CMusicSettingDialog())
{

    m_pMediaPlayer->setPlaylist(m_pMediaPlaylist);
    //m_pMediaPlaylist->setCurrentIndex(index.row());
    //m_pMediaPlayer->play();

    if (pWgtParent)
    {
        m_pLrcWidget = new CLLrcWidget(pWgtParent);
    }
    else
    {
        m_pLrcWidget = new CLLrcWidget();
    }

//    connect(nextButton, SIGNAL(clicked()), m_pMediaPlaylist, SLOT(next()));
//     connect(volumeSlider, SIGNAL(valueChanged(int)), m_pMediaPlayer, SLOT(setVolume(int)));
//    connect(m_pMediaPlayer, SIGNAL(metaDataChanged()), this, SLOT(title()));
    connect(m_pMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onMediaStateChanged(QMediaPlayer::State)));
    connect(m_pMediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(m_pMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(m_pMediaPlaylist, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
}

CLMusicPlayer::~CLMusicPlayer()
{
    disconnect(m_pMediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    disconnect(m_pMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    disconnect(m_pMediaPlaylist, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
    if (m_pLrcWidget->isWindow())
    {
        m_pLrcWidget->deleteLater();
    }
    m_pMusicSettingDialog->deleteLater();
}

bool CLMusicPlayer::isPlaying()
{
    switch (m_pMediaPlayer->state())
    {
    case QMediaPlayer::PlayingState:
        return true;
    default:
        break;
    }
    return false;
}

void CLMusicPlayer::stop()
{
    m_pMediaPlayer->stop();
}

void CLMusicPlayer::showSetting()
{
     m_pMusicSettingDialog->exec();
}


void CLMusicPlayer::onOpenFile()
{
//    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"), tr("."), tr("MP3 file (*.mp3)"));
//    reloadList(fileNames);
}

void CLMusicPlayer::onPlayOtherListPath(QStringList strlstPath)
{
    reloadList(strlstPath);
}

void CLMusicPlayer::onPositionChanged(qint64 position)
{
    m_pLrcWidget->onPositionChanged(position);
}

void CLMusicPlayer::onDurationChanged(qint64 duration)
{
    //positionSlider->setRange(0, duration);
    m_llCurDuration = duration;
    QString strSrcName = m_pMediaPlayer->currentMedia().canonicalUrl().toString();
    if(strSrcName.isEmpty())
    {
        return;
    }
    //吧歌曲后缀改为歌词.lrc为后缀的歌词文本
    QString lrcfilename = strSrcName.remove(strSrcName.right(3)) + "lrc";
    // 去掉//http
    QString lrcname = lrcfilename.remove(lrcfilename.left(8));
    m_pLrcWidget->openLrcFile(lrcname);
    m_pLrcWidget->onDurationChanged(duration);
}

void CLMusicPlayer::onCurrentIndexChanged(int index)
{

}


void CLMusicPlayer::onPlay()
{
    QStringList strlstPath = m_pMusicSettingDialog->getMusicListPath();
    switch (m_pMediaPlayer->state())
    {
    case QMediaPlayer::PlayingState:
        m_pMediaPlayer->pause();
        break;
    case QMediaPlayer::StoppedState:
        reloadList(strlstPath);
        m_pMediaPlayer->play();
        break;
    default:
        m_pMediaPlayer->play();
        break;
    }
}

void CLMusicPlayer::onPlaybackMode(int nMode)
{
    m_pMediaPlaylist->setPlaybackMode((QMediaPlaylist::PlaybackMode)nMode);
}

void CLMusicPlayer::onMediaStateChanged(QMediaPlayer::State)
{
    switch (m_pMediaPlayer->state())
    {
    case QMediaPlayer::PlayingState:
        break;
    case QMediaPlayer::StoppedState:
        m_pLrcWidget->clearCurLrc();
        break;
    default:
        break;
    }
}

void CLMusicPlayer::loadList(QStringList strlstPath)
{
    foreach (QString const &fileName, strlstPath)
    {
        QFileInfo fileInfo(fileName);
        if (fileInfo.exists())
        {
            QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
            if (fileInfo.suffix().toLower() == QLatin1String("m3u"))
            {
                m_pMediaPlaylist->load(url);
            }
            else
            {
                m_pMediaPlaylist->addMedia(url);
            }
        }
        else
        {
            QUrl url(fileName);
            if (url.isValid())
            {
                m_pMediaPlaylist->addMedia(url);
            }
        }
    }
}

void CLMusicPlayer::reloadList(QStringList strlstPath)
{
    m_pMediaPlaylist->clear();
    loadList(strlstPath);
}
