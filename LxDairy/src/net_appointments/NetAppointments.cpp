#include "NetAppointments.h"

#include <QString>
#define URL_FORMAT_MUST    "%1://%2:%3"

static const char* const HTTP_PROTOCOL_HTTP = "http";
static const char* const HTTP_PPROTOCOL_HTTPS = "https";

static const char* const SERVER_LOCAL_DOMAIN = "127.0.0.1";
static const char* const SERVER_RELEASE_DOMAIN = "47.104.141.61";


static const int HTTP_SERVER_PORT = 8181;

const char * const VIRTUAL_DIR_PATH_JOKE_TEST_DUMP = "/dump";

const char * const VIRTUAL_DIR_PATH_DAIRY_ROOT = "/dairy";
const char * const VIRTUAL_DIR_PATH_DAIRY_LIST = "/dairy/list";
const char* const VIRTUAL_DIR_PATH_DAIRY_UPLOAD = "/dairy/upload";
const char* const VIRTUAL_DIR_PATH_DAIRY_DELETE = "/dairy/delete";

const char * const VIRTUAL_DIR_PATH_ARTICLE_ROOT = "/article";
const char * const VIRTUAL_DIR_PATH_ARTICLE_LIST = "/article/list";
const char * const VIRTUAL_DIR_PATH_ARTICLE_RATING = "/article/rating";
const char * const VIRTUAL_DIR_PATH_ARTICLE_UPLOAD = "/article/upload";

const char * const VIRTUAL_DIR_PATH_REGISTER = "/register";
const char * const VIRTUAL_DIR_PATH_LOGIN = "/login";

#ifdef LOCAL_TEST

#endif




T_NetAppointment::T_NetAppointment()
    : strProtocol(HTTP_PROTOCOL_HTTP)
    , nPort(HTTP_SERVER_PORT)
{
    // #ifndef ---> ifdef
#ifdef QT_NO_DEBUG
    strDomainName = SERVER_RELEASE_DOMAIN;
#else
    strDomainName = SERVER_LOCAL_DOMAIN;
#endif
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


////////////////////////////////////////////////////////////////


T_NetAppointment CNetAppointments::s_tNetAppointment;
CNetAppointments::CNetAppointments()
{

}

QString CNetAppointments::urlTest()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Get;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_JOKE_TEST_DUMP;

    return tNetAppointment.url();
}

QString CNetAppointments::urlRegister()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_REGISTER;

    return tNetAppointment.url();
}

QString CNetAppointments::urlLogin()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_LOGIN;

    return tNetAppointment.url();
}

QString CNetAppointments::urlDairyList()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_DAIRY_DELETE;

    return tNetAppointment.url();
}

QString CNetAppointments::urlDairyUpload()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_DAIRY_UPLOAD;

    return tNetAppointment.url();
}

QString CNetAppointments::urlDairyDelete()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_DAIRY_DELETE;

    return tNetAppointment.url();
}

QString CNetAppointments::urlArticleList()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_ARTICLE_LIST;

    return tNetAppointment.url();
}



QString CNetAppointments::urlArticleUpload()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_ARTICLE_UPLOAD;

    return tNetAppointment.url();
}

QString CNetAppointments::urlArticleRating()
{
    T_NetAppointment tNetAppointment;
    tNetAppointment.eRequsetType = T_NetAppointment::ER_Post;
    tNetAppointment.strVirtualDirectory = VIRTUAL_DIR_PATH_ARTICLE_RATING;

    return tNetAppointment.url();
}

void CNetAppointments::loadSetting()
{

}




