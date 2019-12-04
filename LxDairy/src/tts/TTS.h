#ifndef ITTS_H
#define ITTS_H

//QtSpeech是一个Qt封装的跨平台TTS(文本变成语音输出)API，在不同平台下利用系统自带的TTS引擎。
//在Windows下使用SAPI, 在Mac下使用SpeechSynthesis，而在Linux下使用 Festival.
#include <QObject>

class ITTS : public QObject
{
    Q_OBJECT
public:
    ITTS(QObject * parent = NULL);
    virtual ~ITTS();

    virtual bool initSpeech() = 0;
    virtual bool speak(const QString & txt) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;

    //rate range : -10 - 10
    virtual int rate() = 0;
    virtual void setRate(int rate) = 0;

    //volume range : 0 - 100
    virtual int volume() = 0;
    virtual void setVolume(int value)  = 0;
    virtual bool isSpeaking() = 0;

public slots:
    void ttsSpeak(const QString &txt)
    {
        speak(txt);
    }

signals:

    void speakComplete();

};

#endif // ITTS_H
