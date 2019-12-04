#include "LWindowsTTSS.h"

//#include <windows.h>
//#include <mmsystem.h>
//#include <conio.h>
//#include <iostream>
//#include "sapi.h"
//#include "sphelper.h"

//#undef UNICODE
//#include <sapi.h>
////#include <sphelper.h>
//#include <comdef.h>
//#define UNICODE

//#include <windows.h>
//#include <windowsx.h>
//#include <commctrl.h>

#include "LWin10TTS81.h"



CLWindowsTTSS::CLWindowsTTSS(QObject* parent)
    : ITTS(parent)
    , m_bInit(0)
    , m_bReading(0)
{
}

CLWindowsTTSS::~CLWindowsTTSS()
{
    tts_release();
}


bool CLWindowsTTSS::initSpeech()
{

    if(m_bInit)
    {
        return true;
    }

//    m_bInit = this->_voice.setControl("96749377-3391-11D2-9EE3-00C04F797396");
//    if(m_bInit)
//    {
//        connect(&this->_voice, SIGNAL(signal(QString, int, void*)), this, SLOT(dealevent(QString, int, void*)));
//    }
    m_bInit = tts_init();
    return m_bInit;
}

bool CLWindowsTTSS::speak(const QString & txt)
{
    if(!m_bInit)
        return false;
/*
//    int result = this->_voice.dynamicCall("Speak(QString, SpeechVoiceSpeakFlags)", txt ,1).toInt();
//    _bReading = true;
//    return result;

    ISpVoice* pVoice = NULL;

    //COM初始化：
    if (FAILED(::CoInitialize(NULL)))
    {
        return ;
    }

    //获取ISpVoice接口：
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);

    ISpObjectToken * pSpObjectToken = NULL;
    if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, L"language=804", NULL, &pSpObjectToken)))//804代表中文
    {
        pVoice->SetVoice(pSpObjectToken);//声音大小、
        pSpObjectToken->Release();
    }

    if( SUCCEEDED( hr ) )
    {
        CString strText=_T("3张全票");//引号是朗读的话 可以是中文
        hr = pVoice->Speak(strText.AllocSysString(), 0, NULL);
        pVoice->Release(); pVoice = NULL;
    }

    //千万不要忘记：
    ::CoUninitialize();
    return ;
    */

    tts_speak(const_cast<char*>(txt.toStdString().c_str()));
    return true;
}

void CLWindowsTTSS::pause()
{
    if(!m_bInit)
    {
        return;
    }
    m_bReading = false;
//    this->_voice.dynamicCall("Pause()");
//    m_pWin10TTS81->pause();
}

void CLWindowsTTSS::resume()
{
    if(!m_bInit)
    {
        return;
    }
    m_bReading = true;
//    this->_voice.dynamicCall("Resume()");
//    m_pWin10TTS81->resume();
}

void CLWindowsTTSS::stop()
{
    if(!m_bInit)
    {
        return;
    }
    m_bReading = false;
    //int result = this->_voice.dynamicCall("Speak(QString, SpeechVoiceSpeakFlags)", "", 2).toInt();
//    m_pWin10TTS81->stop();
}

bool CLWindowsTTSS::isSpeaking()
{
    return m_bReading;
}



//rate range : -10 - 10
int CLWindowsTTSS::rate()
{
    if(!m_bInit)
    {
        return -99999;
    }

    //return this->_voice.property("Rate").toInt();
 //   return m_pWin10TTS81->rate();
}

void CLWindowsTTSS::setRate(int rate)
{
    if(!m_bInit)
    {
        return;
    }

    //this->_voice.dynamicCall("SetRate(int)", rate);
   // m_pWin10TTS81->setRate(rate);
}

//volume range : 0 - 100
int CLWindowsTTSS::volume()
{

    if(!m_bInit)
    {
        return -99999;
    }

    //return this->_voice.property("Volume").toInt();
   // return m_pWin10TTS81->volume();
}

void CLWindowsTTSS::setVolume(int value)
{
    if(!m_bInit)
    {
        return;
    }

    //this->_voice.dynamicCall("SetVolume(int)", value);
   // m_pWin10TTS81->setVolume(value);
}

void CLWindowsTTSS::dealevent(QString name, int arc, void* argv)
{
    if(name == "EndStream(int,QVariant)")
    {
        m_bReading = false;
        emit speakComplete();
    }
}
