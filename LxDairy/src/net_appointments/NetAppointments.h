#ifndef NET_APPOINTMENTS_H
#define NET_APPOINTMENTS_H

#ifdef APPOINTMENT_DATASTREAM
#include "NetDataStream.h"
#endif

#ifdef APPOINTMENT_JSON
#include "NetJson.h"
#endif

#ifdef APPOINTMENT_PROTOBUFF
#include "NetProtobuff.h"
#endif

/////////////////////// 网络通信约定 //////////////////

extern const char g_szServerUrl[];

class QWidget;
class LHttpClient;

class CNetAppointments
{
public:
    CNetAppointments();


public:
    /////// 通讯接口函数 //////
    // shang chuan
    static void post_uploadJoke(QWidget* widget, const LHttpClient* pHttpClient, const T_Joke & tJoke);


public:
    ///// url 组成 /////
    // 协议 --http: or https: 分隔号//
    QString strProtocol;

    // 域名 --名称或ip 分隔号:
    QString strDomainName;

    // 端口 --果省略端口部分，将采用默认端口
    int nPort;

    // 虚拟目录 --可选
    QString strVirtualDirectory;

    // 文件名部分 --可选
    QString strName;

    // 参数部分 --可选, 从“？”开始到“#”为止之间的部分为参数部分，又称搜索部分、查询部分。参数与参数之间用“&”作为分隔符
    QString strPram;

    // 锚部分 --可选, 从最后一个“#”开始到最后，都是锚部分
    QString strAnchor;



};


#endif // NET_DEF_H
