#ifndef CLMUSICPLAYER_H
#define CLMUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>

class QMediaPlaylist;
//class QMediaPlayer;
class CLLrcWidget;
class CMusicSettingDialog;
//enum class QMediaPlayer::State :int;
//enum class QMediaPlayer::State;

class CLMusicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit CLMusicPlayer(QWidget *parent = 0);
    ~CLMusicPlayer();

    CLLrcWidget* getLrcWidget()
    {
        return m_pLrcWidget;
    }

    bool isPlaying();
    void stop();
    void showSetting();
    virtual QSize sizeHint() const;

signals:
    void finished();

public slots:
    void onOpenFile();
    void onPlayOtherListPath(QStringList strlstPath);
    void onPlay();
    void onPlaybackMode(int nMode);



private slots:
    void onMediaStateChanged(QMediaPlayer::State);
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void onCurrentIndexChanged(int index);



private:
    void loadList(QStringList strlstPath);
    void reloadList(QStringList strlstPath);

private:

    // 媒体播放列表
    QMediaPlaylist* m_pMediaPlaylist;

    // 媒体播放器
    QMediaPlayer* m_pMediaPlayer;

    // 当前播放的媒体总长度
    qint64 m_llCurDuration;

    // 歌词
    CLLrcWidget* m_pLrcWidget;

    // 设置
    CMusicSettingDialog* m_pMusicSettingDialog;
};

#endif // CLMUSICPLAYER_H
