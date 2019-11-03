#ifndef CLMUSICPLAYER_H
#define CLMUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>

class QMediaPlaylist;
//class QMediaPlayer;
class CLLrcWidget;

//enum class QMediaPlayer::State :int;
//enum class QMediaPlayer::State;

class CLMusicPlayer : public QObject
{
    Q_OBJECT
public:
    explicit CLMusicPlayer(QObject *parent = 0, QWidget* pWgtParent = false);
    ~CLMusicPlayer();

    CLLrcWidget* getLrcWidget()
    {
        return m_pLrcWidget;
    }

    bool isPlaying();
    void stop();

signals:

public slots:
    void onOpenFile();
    void onPlayOtherListPath(QStringList strlstPath);
    void onPlay();
    void onPlay(QStringList strlstPath);


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

    CLLrcWidget* m_pLrcWidget;
};

#endif // CLMUSICPLAYER_H