#include "NetAppointments.h"

#include <QString>
#define URL_FORMAT_MUST    "%1://%2:%3"

static const char* const HTTP_PROTOCOL_HTTP = "http";
static const char* const HTTP_PPROTOCOL_HTTPS = "https";

static const char* const SERVER_LOCAL_DOMAIN = "127.0.0.1";
static const char* const SERVER_RELEASE_DOMAIN = "47.104.141.61";

static const int PORT = 8080;


const char * const VIRTUAL_DIR_PATH_JOKE_ROOT = "/joke";
const char * const VIRTUAL_DIR_PATH_JOKE_UPLOAD = "/joke/upload";

#ifdef LOCAL_TEST

#endif




const char g_szServerUrl[] = "http://47.104.141.61:8080/";
//const char* const g_szserver_url="http://47.104.141.61:8080/LxDiaryUpdateDir/"; //ok
//const char* g_szserver_url="http://47.104.141.61:8080/LxDiaryUpdateDir/"; //非常量

const char g_szServerJokeUrl[] = "http://47.104.141.61:8080/joke";

T_NetAppointment::T_NetAppointment()
    : strProtocol(HTTP_PROTOCOL_HTTP)
    , strDomainName(SERVER_LOCAL_DOMAIN)
    , nPort(PORT)
{

}


////////////////////////////////////////////////////////////////


T_NetAppointment CNetAppointments::s_tNetAppointment;
CNetAppointments::CNetAppointments()
{

}


QString T_NetAppointment::url()
{
    QString strUrl = QString(URL_FORMAT_MUST).arg(strProtocol).arg(strDomainName).arg(nPort);

    strUrl +=strVirtualDirectory;
    strUrl +=strName;

    // 参数部分 --可选, 从“？”开始到“#”为止之间的部分为参数部分，又称搜索部分、查询部分。参数与参数之间用“&”作为分隔符
    QString strPrams;
    foreach (QString str, strlstPrams)
    {
        strPrams += str;
        strPrams += "&";
    }
    if (!strPrams.isEmpty())
    {
        strPrams.chop(1);
        strUrl += "?";
        strUrl += strPrams;
        strUrl += "#";
    }

    // 锚部分 --可选, 从最后一个“#”开始到最后，都是锚部分
    if (!strAnchor.isEmpty())
    {
        strUrl += "#";
        strUrl +=strAnchor;
    }
    return strUrl;
}


QString CNetAppointments::urlUploadJoke()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_JOKE_UPLOAD;

    return tNetAppointment.url();
}

void CNetAppointments::loadSetting()
{

}




