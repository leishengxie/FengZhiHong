#ifndef L_WINDOWS_TTS_H
#define L_WINDOWS_TTS_H

#include "tts/TTS.h"
#include <QObject>
//#include <QAxObject>

/**
 *
 qt中要使用了一个vs2010编译的.lib静态库error: undefined reference to
对于C语言而言，用于连接dll的连接lib是可以通用的，dll也是可以通用的。但是静态库目前而言并不是通用的，一般的处理方式是编译成dll，然后生成连接lib(a)库，引入项目，或者使用libtdl动态加载dll文件。
静态库不可通用的原因是，基础库相差太多，objdump甚至都无法识别使用vc默认选项编译出啦的obj文件格式。另外reimp不是用于这个用途的，是为dll的连接lib(a)文件提供转换的。
对于C++而言，所有二进制代码都是不可通用的，毕竟名称修饰都相差甚远。
*/

class CLWin10TTS81;

class CLWindowsTTSS : public ITTS
{
    Q_OBJECT

public:
    CLWindowsTTSS(QObject * parent = NULL);
    virtual ~CLWindowsTTSS();

    virtual bool initSpeech();
    virtual bool speak(const QString & txt);
    virtual void pause();
    virtual void resume();
    virtual void stop();

    //rate range : -10 - 10
    virtual int rate();
    virtual void setRate(int rate);

    //volume range : 0 - 100
    virtual int volume();
    virtual void setVolume(int value) ;
    virtual bool isSpeaking();
private slots:

    void dealevent(QString name, int arc , void* argv);

private:
    //QAxObject _voice;
    bool m_bInit;
    bool m_bReading;

};

#endif // L_WINDOWS_TTS_H
